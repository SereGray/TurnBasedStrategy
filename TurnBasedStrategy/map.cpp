// This file is part of game engine TurnBasedGame
#include"map.h"

// получение координат вершины по номеру
pair<uint32_t,uint32_t> MapPoint::GetCoord(){
	return std::make_pair(x,y);
}

void MapPoint::SetX(uint32_t X){
	x=X;
}

void MapPoint::SetY(uint32_t Y){
	y=Y;
}

KingdoomMap::KingdoomMap(uint32_t num, uint32_t my_id) :my_id_(my_id) {
	list_v.push_back(num);
	borders.push_back(num);
}

uint32_t KingdoomMap::GetMyId(){
	return my_id_;
}

uint32_t KingdoomMap::MyArea()
{
	return uint32_t();
}

MapGameObj::MapGameObj(uint32_t width, uint32_t height, uint32_t kingdoms) : width_(width), height_(height) {
	// создаем таблицу списков смежности
	GenerateTab();
	// добавляю начальные точки
	AddPoitsToMap(kingdoms);
	// заполняем территорию карты
	FillMap();
	// Выравниваю карту на 1 пиксель
	BalanceArea();
}

uint32_t MapGameObj::GetNum(uint32_t x, uint32_t y){// получение номера вершины по координатам
	return x+y*width_;
}

pair<uint32_t, uint32_t> MapGameObj::GetCoord(uint32_t Num){
	uint32_t x = Num - (Num / width_) * width_ ;
	uint32_t y = Num / width_ ;
	return make_pair(x ,y);
}

void MapGameObj::GenerateTab(){
	unsigned long long max=height_*width_; // maby uint64_t
	unsigned width=0,heigth=0;
	MapPoint pNull;
	// заполняем таблицу нулевыми точками
	for(uint32_t i=0;i<max;++i){
		adjacent_list_.push_back(pNull);
	}
	// заполняем таблицу смежности
for(uint32_t i=0;i<max;++i){
	adjacent_list_[i].SetX(heigth);
	adjacent_list_[i].SetY(width);	
	// просматриваю таблицу вправо вниз добавляю 
	// к текущей точке следущую смежную и к следующей текущую
	// проверка правой границы
	if(width<width_-1){
		adjacent_list_[i].adjacent_points.push_back(i+1);
		adjacent_list_[i+1].adjacent_points.push_back(i); 
	}
	// нижней границы
	if(heigth<height_-1){
		adjacent_list_[i].adjacent_points.push_back(i+width_);
		adjacent_list_[i+width_].adjacent_points.push_back(i);
	}
	// опредление координаты на карте
	++width;
	if(width==width_){
	width=0;
	++heigth;
	}
	}
}

// // генерация и добавление начальных точек к карте
void MapGameObj::AddPoitsToMap( uint32_t po){ // ро - количество стартовых точек
	if(po>height_*width_) return;
	while(po>0){
		--po;
		uint32_t x=rand()%width_;
		uint32_t y=rand()%height_;
		if(adjacent_list_[x+y*width_].N_owner==-1){
			adjacent_list_[GetNum(x,y)].N_owner=po;
		}else{
			while(adjacent_list_[GetNum(x,y)].N_owner!=-1){
		x=rand()%width_;
		y=rand()%height_;
			}
			adjacent_list_[GetNum(x,y)].N_owner=po;
		}
		KingdoomMap newKingdoom(GetNum(x,y),po);
		list_kingdoms_.push_back(newKingdoom);
	}
}

// обновление границ (решение влоб)
void MapGameObj::RefreshBorders(KingdoomMap & terr){
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
uint32_t n=adjacent_list_.size();
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
	uint32_t n = adjacent_list_.size();
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
	uint32_t n = adjacentMatrix.size();
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
	while (TerrainsDisbalanced(1)) {
		std::sort(list_kingdoms_.begin(), list_kingdoms_.end(), [](KingdoomMap lkdm, KingdoomMap rkdm) { return lkdm.list_v.size() < rkdm.list_v.size(); });
		KingdoomMap kingdMin = *list_kingdoms_.begin();
		KingdoomMap kingdMax = *(list_kingdoms_.end() - 1);
		// ищу путь наименьшей длины с прим. Флойд-Уоршелла
		vector<uint32_t> path;   // после должен быть наикоротким
		uint32_t lengthMinPath = UINT32_MAX;
		for (auto numBorderKingdMin : kingdMin.borders) {//any vertex from nim terrain
			for (auto numBorderKingdMax : kingdMax.borders) {
				vector<uint32_t> tempPath = FloydWarhsallPath(numBorderKingdMin, numBorderKingdMax);
				if (tempPath.size() < lengthMinPath) {
					path = tempPath;   // выбор наикороткого пути
					lengthMinPath = tempPath.size();
				}
			}
		}
		// push points from max terrain to min terrain
		// двигаясь по пути
		reverse(path.begin(), path.end());
		uint32_t prevNumPoint = 0;
		vector<KingdoomMap>::iterator prevKingd = list_kingdoms_.end() - 1;
		for(uint32_t NumPoint : path) {
			// если текущий владелец отличается от владельца предыдущей точки меняю владельца точки
			auto owner = adjacent_list_[NumPoint].N_owner;
			vector<KingdoomMap>::iterator currentKingd = find_if(list_kingdoms_.begin(), list_kingdoms_.end(), [owner](KingdoomMap& kingd) { return owner == kingd.GetMyId(); });																																						   //NumCurrentTerr = adjacent_list_[NumPoint].N_owner;
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
	uint32_t max=list_kingdoms_[0].list_v.size();
	for(auto terr : list_kingdoms_){
		if(max < terr.list_v.size())max=terr.list_v.size();
	}
	uint32_t min=list_kingdoms_[0].list_v.size();
	for(auto terr : list_kingdoms_){
		if(min > terr.list_v.size())min=terr.list_v.size();
	}
	if((max-min)>offset) return true;
	return false;
}
		
KingdoomMap MapGameObj::GetMinTerrain(){
	uint32_t min = 0 - 1;
	KingdoomMap res = list_kingdoms_[0];
	for(auto terr : list_kingdoms_){
		if(terr.list_v.size() < min) {
		       	min = terr.list_v.size();
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
}

uint32_t MapGameObj::AreaKingdoom(uint32_t by_id)
{
	auto it = std::find_if(list_kingdoms_.begin(), list_kingdoms_.end(), [by_id](KingdoomMap& kingd) {if (kingd.my_id_ == by_id)return true; return false; });
	return it->list_v.size();
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
