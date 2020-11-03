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
	}
};

class kingdoom{ //  клас struct? предсавляющий изображение на карте территорию королевства и методы работы:
	public:
		vector<uint32_t> list_v; // список вершин
		vector<uint32_t> borders; // список границ 
		kingdoom(uint32_t num){
			list_v.push_back(num);
			borders.push_back(num);
		}
	};
class map{
	private:
		uint32_t width,height;
		vector<pair<uint32_t,uint32_t>> points;
		vector<point> tabSmej; // таблица смежности представляет из себя список всех вершин
		vector<kingdoom> list_kingdooms; // список королевств

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

uint32_t getNum(uint32_t x, uint32_t y){// получение номера вершины по координатам
	return x+y*width;
}
// получение координат вершины по номеру
pair<uint32_t,uint32_t> getCoord(uint32_t num){
//TODO: this features
}

void GenerateTab(){
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
	}
}


// генерация и добавление начальных точек к карте
void AddPoitsToMap( uint32_t po){ // ро - количество стартовых точек
	if(po>height*width) return;
	while(po>0){
		uint32_t x=rand()%width;
		uint32_t y=rand()%height;
		if(tabSmej[x+y*width].N_owner==0){
			tabSmej[getNum(x,y)].N_owner=po;
		}else{
			while(tabSmej[getNum(x,y)].N_owner!=0){
		x=rand()%width;
		y=rand()%height;
			}
			tabSmej[getNum(x,y)].N_owner=po;
			kingdoom newKingdoom(getNum(x,y));
			list_kingdooms.push_back(newKingdoom);
		}
		--po;
	}
}
// обновление границ
	void RefreshBorders(kingdoom kingd){
		kingd.borders.clear();
		for(numV: kingd.list_v){// обходим все вершины королевства по номерам и пров
			//  условию границы
		//TODO:	if(tabSmej[numV].)
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
			AddPoitsToMap(p); 
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
	map m(5,5,3);
//	m.PrintTabSmej();


}
