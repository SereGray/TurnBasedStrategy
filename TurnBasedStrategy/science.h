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
        private:	
	unsigned		progress_;			// количество работы ученых над текущим уровнем
	unsigned		progress_limit_;	// макс прогресс для этого уровняя (если больше то повыш ур.)
	float	scienist_force_;	// сколько прогресса добавляет один ученый
	unsigned		count_scienist_; 
	unsigned		scienist_lvl_;
	float Scienist_force();				// подсчет силы ученого запускать в NextTurn() т.к.результат static
	void Increase(unsigned scienist_count); // увеличение науки 
	unsigned GetCountSpecialists();
	void AddScienist();
public:
	// TODO: проверить что прирост идет у предметной области науки а не у всей
	unsigned science_lvl_;		//общий научный уровень   TODO: test static ?
	std::string name_;					// name 
	TheScience() :progress_(0),progress_limit_(100), scienist_force_(1.0), count_scienist_(0),scienist_lvl_(0), science_lvl_(0),  name_("science") {};
	TheScience(std::string nameScience);
};



// предметная наука - скорость(сила) прироста параметра в конкретной области
class SubjectScience: public TheScience{
	SubjectScience();
	public:
		std::string name_;
		TheScience& pbase_science_;
		SubjectScience(TheScience& base_science, std::string name) : TheScience::TheScience(name), pbase_science_(base_science), name_(name) {};
		void Increase(unsigned scienist_count); // увеличение науки 
};


class KingdoomScience{
	TheScience science;
	SubjectScience densety_people_, increase_people_, harvesting_, selling_res_, war_craft_;
	public:
		const unsigned my_id_;
		KingdoomScience(unsigned my_id) :densety_people_(SubjectScience(science, "densety people")), increase_people_(SubjectScience(science, "increase people")), harvesting_(SubjectScience(science,"harvesting")),selling_res_(SubjectScience(science,"Selling resourse")), war_craft_(SubjectScience(science,"war craft")), my_id_(my_id) {};
		std::vector<std::unique_ptr<TheScience>> science_list_vector; // список наук
		//SubjectScience densety_people_(&science, "densety people"), increase_people(&science, "increase people"), harvesting(&science, "harvesting"), selling_res(&science, "selling"), war_craft(&science, "war craft");
		unsigned GetCountSpecialists();
		unsigned GetWarcraftLvl();
		unsigned GetDensityLvl():
private:
		void NextTurn(); // расчет сл хода
		std::string GetSummariesString();
		
};

// игровой объект наука
class Science_game_obj :public TbsInterface, public EngineGameObjInterface {
public:									  
	Science_game_obj() {};
	KingdoomScience& GetKingdoomScience(unsigned kingdom_id);
	~Science_game_obj();
private:
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	std::vector<KingdoomScience> v_kingdom_science; // access to kingdom by my_id_
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
};

#endif
