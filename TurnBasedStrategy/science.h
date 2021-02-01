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
	static unsigned scienceLvl_;		//общий научный уровень   TODO: test static ?
	std::string name;					// name 
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
		unsigned science_lvl;// уровень конкретной предметной отрасли

};

union Science_list{
		
};

class KingdoomScience{
	public:
		const unsigned my_n_;
		KingdoomScience();
		std::vector<std::unique_ptr<TheScience>> science_list_vector; // список наук
		unsigned GetScienceLvl(unsigned N);
	private:
		void NextTurn(); // расчет сл хода
		std::string GetSummariesString();
		
};

// игровой объект наука
class ScienceGameObj :public TbsInterface, public EngineGameObjInterface {
public:
	ScienceGameObj();
	unsigned GetScienceLvl_from_Kingdom(unsigned N, unsigned kingdom_n);
private:
	vector<KingdoomScience> v_kingdom_science;
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
};

#endif
