/*
* Карта хранит положение королевств и осуществляет передачу земель друг другу
* Определяет соседей
*/
#ifndef MAP
#define MAP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "engine.h"
#include "utility.h"


using namespace std;

const double PI = 3.141592653589793238463;

class AdjacentList;
class KingdomMap;

struct PointParametr {
	// decart coordinat system
	int x_, y_;
	PointParametr(int x, int y);
};

struct LineParam {
	int A_, B_;
	float C_;    // line form Ax+By+C=0
	// y = x * k + b
	
	float k_;  // to RIGTH line increase, to LEFT decrease
	float b_;	// to DOWN line increase, or to UP line decrease

	LineParam(int x1, int y1, int x2, int y2);
	LineParam(int a, int b, float c);
	LineParam();
	unsigned GetCoordinateY(unsigned x);
	// offset the line in both directions alternately
	// line_moving_coord: 0 - no moving;
	// return true if offset done, false if offset unavailable
	LineParam operator+(const int count);
	LineParam& operator=(const LineParam& other);
private:
	// additional param
	// x = y * l + c
	float l_; 
	float c_;

	void Move(int line_moving_coord);
};


struct FigureCenter {
	float x_;
	float y_;
	FigureCenter(float x, float y) :x_(x), y_(y) {};
	FigureCenter() :x_(0.0), y_(0.0) {};
};


// finds the center of mass of a figure on the map
FigureCenter GetFigureCenterOfMass(AdjacentList& adjlist, KingdomMap* kingd);

vector<pair<unsigned, unsigned>> GetCoordOfCircle(unsigned &radius, unsigned &center_x, unsigned &center_y, unsigned &x_bound, unsigned &y_bound);

std::vector<unsigned> GetPathByLine(LineParam& line, AdjacentList& adj);
// return path as vector of vertex number

std::vector<unsigned> GetPathBetweenKingdomsByLine(std::vector<unsigned>& path_by_line,const unsigned firts_id, const unsigned second_id, AdjacentList adj);
// return path (vertex numbers sequence) betsween, allow vertex not own start or target kingdom, except first and last vertex

class MapPoint{
	unsigned x_ ,y_; //   TODO: не инициализированны
public:
	vector<uint32_t> adjacent_points; // смежные точки 
	bool border_map;
	int owner_id_;

	MapPoint();
	pair<uint32_t,uint32_t> GetCoord();
	void SetX(uint32_t X);
	void SetY(uint32_t Y);
};



class AdjacentList {
	vector<MapPoint> v_adjacent_list;
	unsigned width_, height_; // 1000000000 max ?
	unsigned long long max;

public:
	AdjacentList(unsigned width, unsigned height);
	MapPoint& operator[](std::size_t index);
	unsigned Size();
	unsigned GetWidth();
	unsigned GetHeight();
	pair<uint32_t, uint32_t> GetCoord(uint32_t Num);
	unsigned GetNum(unsigned x, unsigned y);
	unsigned GetNum(std::pair<unsigned, unsigned> coord);

	std::vector<MapPoint>::iterator begin() ;
	std::vector<MapPoint>::const_iterator begin() const ;
	std::vector<MapPoint>::const_iterator cbegin() const ;
	std::vector<MapPoint>::iterator end() ;
	std::vector<MapPoint>::const_iterator end() const ;
	std::vector<MapPoint>::const_iterator cend() const ;
};

// структура для учета и поиска соседей
struct KingdomMapNeighbor {
	unsigned neighbor_id_, count_points_;
	std::vector<unsigned> v_viewed_points_; // просмотренные точки
	KingdomMapNeighbor(unsigned id, unsigned viewed_vertex) :neighbor_id_(id), count_points_(1), v_viewed_points_({ viewed_vertex }) {};
	KingdomMapNeighbor() = delete;
	bool VertexExist(unsigned vertex)
	{
		return v_viewed_points_.end() != find(v_viewed_points_.begin(), v_viewed_points_.end(), vertex);
	}
};


class KingdomMap{ //  клас предсавляющий изображение на карте территорию королевства и методы работы:
	unsigned my_id_;
	public:
		vector<unsigned> list_v; // список вершин
		vector<unsigned> borders; // список границ 
		vector<KingdomMapNeighbor> v_neighbors_; // список id сосдей и количества контактирующих вершин
		// создание экземпляра из первой точки
		KingdomMap(unsigned my_id);
		KingdomMap(unsigned start_num, unsigned by_id);
		unsigned  GetMyId();
		unsigned MyArea(); // TODO:this
		void RefreshBorders(AdjacentList &  adjacent_list);
	private:
		void RefreshNeighbors(AdjacentList& adjacent_list);

};



class MapGameObj: public EngineGameObjInterface{
	public:
		AdjacentList adjacent_list_; // таблица смежности представляет из себя список всех вершин
		vector<KingdomMap> list_kingdoms_;
	private:
		virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
		unsigned width_,height_;
		unsigned seed_; // necessary to repeat the result of Map generation
		vector<MapPoint*> free_points;
	public:
		MapGameObj(unsigned width, unsigned height, unsigned seed);
		void AddKingdom(unsigned by_id);
		void GenerateMap();
		void GenerateMapByLine();
		KingdomMap* GetKingdomMap(unsigned by_id);
		uint32_t AreaKingdom(unsigned by_id); //TODO: ?

		// переход территории от одного владельца к другому
		// return summaries
		std::string ExchangeArea(int balance, unsigned first_kd_id, unsigned first_count_solders, unsigned second_kd_id, unsigned second_count_solders); //TODO:this
		vector<uint32_t> GetNeighborsList(uint32_t my_id); 		// получить писок соседей 
		uint32_t GetColor(); //  получить цвет территории color is  +8empty bits +RGB 24b ( 8-8-8 bit)

		void SaveState();
		void LoadState();
		void CreateState();
		void NextTurn(); // TODO:this, maybe empty?
		std::string GetSummariesString(); // сводки за предыдущий ход // TODO:this
		unsigned GetCountSpecialists(); // must return 0

private:
	// return path from start vertex to end vertex
	// if restart=true - reset parent matrix (need time)
	vector<uint32_t> FloydWarhsallPath(uint32_t start, uint32_t end, bool restart); 

	// return path from start vertex to end vertex  NOT USED NOW !!
	void DjekstraPath(uint32_t start, uint32_t end, vector<uint32_t>& path);

	// true if there is free space on the map
	bool FreeSpace();

	bool TerrainsDisbalanced(uint32_t offset);
	void BalanceArea(); 
	void BalanceAreaByLine();
	void PushPullPoint(std::vector<unsigned>& path, unsigned minId, unsigned maxId);
	void FloydWarshall(vector<vector<uint32_t>> & parentsMatrix); 
	void RecoveryPath(uint32_t start_vertex, uint32_t end_vertex, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
	void AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);

};

#endif
