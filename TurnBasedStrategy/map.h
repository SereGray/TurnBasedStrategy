/*
* Карта хранит положение королевств и осуществляет передачу земель друг другу
* Определяет соседей
*/
#ifndef MAP
#define MAP

#include <iostream>
#include "CImg.h"
#include <vector>
#include <algorithm>
#include "engine.h"

using namespace std;

class MapPoint{
	uint32_t x,y; //   TODO: не инициализированны
	public:

		MapPoint(){
			border_map=false;
			N_owner=0;
		}

		vector<uint32_t> adjacent_points; // смежные точки 
		vector<uint32_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам                        NULL 
		bool border_map;
		uint16_t N_owner;
		pair<uint32_t,uint32_t> GetCoord();
		void SetX(uint32_t X);
		void SetY(uint32_t Y);
};

class MapTerrain{ //  клас предсавляющий изображение на карте территорию королевства и методы работы:
	public:
		uint32_t N;
		vector<uint32_t> list_v; // список вершин
		vector<uint32_t> borders; // список границ 
		// создание экземпляра из первой точки
		MapTerrain(uint32_t num,uint32_t n){
			N=n;
			list_v.push_back(num);
			borders.push_back(num);
		}
		uint32_t my_N();
};

class Map: public EngineGameObjInterface{
	public:
		vector<MapPoint> adjacentList; // таблица смежности представляет из себя список всех вершин
		vector<MapTerrain> list_terrains;
	private:
		uint32_t width,height;
	public:
		void SaveState();
		void LoadState();
		void CreateState();
		// переход территории от одного владельца к другому
		void ExchangeArea(); 
		// получить писок соседей 
		vector<uint32_t> GetNeighborsList(uint32_t my_N);
		// получить цвет территории
		uint32_t GetColor(); // color is  +8empty bits +RGB 24b ( 8-8-8 bit)
		Map(uint32_t w, uint32_t h, uint32_t p);
		void PrintTabSmej();
		void ToFile(uint8_t);
		void MapToScreen();
	private:
		void NextTurn(); // TODO:this
		unsigned GetCountSpecialists(); // must return 0
		void FillMap();
		MapTerrain GetMinTerrain();
		bool TerrainsDisbalanced(uint32_t offset);
		void BalanceArea(); 
		vector<uint32_t> FloydWarhsallPath(uint32_t start , uint32_t end, bool restart ); 
		void FloydWarshall(vector<vector<uint32_t>> & parentsMatrix);
		void RecoveryPath(uint32_t a, uint32_t b, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
		void AdjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);
		void CreateDxDTable( vector<vector<uint32_t>> & inDxD);
		void DjekstraPath(uint32_t numBorderV,uint32_t numTargetV, vector<uint32_t> &path);
		bool FreeSpace();
		void RefreshBorders(MapTerrain & terr);
		void AddPoitsToMap( uint32_t po);
		void GenerateTab();
		pair<uint32_t, uint32_t> GetCoord(uint32_t Num);
		uint32_t GetNum(uint32_t x, uint32_t y);
};

#endif
