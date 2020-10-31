#include <iostream>
#include <CImg.h>
#include<vector>

using namespace std;
class point{
	public:
		vector<uint32_t> smej; // смежные точки 
		vector<uint8_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам
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
	uint64_t max=height*width;
	uint32_t w=0,h=0;
	point pNull;
	// заполняем таблицу нулевыми точками
	for(uint64_t i=0;i<max;++i){
		tabSmej.push_back(pNull);
	}
	// заполняем таблицу смежности
for(uint64_t i=0;i<max;++i){
	// просматриваю таблицу вправо вниз добавляю 
	// к текущей точке следущую смежную и к следующей текущую
	
	// проверка правой границы
	if(w<width-1){
		tabSmej[i].smej.push_back(i+1);
		tabSmej[i+1].smej.push_back(i); 
	}
	// нижней границы
	if(h<height-1){
		tabSmej[i].smej.push_back(i+width);
		tabSmej[i+width].smej.push_back(i);
	}
	// опредление координаты на карте
	++w;
	if(w==width){
	w=0;
	++h;
	}
	if(h>=height) { cout << " Error ... Generate_tab .."; break;}
	}
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
			// создаем таблицу смежности
			Generate_tab();
			// определяем положения точек
			Generate_coord(p);
			// заполняем территорию карты
			//FillMap();
		}
		void PrintTabSmej(){
			uint32_t i=0;
			for(point p:tabSmej){
				cout << i <<" num smej:"<< p.smej.size() << endl;
				++i;
				for(uint32_t v: p.smej){
				cout << v <<" " ;
				}
			cout << endl;
			}
		}
};


int main(){
	cout<< " test "<< endl;
	map m(5,5,25);
	m.PrintTabSmej();


}
