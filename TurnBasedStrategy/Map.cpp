#include <iostream>
#include <CImg.h>
#include <vector>

using namespace std;
class point{
	public:
		vector<uint32_t> smej; // смежные точки 
		vector<uint8_t> list_neighbor; // смежные точки принадлежащие другим игровым объектам
		bool border_map;
		uint16_t N_owner;
	point(){
	border_map=false;
	N_owner=0;
	cout<< " point constructed owner="<<N_owner<<endl;
	}
};

class map{
	private:
		uint32_t width,height;
		vector<pair<uint32_t,uint32_t>> points;
		vector<point> tabSmej; // таблица смежности представляет из себя список всех вершин

	public:
	private:
		//  генерирует вектор координат ( ВНИМАНИЕ  повторяющихся)
void GenerateCoord(uint32_t p){
			for(uint32_t i=0;i<p;i++){
				int32_t cx=0,cy=0;
				cx=rand()%width;
				cy=rand()%height;
				cout<< "cx="<<cx<<" cy="<<cy<<endl;
			points.push_back(std::make_pair(cx,cy));
			}
}

void GenerateTab(){
	uint64_t max=height*width;
	uint32_t w=0,h=0;
	point pNull;
	pNull.N_owner=0;
	cout<<"pnull owner="<<pNull.N_owner<<endl;
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
	cout << "i="<<i<<" w="<<w<<" h="<<h<<endl;
	++w;
	if(w==width){
	w=0;
	++h;
	}
	}
}

// обновление границ
void RefreshBorders(){

}
// генерация и добавление начальных точек к карте
void AddPoitsToMap( uint32_t po){ // ро - количество стартовых точек
	if(po>height*width) return;
	while(po>0){
		uint32_t x=rand()%width;
		uint32_t y=rand()%height;
		if(tabSmej[x+y*width].N_owner==0){
			tabSmej[x+y*width].N_owner=po;
		}else{
			while(tabSmej[x+y*width].N_owner!=0){
		x=rand()%width;
		y=rand()%height;
			}
			tabSmej[x+y*width].N_owner=po;
		}
		--po;
	}
}
// вывод на экран карты
void MapToScreen(){
		// проходим по всем вершинам и форматируем в виде таблицы heigth x width
uint32_t k=0;
	for(uint32_t j=0;j<height;++j){
		for(uint32_t i=0;i<width;++i){
			cout << tabSmej[k].N_owner<<" . ";
			++k;
		}
		cout<<endl;
	}
}
// функц вывода карты в файл с помощью CImg.h
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
			// создаем таблицу списков смежности
			cout<<" gen tab\n";
			GenerateTab();
			cout<<"map to scre\n";
			MapToScreen();
			AddPoitsToMap(10); 
			cout<<"poins scre\n";
			MapToScreen();
			// определяем положения точек
		//	GenerateCoord(p);
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
//	m.PrintTabSmej();


}
