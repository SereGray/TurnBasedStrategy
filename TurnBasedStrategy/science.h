#ifndef SCIENCE 
#define SCIENCE
#include "TbsInterface.h"
#include "Engine.h"
#include <string>
#include <vector>
#include <memory>

//  общая наука - уровень общей науки определяет скорость развития предметных областе науки 
class TheScience{
	// класс наука
	public:
		// TODO: проверить что прирост идет у предметной области а не у всей
	static unsigned scienceLvl; //общий научный уровень 
	std::string name; // name 
        private:	
	unsigned progress;    // количество работы ученых над текущим уровнем
	unsigned progressLimit; // макс прогресс для этого уровняя (если больше то повыш ур.)
	float scienistForce; // сколько прогресса добавляет один ученый
	void Increase(unsigned scienist_count); // увеличение науки 
};

// предметная наука - скорость(сила) прироста параметра в конкретной области
class SubjectScience: public TheScience{
	public:
		unsigned science_lvl;// уровень конкретной предметной отрасли

};

// игровой объект наука
class ScienseObject: public TbsInterface, public EngineGameObjInterface{
	public:
		ScienseObject(){
			// science_vector= add demography incrase, demography density,  ...
		}
	private:
		void NextTurn(); // расчет сл хода
	// the_science base_science(); // базовая наука
	// пример :std::unique_ptr<the_science> scns(new the_science);
	std::vector<std::unique_ptr<SubjectScience>> science_vector; // список наук
};

#endif
