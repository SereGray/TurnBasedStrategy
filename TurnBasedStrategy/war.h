/* Хранит состояние генералов солдат 
* Реализует механику битвы,  
*/
#ifndef WAR 
#define WAR
#include<string>
#include"engine.h"
#include<vector>

// правила войны
// расчет сражений
class General
{
	unsigned skill_;  // max 100
	float skill_float_;
	unsigned intelegence; // max 100
	unsigned spirit_; // max 100
	unsigned age_;   // max 100
	unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4 ... attack to kingdom  TODO: action Generall
	unsigned target_;  // number of kingdom to attack
	unsigned count_solders_;
	std::string name_;
	void Workout();
	void Study();
	void Defense(unsigned count_defenders);
	void NextTurn(); // change general condition 

};

class Kingdoom_defense {
	unsigned solders_;
	float solder_force_;
public:
	const unsigned my_n_;
	Kingdoom_defense(unsigned my_number):solders_(10), solder_force_(1.0), my_n_ = (my_number);
	std::vector<General> vGeneral_list;
	void AddGeneral(std::string name);
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	void NextTurn();
};

class Defense: public EngineGameObjInterface 
{
	std::vector<Kingdoom_defense> vkingdoom_def;   // список игроков
	General landaun_; // default bad general 
	

	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
	float GetSolderForce();
	void Battle();  // расчет битвы вызывается в NextTurn()
	std::string GetSummariesString();
public:
	unsigned DefenseBattle(); // return territory area
	unsigned AttackBattle();  // return territory area
};

#endif
