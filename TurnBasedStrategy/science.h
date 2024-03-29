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
#include "utility.h"

//  общая наука - уровень общей науки определяет скорость развития предметных областе науки 
class TheScience{
	// класс наука
protected:	
	unsigned		progress_;			// количество работы ученых над текущим уровнем
	unsigned		progress_limit_;	// макс прогресс для этого уровняя (если больше то повыш ур.)
	float			scienist_force_;	// сколько прогресса добавляет один ученый
	int		count_scienist_; 
	unsigned		scienist_lvl_;
public:
	// TODO: проверить что прирост идет у предметной области науки а не у всей
	unsigned science_lvl_;		//общий научный уровень   TODO: test static ?
	std::string name_;					// name 
	TheScience() :progress_(0),progress_limit_(100), scienist_force_(1.0), count_scienist_(0),scienist_lvl_(0), science_lvl_(0),  name_("science") {};
	TheScience(std::string);
	TheScience& operator()(const TheScience& other);
	int GetCountSpecialists();
	void ChangeCountSpecialists(int);
	std::pair<unsigned, unsigned> GetProgress();
	void NextTurn(); // return scienist force_
	float GetScienistForce();
};



// предметная наука - скорость(сила) прироста параметра в конкретной области
class SubjectScience: public TheScience{
	public:
		
		std::string name_;
		TheScience* pbase_science_;
		SubjectScience() :TheScience::TheScience(), pbase_science_(this){};
		SubjectScience(TheScience* base_science, std::string name) : TheScience::TheScience(name), pbase_science_(base_science), name_(name) {};
		SubjectScience& operator()(TheScience* base_science, const SubjectScience& other);
		void NextTurn();
};


class KingdoomScience{
	TheScience science_;
	SubjectScience densety_people_, increase_people_, harvesting_, selling_res_, war_craft_;
	int free_scienists_;
	unsigned my_id_;
	public:
		KingdoomScience(unsigned my_id):science_(TheScience()),densety_people_(SubjectScience(&science_, "densety people")),\
			increase_people_(SubjectScience(&science_, "increase people")), harvesting_(SubjectScience(&science_,"harvesting"))\
			,selling_res_(SubjectScience(&science_,"Selling resourse")), war_craft_(SubjectScience(&science_,"war craft")),\
			my_id_(my_id), free_scienists_(0) {};
		KingdoomScience(const KingdoomScience& other);
		//std::vector<std::unique_ptr<TheScience>> science_list_vector; // список наук
		//SubjectScience densety_people_(&science, "densety people"), increase_people(&science, "increase people"), harvesting(&science, "harvesting"), selling_res(&science, "selling"), war_craft(&science, "war craft");
		
		unsigned GetScienceLvl();
		unsigned GetHarvestingLvl();
		unsigned GetSellingResLvl();
		unsigned GetWarcraftLvl();
		unsigned GetDensityLvl();
		unsigned GetIncreasingLvl();
		void ChangeCountSpec_DensetyPeople(int);
		void ChangeCountSpec_Science(int);
		void ChangeCountSpec_IncreasePeople(int);
		void ChangeCountSpec_Harvesting(int);
		void ChangeCountSpec_SellingRes(int);
		void ChangeCountSpec_WarCraft(int);
		unsigned GetCountSpec_DensetyPeople();
		unsigned GetCountSpec_Science();
		unsigned GetCountSpec_IncreasePeople();
		unsigned GetCountSpec_Harvesting();
		unsigned GetCountSpec_SellingRes();
		unsigned GetCountSpec_WarCraft();
		std::pair<unsigned, unsigned> GetProgress_DensetyPeople();
		std::pair<unsigned, unsigned> GetProgress_Science();
		std::pair<unsigned, unsigned> GetProgress_IncreasePeople();
		std::pair<unsigned, unsigned> GetProgress_Harvesting();
		std::pair<unsigned, unsigned> GetProgress_SellingRes();
		std::pair<unsigned, unsigned> GetProgress_WarCraft();

		unsigned GetMyId() const;
		void ChangeFreeSpecialists(int);
		unsigned GetFreeSpecialist();
		void ResetAllSpecialist();
		unsigned GetCountAllSpecialists();

		void NextTurn(); // расчет сл хода

	private:
		void ChangeCountSpecialist(TheScience&, int);
		unsigned GetCountSpecialists(TheScience&);
		std::string GetSummariesString();
		
};

// игровой объект наука
class ScienceGameObj : public EngineGameObjInterface {
public:									  
	ScienceGameObj();
	KingdoomScience* GetKingdoomScience(unsigned by_id);
	void AddKingdoom(unsigned);
	~ScienceGameObj();
	void NextTurn();
private:
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	std::vector<KingdoomScience> v_kingdom_science; // access to kingdom by my_id_
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
};

#endif
