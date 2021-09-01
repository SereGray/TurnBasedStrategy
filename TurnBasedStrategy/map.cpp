// This file is part of game engine TurnBasedGame
#include"map.h"


MapPoint::MapPoint() :x_(0), y_(0), border_map(false), owner_id_(-1)// -1  point is free	
{ 	
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


unsigned  KingdomMap::GetMyId(){
	return my_id_;
}

unsigned KingdomMap::MyArea()
{
	return static_cast<unsigned>(list_v.size());
}

// обновление границ (решение влоб)
void KingdomMap::RefreshBorders(AdjacentList & adjacent_list) {
	borders.clear();
	for (auto numV : list_v) {// обходим все вершины королевства по номерам и пров
		//  условию границы  (  соседняя 
		//  точка мне не принадлежит )

	//  получаю вершину смотрю список смежных  и владельца
		// цикл проверяет соседние точки если соседняя точка не моя то значит проверяемая точка - гранинкая
		for (auto smej_V : adjacent_list[numV].adjacent_points) {
			if (adjacent_list[smej_V].owner_id_ != GetMyId()) {
				borders.push_back(numV);
				break; //  эта вершина граничная  выходим
			}
		}
	}
	RefreshNeighbors(adjacent_list);
}

void KingdomMap::RefreshNeighbors(AdjacentList& adjacent_list)
{
	// обнуляю счетчики вершин соседей
	for (auto &id_count : v_neighbors_) { id_count.count_points_ = 0; }
	// просматриваю пограничные вершины
	for (auto border_point: borders)
	{
		// просматриваю все соседние вершины
		for (auto point : adjacent_list[border_point].adjacent_points)
		{
			if (adjacent_list[point].owner_id_ == my_id_) continue;

			auto it = find_if(v_neighbors_.begin(),\
				v_neighbors_.end(), [&adjacent_list, &point](KingdomMapNeighbor& neighbor)->bool \
			{
				if (adjacent_list[point].owner_id_ == neighbor.neighbor_id_) // если сосед уже есть в списке
				{
					// проверяю есть ли вершина в списке рассмотренных 
					if (!neighbor.VertexExist(point))
					{
						// если не рассматривал эту вершину увеличиваю счетчик вершин соседей
						++neighbor.count_points_;
						// и добавляю в список рассмотренных
						neighbor.v_viewed_points_.push_back(point);
					}
					return true;
				}
				return false;
			}
			);
			// сравниваю владельца вершины со списком соседей
			if(it==v_neighbors_.end())
			{
				// если не найден то добваляю в список
				KingdomMapNeighbor kmn(adjacent_list[point].owner_id_, point);
				v_neighbors_.push_back(kmn);
			}
		}
	}
}

MapGameObj::MapGameObj(unsigned width, unsigned height, unsigned seed):adjacent_list_(width,height), width_(width), height_(height), seed_(seed) {
	srand(seed_);
	for (MapPoint& mp : adjacent_list_) {
		free_points.push_back(&mp);
	}
}



bool MapGameObj::FreeSpace(){
//	static uint32_t maxIteration=100;
//	if(--maxIteration==0)return false;
	for(MapPoint p: adjacent_list_){
		if(p.owner_id_==-1) return true;
	}
	return false;
}

void MapGameObj::DjekstraPath(uint32_t start_vertex,uint32_t end_vertex, vector<uint32_t> &path){
	//считается что все вершины доступны иначе добавить вес ребра = бесконечности или др. промеж. варианты
uint32_t n=adjacent_list_.Size();
vector<uint32_t> dist(n, UINT32_MAX/2), parent(n);
dist[start_vertex] = 0; // start vertex
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
			const uint32_t len =1; // weigth edge
			if (dist[vertex] + len < dist[to]) {
				dist[to] = dist[vertex] + len;
				parent[to] = vertex;
			}
		}
	}
	//recover path to target from parent vector
	vector<uint32_t> tempPath;
	uint32_t currV=end_vertex;
	// until we reach starting vertex
	while(parent[currV]!=start_vertex){
		// recover parent
		tempPath.push_back(currV);
		currV = parent[currV];
	}
	// add starting vertex
	tempPath.push_back(start_vertex);
	for(uint32_t i=0;i<tempPath.size();++i){
		uint32_t temp= tempPath.back();
		path.push_back(temp);
		tempPath.pop_back();
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

void MapGameObj::RecoveryPath(uint32_t start_vertex, uint32_t end_vertex, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path) {
	if (parent[start_vertex][end_vertex] == start_vertex) {   
		path.push_back(start_vertex);
	}
	else {
		RecoveryPath(start_vertex, parent[start_vertex][end_vertex], parent, path);
		RecoveryPath(parent[start_vertex][end_vertex], end_vertex, parent, path);
	}
}

void MapGameObj::BalanceAreaByLine()
{
	if (list_kingdoms_.size() == 0) return;
	unsigned average_count = std::round(float(adjacent_list_.Size()) / list_kingdoms_.size()); // average count of points;
	// сортирую список королевств по возрастанию количества вершин
	std::sort(list_kingdoms_.begin(), list_kingdoms_.end(), [](KingdomMap lkdm, KingdomMap rkdm) { return lkdm.list_v.size() < rkdm.list_v.size(); });
	auto kingdMax = list_kingdoms_.end() - 1; // самое большое королевство
	auto kingCurrent = list_kingdoms_.begin(); // самое маленькое королевство
	int positive_line_moving_count = 0;
	int negative_line_moving_count = 0;
	int direction_line_moving = 1; // 1 or -1
	FigureCenter minCoord;
	FigureCenter maxCoord;
	LineParam line;
	std::vector<unsigned> path;
	std::vector<unsigned> line_path;
	unsigned count = 0;
	while (TerrainsDisbalanced(1)) {
		++count;
		//   у кингМакс болшье сред точек ? 
		if (kingdMax->list_v.size() <= average_count && kingdMax != list_kingdoms_.begin())
		{
			--kingdMax;
			positive_line_moving_count = 0;
			negative_line_moving_count = 0;
		}
		if (kingCurrent->list_v.size() >= average_count && kingCurrent != list_kingdoms_.end() - 1)
		{
			++kingCurrent;
			positive_line_moving_count = 0;
			negative_line_moving_count = 0;
		}
		// начало цикла:
		minCoord = GetFigureCenterOfMass(adjacent_list_, &(*kingCurrent));
		maxCoord = GetFigureCenterOfMass(adjacent_list_, &(*kingdMax));
		//   строю линию из центров королевств 
		line = LineParam(minCoord.x_, minCoord.y_, maxCoord.x_, maxCoord.y_);
		//	 смещаю линию почти перпендикулярно в одну из сторон и сохраняю количество смещений 

		if (direction_line_moving > 0 && positive_line_moving_count >= 0)
		{ // positive moving
			++positive_line_moving_count;
			LineParam new_line = line + positive_line_moving_count;
			line_path = GetPathByLine(new_line, adjacent_list_);
			path.clear();
			path = GetPathBetweenKingdomsByLine(line_path, kingCurrent->GetMyId(), kingdMax->GetMyId(), adjacent_list_);
			if (path.empty())
			{
				positive_line_moving_count = -1; // no path
				direction_line_moving = -1; // reverse direction
			}
		}

		if (direction_line_moving < 0 && negative_line_moving_count <= 0) 
		{
			--negative_line_moving_count;
			LineParam new_line = line + negative_line_moving_count;
			path.clear();
			line_path = GetPathByLine(new_line, adjacent_list_);
			path = GetPathBetweenKingdomsByLine(line_path, kingCurrent->GetMyId(), kingdMax->GetMyId(), adjacent_list_);
			if (path.empty())
			{
				negative_line_moving_count = 1; // no path
				direction_line_moving = 1; // reverse direction
			}


		}

		if (negative_line_moving_count > 0 && positive_line_moving_count < 0)
		{
			line_path = GetPathByLine(line, adjacent_list_);
			path.clear();
			path = GetPathBetweenKingdomsByLine(line_path, kingCurrent->GetMyId(), kingdMax->GetMyId(), adjacent_list_);
			positive_line_moving_count = 0;
			negative_line_moving_count = 0;
			direction_line_moving = 1;
		}
		PushPullPoint(path, kingCurrent->GetMyId(), kingdMax->GetMyId());
	}
}

void MapGameObj::PushPullPoint(std::vector<unsigned>& path, unsigned minId, unsigned maxId)
{
	if (adjacent_list_[*path.begin()].owner_id_ == minId)
	{
		reverse(path.begin(), path.end());
	}
	uint32_t prevNumPoint = 0;
	vector<KingdomMap>::iterator prevKingd = list_kingdoms_.end();
	for (uint32_t NumPoint : path) {
		// если текущий владелец отличается от владельца предыдущей точки меняю владельца точки
		auto owner = adjacent_list_[NumPoint].owner_id_;
		vector<KingdomMap>::iterator currentKingd = find_if(list_kingdoms_.begin(), list_kingdoms_.end(), [owner](KingdomMap& kingd) { return owner == kingd.GetMyId(); });																																						   //NumCurrentTerr = adjacent_list_[NumPoint].owner_id_;
		if (prevKingd != list_kingdoms_.end() && currentKingd->GetMyId() != prevKingd->GetMyId()) {
			// найти предыдущ terrain и убрать у него точку из списка   find_if

			// нахожу текущую точку(указатель на нее) у предыдущего королевства

			vector<uint32_t>::iterator prevPointIt = find_if(prevKingd->list_v.begin(), prevKingd->list_v.end(), [prevNumPoint](uint32_t& pnt) { return prevNumPoint == pnt; });
			prevKingd->list_v.erase(prevPointIt); // удалил вершину из пред списка
			currentKingd->list_v.push_back(prevNumPoint); // добавил вершину в текущ список 
			prevKingd = currentKingd;
			adjacent_list_[prevNumPoint].owner_id_ = currentKingd->GetMyId(); // присвоил вершину окончательно в списке смежности
		}
		prevNumPoint = NumPoint;
		prevKingd = currentKingd;
	}
	for (auto& kingd : list_kingdoms_)kingd.RefreshBorders(adjacent_list_);
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
		// first start FloydWarhsalPath with reset true to reset parentsMatrixs 
		FloydWarhsallPath(kingdMin.borders[0], kingdMax.borders[0], true);
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
			auto owner = adjacent_list_[NumPoint].owner_id_;
			vector<KingdomMap>::iterator currentKingd = find_if(list_kingdoms_.begin(), list_kingdoms_.end(), [owner](KingdomMap& kingd) { return owner == kingd.GetMyId(); });																																						   //NumCurrentTerr = adjacent_list_[NumPoint].owner_id_;
			if (currentKingd->GetMyId() != prevKingd->GetMyId()){
				// найти предыдущ terrain и убрать у него точку из списка   find_if
				
				// нахожу текущую точку(указатель на нее) у предыдущего королевства
				
				vector<uint32_t>::iterator prevPointIt = find_if(prevKingd->list_v.begin(), prevKingd->list_v.end(), [prevNumPoint](uint32_t& pnt) { return prevNumPoint == pnt; }); 
				prevKingd->list_v.erase(prevPointIt); // удалил вершину из пред списка
				currentKingd->list_v.push_back(prevNumPoint); // добавил вершину в текущ список 
				prevKingd = currentKingd; 
				adjacent_list_[prevNumPoint].owner_id_ = currentKingd->GetMyId(); // присвоил вершину окончательно в списке смежности
			}
			prevNumPoint = NumPoint;
		}
		for(auto & kingd : list_kingdoms_)kingd.RefreshBorders(adjacent_list_);
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
	unsigned number = 0;
	if (free_points.size() != 1) {
		number = rand() % free_points.size();
	} 
	unsigned kingdom_start_number = adjacent_list_.GetNum(free_points[number]->GetCoord());
	adjacent_list_[kingdom_start_number].owner_id_ = by_id;
	list_kingdoms_.push_back(KingdomMap(kingdom_start_number, by_id));
	std::vector<MapPoint*>::iterator it = free_points.begin() + number;
	free_points.erase(it);
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

void MapGameObj::GenerateMap(){
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
				if(adjacent_list_[numV].owner_id_==-1){
					adjacent_list_[numV].owner_id_=kingd.GetMyId();
					kingd.list_v.push_back(numV);
					break; // quit if ok
				}
			}
			++iterOnBorders[kingd.GetMyId() ]; 	 // перемещаем итератор
		}	
		for(auto & kingd : list_kingdoms_) kingd.RefreshBorders(adjacent_list_);
	}	
	BalanceArea();
}

void MapGameObj::GenerateMapByLine() {
	if (list_kingdoms_.size() == 0) return;
	vector<uint32_t> iterOnBorders;		// список текущего положения итератора перебора 
					//по пограничным вершинам для всех королевств ( массив итераторов по одному на королевство)
	for (uint32_t i = 0; i < list_kingdoms_.size(); ++i) iterOnBorders.push_back(0);  //  установка начального значения итератора на 0

	while (FreeSpace()) {// пока свободные клетки не закончатся
	//Обход
		for (auto& kingd : list_kingdoms_) {
			// движение по окружности границы по их порядку начиная с правой
			if (iterOnBorders[kingd.GetMyId()] >= kingd.borders.size()) {
				iterOnBorders[kingd.GetMyId()] = 0;  // если итератор вышел за 
										//"границы королевства" то возвращаем на стартовую поз
			}
			//  если заграничная точка ничья то присваиваем (только 1)
			//  далее прохожу по границе numV - номер заграничной вершины(точки)
			// двигаюсь по списку смежности - по смежным вершинам вершины "tabSmej[kingd.borders[iterOnBorders[i]]]"
			for (uint32_t numV : adjacent_list_[kingd.borders[iterOnBorders[kingd.GetMyId()]]].adjacent_points) {
				if (adjacent_list_[numV].owner_id_ == -1) {
					adjacent_list_[numV].owner_id_ = kingd.GetMyId();
					kingd.list_v.push_back(numV);
					break; // quit if ok
				}
			}
			++iterOnBorders[kingd.GetMyId()]; 	 // перемещаем итератор
		}
		for (auto& kingd : list_kingdoms_) kingd.RefreshBorders(adjacent_list_);
	}
	BalanceAreaByLine();
}

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

unsigned AdjacentList::GetWidth()
{
	return width_;
}

unsigned AdjacentList::GetHeight()
{
	return height_;
}

unsigned AdjacentList::GetNum(unsigned x, unsigned y) {// получение номера вершины по координатам
	return x + y * width_;
}

unsigned AdjacentList::GetNum(std::pair<unsigned, unsigned> coord) {// тоже но через пару
	return coord.first + coord.second * width_;
}


pair<uint32_t, uint32_t> AdjacentList::GetCoord(uint32_t Num) {
	uint32_t x = Num - (Num / width_) * width_;
	uint32_t y = Num / width_;
	return make_pair(x, y);
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




FigureCenter GetFigureCenterOfMass(AdjacentList& adjlist, KingdomMap* kingd)
{
	// Xc and Yc are the coordinates of the center of mass of the figure
	// Xc=(x1*S1 + x2*S2 + ... +xn*Sn)/(S1+S2+...Sn) where x1 - is X coordinate 
	// and S1 - square of figure (always S1=1, S2=1, ... Sn=1)
	// 	  so Xc=(x1*1 + x2*2 + ... xn*1)/ n = sum of coord x / count vertex
	// similarly, we find Yc coord
	unsigned Sum_of_coord_x = 0, Sum_of_coord_y = 0;
	for (auto vertex : kingd->list_v) {
		Sum_of_coord_x += adjlist[vertex].GetCoord().first; // add x coord to summ
		Sum_of_coord_y += adjlist[vertex].GetCoord().second; // add y coord to summ
	}
	float Xc = (float)Sum_of_coord_x / kingd->list_v.size();
	float Yc = (float)Sum_of_coord_y / kingd->list_v.size();
	return FigureCenter(Xc, Yc);
}


std::vector<unsigned> GetPathByLine(LineParam& line, AdjacentList& adj)
{
	vector<unsigned> path;
	unsigned max_x = adj.GetWidth();
	int y = 0, y_old = line.GetCoordinateY(0);
	if(std::abs(line.k_) == INFINITY)
		{
		unsigned max_y = adj.GetHeight();
		int x = std::roundf( float(line.C_) / line.A_) * (-1);
		if (x >= adj.GetWidth() || x < 0) return path;
		for (unsigned y = 0; y < max_y; ++y) {
			path.push_back(adj.GetNum(x, y));
		}
		return path;
	}
	// moving coordiantes x from 0 to max_x
	for (unsigned x = 0; x < max_x; ++x) {
		y = line.GetCoordinateY(x);
		if (y < 0) 
		{
			y = 0;
			path.push_back(adj.GetNum(x, y));
			y_old = y;
			continue;
		}
		if (y >= adj.GetHeight())
		{
			y = adj.GetHeight() - 1;
			path.push_back(adj.GetNum(x, y));
			y_old = y;
			continue;
		}
		//if (y >= adj.GetHeight() || y < 0) continue;
		if (y != y_old && y_old <adj.GetHeight()) { // detecting diagonal and vertical  moving
			while (y != y_old)
			{
				if (y_old < y)
				{
					++y_old;
				}
				else
				{
					--y_old;
				}
				path.push_back(adj.GetNum(x - 1, y_old)); // add additionals points in path

			}
		}
		path.push_back(adj.GetNum(x, y));
		y_old = y;
	}
	return path;
}


std::vector<unsigned> GetPathBetweenKingdomsByLine(std::vector<unsigned>& path_by_line, const unsigned first_id, const unsigned second_id, AdjacentList adj)
{

	// TODO: при появлении других id между first id и second id алгоритм не находит стартовой вершины
	if (path_by_line.empty()) return std::vector<unsigned>();
	if (first_id == second_id) return std::vector<unsigned>();
	std::vector<unsigned> path;
	unsigned previous_owner_id = UINT_MAX, previous_vertex =0;
	for (int i=0; i<path_by_line.size(); ++i)	// find start 
	{
		unsigned vertex = path_by_line[i]; 
		unsigned current_id = adj[vertex].owner_id_;
		if (previous_owner_id != current_id && ( previous_owner_id == first_id || previous_owner_id == second_id))
		{
			path.push_back(previous_vertex);
			path.push_back(vertex);
			unsigned target = UINT_MAX;
			previous_owner_id == first_id ? target = second_id : target = first_id;
			while (adj[vertex].owner_id_ != target)
			{
				++i;
				if (i >= path_by_line.size()) { // if target not found  function return empty vector<>()
					path.clear();
					break;
				}
				vertex = path_by_line[i];
				path.push_back(vertex);

			}
			break; // out of cicle for
		}
		previous_owner_id = adj[vertex].owner_id_;
		previous_vertex = vertex;
	}
	return path;
}


LineParam::LineParam(int x1, int y1, int x2, int y2)
{
	A_ = y2 - y1;
	B_ = x1 - x2;
	C_ = (-1) * x1 * A_ + y1 * (x2 - x1);
	k_ = float(A_) / B_ * (-1.0);
	b_ = C_ / B_ * (-1.0);
	l_ = float(B_) / A_ * (-1.0);
	c_ = C_ / A_ * (-1.0);
}

LineParam::LineParam(int a, int b, float c) :A_(a), B_(b), C_(c), k_(0.0), b_(0.0), l_(0.0), c_(0)
{
	k_ = float(A_) / B_ * (-1.0);
	b_ = C_ / B_ * (-1.0);
	l_ = float(B_) / A_ * (-1.0);
	c_ = C_ / A_ * (-1.0);
}

LineParam::LineParam():A_(0),B_(0),C_(0.0),k_(0.0),b_(0.0),l_(0.0),c_(0)
{
	
}

unsigned LineParam::GetCoordinateY(unsigned x)
{
	return static_cast<unsigned>(round(x * k_ + b_));
}

// TODO: return new LineParam !!!
void LineParam::Move(int line_moving_coord)
{ // if line_moving_coord =0 // no moving if even + direction, odd -direction
	if (line_moving_coord != 0)
	{
		if (k_ <= 1.0 && k_ >= -1.0)
		{
			// moving by change Y coord
			b_ += line_moving_coord;
			C_ = B_ * b_ * (-1.0);
			c_ = C_ / A_ * (-1.0);
		}
		else
		{
			// moving by change X coord
			c_ += line_moving_coord ;
			// calculation other param k_, b_
			C_ = c_ * A_ * (-1.0);
			b_ = C_ / B_ * (-1.0);
		}
	}
}

LineParam LineParam::operator+(const int count)
{
	LineParam line = *this;
	line.Move(count);
	return line;
}

LineParam& LineParam::operator=(const LineParam& other)
{
	this->A_ = other.A_;
	this->B_ = other.B_;
	this->C_ = other.C_;
	this->c_ = other.c_;
	this->l_ = other.l_;
	this->k_ = other.k_;
	this->b_ = other.b_;
	return *this;
}

PointParametr::PointParametr(int x, int y): x_(x), y_(y)
{

}

