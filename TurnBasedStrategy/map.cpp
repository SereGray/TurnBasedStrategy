// This file is part of game engine TurnBasedGame
#include"map.h"


MapPoint::MapPoint() :x_(0), y_(0)
{
	border_map = false;
	N_owner = -1; // -1  point is free		
}

// получение координат вершины по номеру
pair<uint32_t,uint32_t> MapPoint::GetCoord(){
	return std::make_pair(x_,y_);
}

void MapPoint::SetX(uint32_t X){
	x_=X;
}

void MapPoint::SetY(uint32_t Y){
	y_=Y;
}


KingdomMap::KingdomMap(unsigned start_PointNum, unsigned my_id) :my_id_(my_id) {
	list_v.push_back(start_PointNum);
	borders.push_back(start_PointNum);
}

unsigned KingdomMap::GetMyId(){
	return my_id_;
}

unsigned KingdomMap::MyArea()
{
	return static_cast<unsigned>(list_v.size());
}

MapGameObj::MapGameObj(unsigned width, unsigned height):adjacent_list_(width,height), width_(width), height_(height) {

}

unsigned MapGameObj::GetNum(unsigned x, unsigned y){// получение номера вершины по координатам
	return x+y*width_;
}

unsigned MapGameObj::GetNum(std::pair<unsigned, unsigned> coord) {// тоже но через пару
	return coord.first + coord.second * width_;
}

pair<uint32_t, uint32_t> MapGameObj::GetCoord(uint32_t Num){
	uint32_t x = Num - (Num / width_) * width_ ;
	uint32_t y = Num / width_ ;
	return make_pair(x ,y);
}


// // генерация и добавление начальных точек к карте
void MapGameObj::AddStartPoitsToMap( uint32_t po){ // ро - количество стартовых точек
	if(po>height_*width_) return;
	// создаем вектор ссылок на незанятые точки 
	vector<MapPoint*> free_points;
	for (MapPoint mp : adjacent_list_) {
		if (mp.N_owner == -1) free_points.push_back(&mp);
	}
	while(po>0 && free_points.size()>0){
		--po;
		unsigned number = rand() % free_points.size();
		adjacent_list_[GetNum(free_points[number]->GetCoord())].N_owner = po;
		KingdomMap newKingdoom(number,po);
		list_kingdoms_.push_back(newKingdoom);
	}
}

// обновление границ (решение влоб)
void MapGameObj::RefreshBorders(KingdomMap & terr){
	terr.borders.clear();
	for(auto numV: terr.list_v){// обходим все вершины королевства по номерам и пров
		//  условию границы  (список точек принадлежащ соседям не пуст или соседняя 
		//  точка никому не принадлежит 

	//  получаю вершину смотрю список смежных  и владельца
		// цикл проверяет соседние точки если соседняя точка не моя то значит проверяемая точка - гранинкая
		for (auto smej_V : adjacent_list_[numV].adjacent_points) {
			if (adjacent_list_[smej_V].N_owner != terr.GetMyId()) {
				terr.borders.push_back(numV);
				break; //  эта вершина граничная  выходим
			}
		}
	}
}

// вывод на экран карты
void MapGameObj::MapToScreen(){
		// проходим по всем вершинам и форматируем в виде таблицы heigth x width_
uint32_t k=0;
	for(uint32_t j=0;j<height_;++j){
		for(uint32_t i=0;i<width_;++i){
			cout << adjacent_list_[k].N_owner<<" . ";
			++k;
		}
		cout<<endl;
	}
}

#ifdef CIMG
// функц вывода карты в графический файл с помощью CImg.h
void MapGameObj::ToFile(uint8_t point_size=10) {
	if(point_size < 10) point_size = 10;
	using namespace cimg_library;
	// генерация цветов областей
	vector<vector<unsigned char>> colors;
	for(uint32_t i=0; i <= list_kingdoms_.size(); ++i){ //TODO: check list size and N_owner 
		unsigned char r,g,b;
		r = rand() % UINT8_MAX;
		g = rand() % UINT8_MAX;
		b = rand() % UINT8_MAX;
		vector<unsigned char> temp = { r, g, b};
		colors.push_back(temp);
	}
	CImg<uint8_t> img(width_ * point_size, height_ * point_size, 1, 3); 
	// двигаюсь по списку вершин и окрашиваю каждую точку в свой цвет области
	uint32_t counter = 0;
	for(MapPoint kingdoms: adjacent_list_){
		uint32_t country = kingdoms.N_owner;
		const unsigned char color[]={ colors[country][0],colors[country][1],colors[country][2]};
		pair<uint32_t,uint32_t> coord = GetCoord(counter);
		img.draw_rectangle((coord.first * point_size),(coord.second * point_size),( coord.first * point_size + point_size),( coord.second * point_size + point_size), color);
		++counter;
	}
	img.save_bmp("map.bmp");
}
#endif //CIMG

bool MapGameObj::FreeSpace(){
	static uint32_t maxIteration=100;
	if(--maxIteration==0)return false;
	for(MapPoint p: adjacent_list_){
		if(p.N_owner==-1) return true;
	}
	return false;
}

void MapGameObj::DjekstraPath(uint32_t numBorderV,uint32_t numTargetV, vector<uint32_t> &path){
	//считается что все вершины доступны иначе добавить вес ребра = бесконечности или др. промеж. варианты
uint32_t n=adjacent_list_.Size();
vector<uint32_t> dist(n, UINT32_MAX/2), parent(n);
dist[numBorderV] = 0; // // стартовая вершина
vector<bool> used(n);
for (uint32_t i = 0; i < n; ++i) {
	int32_t vertex = -1;
	for (uint32_t j = 0; j < n; ++j)
		if (!used[j] && (vertex == -1 || dist[j] < dist[vertex]))
			vertex = j;
		if (dist[vertex] == UINT32_MAX/2)
		break;
		used[vertex] = true;
		for (size_t j = 0; j < adjacent_list_[vertex].adjacent_points.size(); ++j) {
			uint32_t to = adjacent_list_[vertex].adjacent_points[j];
			const uint32_t len =1; // вес ребра
			if (dist[vertex] + len < dist[to]) {
				dist[to] = dist[vertex] + len;
				parent[to] = vertex;
			}
		}
	}
	//recover path to target from parent vector
	vector<uint32_t> tempPath;
	uint32_t currV=numTargetV;
	//пока не достигнем стартовой вершины 
	while(parent[currV]!=numBorderV){
		//восстанавливаем предка
		tempPath.push_back(currV);
		currV = parent[currV];
	}
	// add start vertex
	tempPath.push_back(numBorderV);
	for(uint32_t i=0;i<tempPath.size();++i){
		uint32_t temp= tempPath.back();
		path.push_back(temp);
		tempPath.pop_back();
	}

}

void MapGameObj::CreateDxDTable( vector<vector<uint32_t>> & inDxD){  
	uint32_t i=0;
	inDxD.clear(); // 
	for(MapPoint p : adjacent_list_){
		for( uint32_t j: p.adjacent_points){
			inDxD[i][j] = 1;  // set 1 to contiguous(smej) vertex
			inDxD[j][i] = 1;
		}
	++i;	
	}
}

void MapGameObj::AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix) {
	inMatrix.clear();
	const uint32_t cost = 1; // default cost to move between two adjacent vertex
	uint32_t n = adjacent_list_.Size();
	vector<uint32_t> v;
	for (uint32_t j = 0; j < n; ++j) {
		v.push_back(UINT32_MAX/2);
	}
	for (uint32_t i = 0; i < n; ++i) {
		inMatrix.push_back(v);
	}
	for (uint32_t i = 0; i < n; ++i) inMatrix[i][i] = 0;
	// перевод из списка смежности в матрицу смежности
	for (uint32_t i = 0; i < n; i++){
		for (uint32_t vertex : adjacent_list_[i].adjacent_points){
			inMatrix[i][vertex] = cost;
			inMatrix[vertex][i] = cost; 
		}
	}

}

void MapGameObj::RecoveryPath(uint32_t a, uint32_t b, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path) {
	if (parent[a][b] == a) {   
		path.push_back(a);
	}
	else {
		RecoveryPath(a, parent[a][b], parent, path);
		RecoveryPath(parent[a][b], b, parent, path);
	}
}

void MapGameObj::FloydWarshall(vector<vector<uint32_t>> & parentsMatrix) {
	vector<vector<uint32_t>> adjacentMatrix;
	AdjacentMatrixFill(adjacentMatrix);
	//createDxDTable(adjacentMatrix);
	unsigned n = static_cast<unsigned>(adjacentMatrix.size());
	parentsMatrix.clear();
	for (unsigned i = 0; i < n; ++i) {
		vector<uint32_t> p;
		for (unsigned j = 0; j < n; ++j)p.push_back(i);
		parentsMatrix.push_back(p);
	}
	for (uint32_t k = 0; k < n; ++k)
		for (uint32_t i = 0; i < n; ++i)
			for (uint32_t j = 0; j < n; ++j) {
				if (adjacentMatrix[i][j] > adjacentMatrix[i][k] + adjacentMatrix[k][j]) {
					adjacentMatrix[i][j] = adjacentMatrix[i][k] + adjacentMatrix[k][j];
					parentsMatrix[i][j] = k;
				}
			}

}

vector<uint32_t> MapGameObj::FloydWarhsallPath(uint32_t start , uint32_t end, bool restart = false) { // start and end path vertex numbers
	vector<uint32_t> path ;
	static vector<vector<uint32_t>> parentsMatrix;
	if (parentsMatrix.empty() || restart == true) FloydWarshall(parentsMatrix);
	RecoveryPath(start, end, parentsMatrix, path);
	path.push_back(end);
	return path;
}
	
void MapGameObj::BalanceArea() {
	if (list_kingdoms_.size() == 0) return;
	while (TerrainsDisbalanced(1)) {
		std::sort(list_kingdoms_.begin(), list_kingdoms_.end(), [](KingdomMap lkdm, KingdomMap rkdm) { return lkdm.list_v.size() < rkdm.list_v.size(); });
		KingdomMap kingdMin = *list_kingdoms_.begin();
		KingdomMap kingdMax = *(list_kingdoms_.end() - 1);
		// ищу путь наименьшей длины с прим. Флойд-Уоршелла
		vector<uint32_t> path;   // после должен быть наикоротким
		unsigned lengthMinPath = UINT32_MAX;
		for (auto numBorderKingdMin : kingdMin.borders) {//any vertex from nim terrain
			for (auto numBorderKingdMax : kingdMax.borders) {
				vector<uint32_t> tempPath = FloydWarhsallPath(numBorderKingdMin, numBorderKingdMax);
				if (tempPath.size() < lengthMinPath) {
					path = tempPath;   // выбор наикороткого пути
					lengthMinPath = static_cast<unsigned>(tempPath.size());
				}
			}
		}
		// push points from max terrain to min terrain
		// двигаясь по пути
		reverse(path.begin(), path.end());
		uint32_t prevNumPoint = 0;
		vector<KingdomMap>::iterator prevKingd = list_kingdoms_.end() - 1;
		for(uint32_t NumPoint : path) {
			// если текущий владелец отличается от владельца предыдущей точки меняю владельца точки
			auto owner = adjacent_list_[NumPoint].N_owner;
			vector<KingdomMap>::iterator currentKingd = find_if(list_kingdoms_.begin(), list_kingdoms_.end(), [owner](KingdomMap& kingd) { return owner == kingd.GetMyId(); });																																						   //NumCurrentTerr = adjacent_list_[NumPoint].N_owner;
			if (currentKingd->GetMyId() != prevKingd->GetMyId()){
				// найти предыдущ terrain и убрать у него точку из списка   find_if
				
				// нахожу текущую точку(указатель на нее) у предыдущего королевства
				
				vector<uint32_t>::iterator prevPointIt = find_if(prevKingd->list_v.begin(), prevKingd->list_v.end(), [prevNumPoint](uint32_t& pnt) { return prevNumPoint == pnt; }); //and there
				prevKingd->list_v.erase(prevPointIt); // удалил вершину из пред списка
				currentKingd->list_v.push_back(prevNumPoint); // добавил вершину в текущ список 
				prevKingd = currentKingd; 
				adjacent_list_[prevNumPoint].N_owner = currentKingd->GetMyId(); // присвоил вершину окончательно в списке смежности
			}
			prevNumPoint = NumPoint;
		}
		for(auto & kingd : list_kingdoms_) RefreshBorders(kingd);
	}
}

bool MapGameObj::TerrainsDisbalanced(uint32_t offset){ // offset - допуск на равенство 
	unsigned max= static_cast<unsigned>(list_kingdoms_[0].list_v.size());
	for(auto terr : list_kingdoms_){
		if(max < terr.list_v.size())max=static_cast<unsigned>(terr.list_v.size());
	}
	unsigned min= static_cast<unsigned>(list_kingdoms_[0].list_v.size());
	for(auto terr : list_kingdoms_){
		if(min > terr.list_v.size())min= static_cast<unsigned>(terr.list_v.size());
	}
	if((max-min)>offset) return true;
	return false;
}
		
KingdomMap MapGameObj::GetMinTerrain(){
	unsigned min = UINT_MAX;
	KingdomMap res = list_kingdoms_[0];
	for(auto terr : list_kingdoms_){
		if(terr.list_v.size() < min) {
		       	min = static_cast<unsigned>(terr.list_v.size());
			res = terr;
		}
	}
	return res;
}

unsigned MapGameObj::GetCountSpecialists()
{
	return 0;
}

void MapGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in)
{
	// TODO: this
}

void MapGameObj::AddKingdom(unsigned by_id)
{
	vector<MapPoint*> free_points;
	for (MapPoint &mp : adjacent_list_) {
		if (mp.N_owner == -1) free_points.push_back(&mp);
	}
	if (free_points.empty()) return; // TODO: throw exception?
	unsigned number = rand() % free_points.size();
	unsigned kingdom_start_number = GetNum(free_points[number]->GetCoord());
	adjacent_list_[kingdom_start_number].N_owner = by_id;
	list_kingdoms_.push_back(KingdomMap(kingdom_start_number, by_id));
}

KingdomMap* MapGameObj::GetKingdomMap(unsigned by_id)
{
	return GetObjFromVectorUt(by_id, list_kingdoms_);
}

uint32_t MapGameObj::AreaKingdom(unsigned by_id)
{
	KingdomMap* it = GetObjFromVectorUt(by_id, list_kingdoms_);
	return it->MyArea();
}

std::string MapGameObj::ExchangeArea(int balance, unsigned first_kd_id, unsigned first_count_solders, unsigned second_kd_id, unsigned second_count_solders)
{
	return std::string();
}

vector<uint32_t> MapGameObj::GetNeighborsList(uint32_t my_N)
{
	return vector<uint32_t>();
}

uint32_t MapGameObj::GetColor()
{
	return uint32_t();
}

std::string MapGameObj::GetSummariesString()
{
	return std::string();
}

void MapGameObj::FillMap(){
	if (list_kingdoms_.size() == 0) return;
	vector<uint32_t> iterOnBorders;		// список текущего положения итератора перебора 
					//по пограничным вершинам для всех королевств ( массив итераторов по одному на королевство)
	for(uint32_t i=0;i< list_kingdoms_.size();++i) iterOnBorders.push_back(0);  //  установка начального значения итератора на 0

	while(FreeSpace()){// пока свободные клетки не закончатся
	//Обход
		for(auto &kingd: list_kingdoms_){
			// движение по окружности границы по их порядку начиная с правой
			if (iterOnBorders[kingd.GetMyId() ] >= kingd.borders.size()) {
				iterOnBorders[kingd.GetMyId() ] = 0;  // если итератор вышел за 
										//"границы королевства" то возвращаем на стартовую поз
			}
			//  если заграничная точка ничья то присваиваем (только 1)
			//  далее прохожу по границе numV - номер заграничной вершины(точки)
			// двигаюсь по списку смежности - по смежным вершинам вершины "tabSmej[kingd.borders[iterOnBorders[i]]]"
			for(uint32_t numV: adjacent_list_[kingd.borders[iterOnBorders[kingd.GetMyId()]]].adjacent_points){
				if(adjacent_list_[numV].N_owner==-1){
					adjacent_list_[numV].N_owner=kingd.GetMyId();
					kingd.list_v.push_back(numV);
					break; // quit if ok
				}
			}
			++iterOnBorders[kingd.GetMyId() ]; 	 // перемещаем итератор
		}	
		for(auto & kingd : list_kingdoms_) RefreshBorders(kingd);
	}	
	BalanceArea();
}

void MapGameObj::PrintTabSmej(){
	uint32_t i=0;
	for(MapPoint p:adjacent_list_){
		cout << i <<" num smej:"<< p.adjacent_points.size() << endl;
		++i;
		for(uint32_t v: p.adjacent_points){
		cout << v <<" " ;
		}
	cout << endl;
	}
}

/*
int main(){
	cout<< " test "<< endl;
	map m(10,10,7);
	m.toFile(10);
//	m.PrintTabSmej();
}*/

AdjacentList::AdjacentList(unsigned width, unsigned height) :width_(width), height_(height), max((unsigned long long)width * height)
{
	unsigned coordX = 0, coordY = 0;
	for (uint32_t i = 0; i < max; ++i) {
		v_adjacent_list.push_back(MapPoint());
	}
	// заполняем таблицу смежности
	for (unsigned i = 0; i < max; ++i) {
		v_adjacent_list[i].SetX(coordX);
		v_adjacent_list[i].SetY(coordY);
		// просматриваю таблицу вправо вниз добавляю 
		// к текущей точке следущую смежную и к следующей текущую
		// проверка правой границы
		if (coordX < width_ - 1) {
			v_adjacent_list[i].adjacent_points.push_back(i + 1);
			v_adjacent_list[(unsigned long long)i + 1].adjacent_points.push_back(i);
		}
		// нижней границы
		if (coordY < height_ - 1) {
			v_adjacent_list[i].adjacent_points.push_back(i + width_);
			v_adjacent_list[(unsigned long long)i + width_].adjacent_points.push_back(i);
		}
		// опредление координаты на карте
		++coordX;
		if (coordX == width_) {
			coordX = 0;
			++coordY;
		}
	}
}

MapPoint& AdjacentList::operator[](std::size_t index)
{
	return v_adjacent_list[index];
}

unsigned AdjacentList::Size()
{
	return static_cast<unsigned>(v_adjacent_list.size());
}

std::vector<MapPoint>::iterator AdjacentList::begin()
{
	return v_adjacent_list.begin();
}

std::vector<MapPoint>::const_iterator AdjacentList::begin() const
{
	return v_adjacent_list.begin();
}

std::vector<MapPoint>::const_iterator AdjacentList::cbegin() const
{
	return begin();
}

std::vector<MapPoint>::iterator AdjacentList::end()
{
	return v_adjacent_list.end();
}

std::vector<MapPoint>::const_iterator AdjacentList::end() const
{
	return v_adjacent_list.end();
}

std::vector<MapPoint>::const_iterator AdjacentList::cend() const
{
	return end();
}