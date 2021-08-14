/*
* Карта хранит положение королевств и осуществляет передачу земель друг другу
* Определяет соседей
*/
#ifndef MAP
#define MAP

#include <iostream>
#include <vector>
#include <algorithm>
//#include <cmath>
#include "engine.h"
#include "utility.h"

using namespace std;

class AdjacentList;
class KingdomMap;

struct PointParametr {
	//int x_, y_;
	// radial coordinat system
	float angle_;
	float radius_;
	PointParametr(float angle, float radius) :angle_(angle), radius_(radius) {};
};

struct LineParameter {
	// y = x * k + b
	float k_;  // to RIGTH line increase, to LEFT decrease
	float b_;	// to DOWN line increase, or to UP line decrease
	// radial coordinat system
	float angle_;
	float radius_;
	LineParameter(float k, float b);
	unsigned GetCoordinateY(unsigned x);
};

struct FigureCenter {
	float x_;
	float y_;
	FigureCenter(float x, float y) :x_(x), y_(y) {};
};

// finds the Line parameters k and b  (y=x*k + b)
LineParameter  GetLineParameters(int& Point1_x, int& Point1_y, int& Point2_x, int& Point2_y);
LineParameter  GetLineParameters(float& Point1_x, float& Point1_y, float& Point2_x, float& Point2_y);

// finds point coord by LineParameters in radial coord sys 
// by angle
PointParametr GetPointOnLine(LineParameter &line, float &angle);

// finds point angle coord by LineParameters in radial coord sys 
// by radius
std::pair<float,float> GetAngleCoordOfPoint(LineParameter &line, float &radius);

// finds the center of mass of a figure on the map
FigureCenter GetFigureCenterOfMass(AdjacentList& adjlist, KingdomMap* kingd);

// return path (vertex numbers sequence) by line
std::vector<unsigned> GetPathByLine(LineParameter& line, AdjacentList& adj);

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
		KingdomMap(unsigned num, unsigned my_id);
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
	public:
		MapGameObj(unsigned width, unsigned height, unsigned seed);
		void AddKingdom(unsigned by_id);
		void GenerateMap();
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
	void HeuristicBalanceArea();
	void SpeedBalanceArea();
	void FloydWarshall(vector<vector<uint32_t>> & parentsMatrix); 
	void RecoveryPath(uint32_t start_vertex, uint32_t end_vertex, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
	void AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);

};

#endif
