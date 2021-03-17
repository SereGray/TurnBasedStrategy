/* Хранит состояние генералов солдат 
* Реализует механику битвы,  
*/
#ifndef WAR 
#define WAR
#include<string>
#include"engine.h"
#include<vector>
#include"science.h"
#include<memory>

// правила войны
// расчет сражений

class Kingdoom_defense;// forward declaration

class General
{
	friend class Kingdoom_defense; // only kingdom may create own generals
	float skill_float_;
	General();
	Kingdoom_defense & my_master_;
	General(Kingdoom_defense& my_master, std::string name,unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);
	public:
	General(); // def constructor for landaun general  TODO:this
	unsigned skill_; // max 100
	unsigned intelegence_; // max 100
	unsigned spirit_; // max 100
	unsigned speed_; // max 100
	unsigned age_;   // max 100
	unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4 ... attack to kingdom  TODO: action Generall
	unsigned target_;  // number of kingdom to attack TODO: set targer
	unsigned count_solders_;
	std::string name_;
	void AttackTo(unsigned count_attack, unsigned number_kingd);
	void Rest();
	void Workout();
	void Study();
	void Defense(unsigned count_defenders);
	void NextTurn(); // change general condition 
	void Dead();

};

class Defense;


// TODO: set attack
class Kingdoom_defense {
	Defense& master_;
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_n_;
	Kingdoom_defense(unsigned my_number, Defense& master):solders_(10), solder_force_(1.0), my_n_(my_number), master_(master);
	std::vector<General> vgeneral_list;
	General landaun_; // default bad general TODO: inicialization
	void AddGeneral(std::string name, unsigned skill, unsigned intelegence,unsigned speed, unsigned age);
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	float GetSolderForce();
	void NextTurn();
	void AddSummaryString(string text);
};
// struct войны между гос-ми
// структура сама определяет кто из генералов бьется между собой при войне
// localWar exists if exists one attacker
struct LocalWar
{
	vector<General&> first_kd_attacers_;
	vector<General&> second_kd_attacers_;
	std::pair<Kingdoom_defense&,Kingdoom_defense&> ref_to_kingd_defense_;// 
	static bool AttackersEmpty(); // нужно для цикла в nextturn
	General& GetMaxSpeedGeneral();
	LocalWar(Kingdoom_defense& first, Kingdoom_defense& second): ref_to_kingd_defense_(std::make_pair(first, second){}; 
	std::pair<General&, General&> GetPairBattleGeneral();
	General& GetDefener(); // or lose area or landaun if solders > 0
	General& GetAttacer(); // sort attacers_ and get first by speed if no attacker return defender  TODO: если встретились два атакующих значит атакующий цели не достиг и из списка не удаляется, если он растерял все войско то он должен удалиться при следующей итерации, один генерал бьется не более 2ух раз за ход
};

class Defense: public EngineGameObjInterface 
{
	string summaries_;
	std::vector<Kingdoom_defense> vkingdoom_def;   // список игроков (они идут по номерам соответсвующим номерам в map.h my_N) TODO: rename to vkingdom_def_
	std::queue<LocalWar> q_local_wars_; // список указателей?
	std::queue<LocalWar> GetLocalWars();
	int SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number);  // return number in queue, else -1
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
	int Battle(General & attacker, float attacker_force, General & defender, float defender_force);  // расчет битвы вызывается в NextTurn() возвращает территориальный коэффициент битвы от -100 до 0 или +100 (исп при обмене территорией) 
	std::string GetSummariesString();
public:
	Defense():summaries_(""); // TODO: initialization args? 
	unsigned DefenseBattle(); // return territory area
	unsigned AttackBattle();  // return territory area
};

#endif
