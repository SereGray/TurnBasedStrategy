#ifndef SCIENCE 
#define SCIENCE
#include "TbsInterface.h"
#include <string>
#include <vector>
#include <memory>

//  общая наука - уровень общей науки определяет скорость развития предметных областе науки 
class the_science{
	// класс наука
	public:
		// TODO: проверить что прирост идет у предметной области а не у всей
	static unsigned science_lvl; //общий научный уровень 
	std::string name; // name 
        private:	
	unsigned progress;    // количество работы ученых над текущим уровнем
	unsigned progress_limit; // макс прогресс для этого уровняя (если больше то повыш ур.)
	float scienist_force; // сколько прогресса добавляет один ученый
	void increase(unsigned scienist_count); // увеличение науки 
};

// предметная наука - скорость(сила) прироста параметра в конкретной области
class subject_science: public the_science{
	public:
		unsigned science_lvl;// уровень конкретной предметной отрасли

};

// игровой объект наука
class sciense_object: public TbsInterface{
	// the_science base_science(); // базовая наука
	// пример :std::unique_ptr<the_science> scns(new the_science);
	std::vector<std::unique_ptr<subject_science>> science_vector; // список наук
};

#endif
