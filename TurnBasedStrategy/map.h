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

using namespace std;

class MapPoint{
	unsigned x_ ,y_; //   TODO: не инициализированны
	public:

		MapPoint():x_(0), y_(0){
			border_map=false;
			N_owner=-1; // -1  point is free		
		}

		vector<uint32_t> adjacent_points; // смежные точки 
		vector<uint32_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам                        NULL 
		bool border_map;
		int N_owner;
		pair<uint32_t,uint32_t> GetCoord();
		void SetX(uint32_t X);
		void SetY(uint32_t Y);
};

class KingdomMap{ //  клас предсавляющий изображение на карте территорию королевства и методы работы:
	public:
		unsigned my_id_; // TODO: SET ID
		vector<unsigned> list_v; // список вершин
		vector<unsigned> borders; // список границ 
		// создание экземпляра из первой точки
		KingdomMap(uint32_t num, uint32_t my_id);
		unsigned GetMyId();
		unsigned MyArea(); // TODO:this
};

class MapGameObj: public EngineGameObjInterface{
	public:
		vector<MapPoint> adjacent_list_; // таблица смежности представляет из себя список всех вершин
		vector<KingdomMap> list_kingdoms_;
	private:
		virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
		uint32_t width_,height_;
	public:
		uint32_t AreaKingdom(uint32_t); //TODO: ?
		// переход территории от одного владельца к другому
		// return summaries
		std::string ExchangeArea(int balance, unsigned first_kd_id, unsigned first_count_solders, unsigned second_kd_id, unsigned second_count_solders); //TODO:this
		// получить писок соседей 
		vector<uint32_t> GetNeighborsList(uint32_t my_id);
		// получить цвет территории
		uint32_t GetColor(); // color is  +8empty bits +RGB 24b ( 8-8-8 bit)
	
		MapGameObj(uint32_t w, uint32_t h, uint32_t p);

		void PrintTabSmej();

#ifdef CIMG
		void ToFile(uint8_t);
#endif // CIMG
		void MapToScreen();
	private:
		void SaveState();
		void LoadState();
		void CreateState();
		void NextTurn(); // TODO:this, maybe empty?
		std::string GetSummariesString(); // сводки за предыдущий ход // TODO:this
		unsigned GetCountSpecialists(); // must return 0

		void FillMap();
		KingdomMap GetMinTerrain();
		bool TerrainsDisbalanced(uint32_t offset);
		void BalanceArea(); 
		vector<uint32_t> FloydWarhsallPath(uint32_t start , uint32_t end, bool restart ); 
		void FloydWarshall(vector<vector<uint32_t>> & parentsMatrix);
		void RecoveryPath(uint32_t a, uint32_t b, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
		void AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);
		void CreateDxDTable( vector<vector<uint32_t>> & inDxD);
		void DjekstraPath(uint32_t numBorderV,uint32_t numTargetV, vector<uint32_t> &path);
		bool FreeSpace();
		void RefreshBorders(KingdomMap & terr);
		void AddStartPoitsToMap( uint32_t po);
		void GenerateTab();
		pair<uint32_t, uint32_t> GetCoord(uint32_t Num);
		unsigned GetNum(unsigned x, unsigned y);
		unsigned GetNum(std::pair<unsigned, unsigned> coord);
};

#endif
