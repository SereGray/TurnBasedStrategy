#include <iostream>
#include <CImg.h>
#include<vector>

using namespace std;
class point{
	public:
		vector<uint32_t> smej;
		vector<uint8_t> list_neighbor;
		uint8_t N_owner=0;
};

class map{
	private:
		uint32_t width,height;
		vector<pair<uint32_t,uint32_t>> points;
		vector<point> tabSmej;
	public:
	private:
		void Generate_coord(uint32_t p){
			for(uint32_t i=0;i<p;i++){
				int32_t cx=0,cy=0;
				cx=rand()%width;
				cy=rand()%height;
				cout<< "cx="<<cx<<" cy="<<cy<<endl;
			points.push_back(std::make_pair(cx,cy));
			}
		}
void Generate_tab(){
// таблица смежности
}

		void FillMap(){
			while(1){// пока свободные клетки не закончатся
				//1)обход окружности точек
				//добавление незанятых (окрашивание)
				//2)опр новых границ		
				}
			//Если площади областей не равны то
			//сортируем 
			//цикл пока не равны
			//берем самую маленькую площадь(выбираем точку на гранце)
			//строим цепочку до самой большой
			//тянем к себе точки
			//
			

		}
	public:
		vector<uint32_t> list_smej;
		map(uint32_t w,uint32_t h, uint32_t p): width(w), height(h){
			Generate_tab();
			Generate_coord(p);


			//FillMap();
		}
};


int main(){
	cout<< " test "<< endl;
	map m(100,100,25);


}
