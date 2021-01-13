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
		TheScience(std::string nameScience);
		// TODO: проверить что прирост идет у предметной области науки а не у всей
	static unsigned scienceLvl; //общий научный уровень 
	std::string name; // name 
        private:	
	unsigned	progress_;    // количество работы ученых над текущим уровнем
	unsigned	progress_limit_; // макс прогресс для этого уровняя (если больше то повыш ур.)
	float		scienist_force_; // сколько прогресса добавляет один ученый
	unsigned	count_scienist_; 
	void Increase(unsigned scienist_count); // увеличение науки 
	unsigned GetCountSpecialists();
};

// предметная наука - скорость(сила) прироста параметра в конкретной области
class SubjectScience: public TheScience{
	public:
		unsigned science_lvl;// уровень конкретной предметной отрасли

};

// игровой объект наука
class ScienseObject: public TbsInterface, public EngineGameObjInterface{
	public:
		ScienseObject();
			
	private:
		void NextTurn(); // расчет сл хода
	// the_science base_science(); // базовая наука
	// пример :std::unique_ptr<the_science> scns(new the_science);
	std::vector<std::unique_ptr<TheScience>> scienceList_vector; // список наук
};

#endif
