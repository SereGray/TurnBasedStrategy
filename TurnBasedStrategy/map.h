/*
* Карта хранит положение королевств и осуществляет передачу земель друг другу
* Определяет соседей
*/
#ifndef MAP
#define MAP

//#define CIMG

#ifndef CIMG
//#include "CImg.h" deleted
#endif // CIMG

#include <iostream>
#include <vector>
#include <algorithm>
#include "engine.h"
#include "utility.h"

using namespace std;

class MapPoint{
	unsigned x_ ,y_; //   TODO: не инициализированны
public:
	vector<uint32_t> adjacent_points; // смежные точки 
	vector<uint32_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам                        NULL 
	bool border_map;
	int N_owner;

	MapPoint();
	pair<uint32_t,uint32_t> GetCoord();
	void SetX(uint32_t X);
	void SetY(uint32_t Y);
};

class AdjacentList {
	vector<MapPoint> v_adjacent_list;
	unsigned width_, height_;
	unsigned long long max;

public:
	AdjacentList(unsigned width, unsigned height);
	MapPoint& operator[](std::size_t index);
	unsigned Size();
	std::vector<MapPoint>::iterator begin();
	std::vector<MapPoint>::const_iterator begin() const;
	std::vector<MapPoint>::const_iterator cbegin() const;
	std::vector<MapPoint>::iterator end();
	std::vector<MapPoint>::const_iterator end() const;
	std::vector<MapPoint>::const_iterator cend() const;
};

class KingdomMap{ //  клас предсавляющий изображение на карте территорию королевства и методы работы:
	unsigned my_id_;
	public:
		vector<unsigned> list_v; // список вершин
		vector<unsigned> borders; // список границ 
		// создание экземпляра из первой точки
		KingdomMap(unsigned num, unsigned my_id);
		unsigned GetMyId();
		unsigned MyArea(); // TODO:this
		void RefreshBorders(AdjacentList &  adjacent_list);
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

	pair<uint32_t, uint32_t> GetCoord(uint32_t Num);
	unsigned GetNum(unsigned x, unsigned y);
	unsigned GetNum(std::pair<unsigned, unsigned> coord);


	bool TerrainsDisbalanced(uint32_t offset);
	void BalanceArea(); 
	void FloydWarshall(vector<vector<uint32_t>> & parentsMatrix); 
	void RecoveryPath(uint32_t start_vertex, uint32_t end_vertex, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
	void AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);

};

#endif
