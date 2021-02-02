/*
* Наука хранит состояние прогресса от которого зависить эфективность работы королевств
*/
#ifndef SCIENCE 
#define SCIENCE
#include "tbs_interface.h"
#include "engine.h"
#include <string>
#include <vector>
#include <memory>

//  общая наука - уровень общей науки определяет скорость развития предметных областе науки 
class TheScience{
	// класс наука
	public:
		TheScience(std::string nameScience);
		// TODO: проверить что прирост идет у предметной области науки а не у всей
	unsigned science_lvl_;		//общий научный уровень   TODO: test static ?
	std::string name_;					// name 
        private:	
	unsigned		progress_;			// количество работы ученых над текущим уровнем
	unsigned		progress_limit_;	// макс прогресс для этого уровняя (если больше то повыш ур.)
	static float	scienist_force_;	// сколько прогресса добавляет один ученый
	unsigned		count_scienist_; 
	float Scienist_force();				// подсчет силы ученого запускать в NextTurn() т.к.результат static
	void Increase(unsigned scienist_count); // увеличение науки 
	unsigned GetCountSpecialists();
	void AddScienist();
};

// предметная наука - скорость(сила) прироста параметра в конкретной области
class SubjectScience: public TheScience{
	public:
		TheScience* pbase_science_;
		SubjectScience(TheScience* base_science, string name) : pbase_science_(base_science), name_(name);
		void Increase(unsigned scienist_count); // увеличение науки 
};


class KingdoomScience{
	public:
		const unsigned my_n_;
		KingdoomScience();
		std::vector<std::unique_ptr<TheScience>> science_list_vector; // список наук
		TheScience science;
		SubjectScience densety_people(&science, "densety people"), increase_people(&science, "increase people"), harvesting(&science, "harvesting"), selling_res(&science, "selling"), war_craft(&science, "war craft");
	private:
		void NextTurn(); // расчет сл хода
		std::string GetSummariesString();
		
};

// игровой объект наука
class ScienceGameObj :public TbsInterface, public EngineGameObjInterface {
public:
	ScienceGameObj();
	KingdoomScience& GetScience_from_Kingdom(unsigned kingdom_n);
private:
	vector<KingdoomScience> v_kingdom_science; // access to kingdom by my_n_
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
};

#endif
