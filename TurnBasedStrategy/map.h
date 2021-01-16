
#ifndef MAP
#define MAP

#include <iostream>
#include "CImg.h"
#include <vector>
#include <algorithm>
#include "Engine.h"

using namespace std;

class point{
	uint32_t x,y; //   TODO: не инициализированны
	public:

		point(){
			border_map=false;
			N_owner=0;
		}

		vector<uint32_t> adjacentPoints; // смежные точки 
		vector<uint32_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам                        NULL 
		bool border_map;
		uint16_t N_owner;
		pair<uint32_t,uint32_t> getCoord();
		void setX(uint32_t X);
		void setY(uint32_t Y);
};

class terrain{ //  клас предсавляющий изображение на карте территорию королевства и методы работы:
	public:
		uint32_t N;
		vector<uint32_t> list_v; // список вершин
		vector<uint32_t> borders; // список границ 
		// создание экземпляра из первой точки
		terrain(uint32_t num,uint32_t n){
			N=n;
			list_v.push_back(num);
			borders.push_back(num);
		}
		uint32_t my_N();
};

class map: public EngineGameObjInterface{
	private:

		uint32_t width,height;
	public:
		vector<point> adjacentList; // таблица смежности представляет из себя список всех вершин
		vector<terrain> list_terrains;
	private:
void NextTurn(); // TODO:this
unsigned GetCountSpecialists(); // must return 0
void FillMap();
terrain get_minTerrain();
bool terrainsDisbalanced(uint32_t offset);
void BalanceArea(); 
vector<uint32_t> Floyd_Warhsall_Path(uint32_t start , uint32_t end, bool restart ); 
void Floyd_Warshall(vector<vector<uint32_t>> & parentsMatrix);
void recoveryPath(uint32_t a, uint32_t b, vector<vector<uint32_t>> & parent, vector<uint32_t>  & path);
void adjacentMatrixFill(vector<vector<uint32_t>> & inMatrix);
void createDxDTable( vector<vector<uint32_t>> & inDxD);
void DjekstraPath(uint32_t numBorderV,uint32_t numTargetV, vector<uint32_t> &path);
bool freeSpace();
void RefreshBorders(terrain & terr);
void AddPoitsToMap( uint32_t po);
void GenerateTab();
pair<uint32_t, uint32_t> getCoord(uint32_t Num);
uint32_t getNum(uint32_t x, uint32_t y);

	public:
		map(uint32_t w,uint32_t h, uint32_t p): width(w), height(h){
			// создаем таблицу списков смежности
			cout<<" gen tab\n";
			GenerateTab();
			cout<<"map to scre\n";
			AddPoitsToMap(p); 
			cout<<"poins scre\n";
			MapToScreen();
			// заполняем территорию карты
			FillMap();
			cout << endl;
			MapToScreen();
			// Выравниваю карту на 1 пиксель
			BalanceArea();
			cout << "Balancing ...\n";
			MapToScreen();
}
void PrintTabSmej();	 
void toFile(uint8_t);
void MapToScreen();

};

#endif
