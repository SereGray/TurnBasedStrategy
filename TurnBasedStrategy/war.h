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
#include"map.h"
#include "gtest/gtest.h"
// правила войны
// расчет сражений

class Kingdoom_defense;// forward declaration
class WarGameObj;

//class MapGameObj;

class General
{
	friend class FixationGeneralPrivate;   // for googletest
	FRIEND_TEST(FixationGeneralPrivate,GeneralSkillFloat);
	static unsigned next_general_id;
	unsigned my_id_;
	float skill_float_;
	General();
	Kingdoom_defense* my_master_;
	General(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned intelegence, \
		unsigned spirit, unsigned speed, unsigned age);
	
public:
	unsigned skill_; // max 100
	unsigned intelegence_; // max 100
	unsigned spirit_; // max 100
	unsigned speed_; // max 100
	unsigned age_;   // max 100
	unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4  attack , 5 - dead TODO: action Generall enum ? union ?
	unsigned target_;  // number of kingdom to attack TODO: set targer
	unsigned count_solders_;
	std::string name_;

	static General CreateGeneral(Kingdoom_defense& my_master, std::string name, unsigned skill,\
		unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);
	General(Kingdoom_defense& my_master); // constructor for landaun general 
	void AttackTo(unsigned count_attack, unsigned number_kingd);
	void Rest();
	void Workout();
	void Study();
	void Defense(unsigned count_defenders);
	void NextTurn(); // change general condition 
	void Dead();
	Kingdoom_defense* GetMaster();
	float GetSolderForce();
	unsigned GetMyId();
	static unsigned GetNextId();
	static void SetNullId();

};


// TODO: set attack
class Kingdoom_defense {
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_id_;
	WarGameObj* master_;
	std::vector<General> v_general_; //  kingdom generals
	General landaun_; // default bad general // TODO: this general must be default, if no generals

	void DeleteGeneral(unsigned by_id);
	General& GetGeneral(unsigned by_id);
	unsigned GetIndexOfGeneral(unsigned by_id);
	Kingdoom_defense(unsigned my_number, WarGameObj& master);
	General& GetSpeedestGeneral(unsigned target);
	unsigned AddGeneral(std::string name, unsigned skill, unsigned intelegence, \
		unsigned speed, unsigned age); // TODO: refractor there
	void AddSolder(unsigned count);
	void DecreaseSolders(unsigned count);
	unsigned GetCountFreeSpecialists();
	float GetSolderForce();
	void NextTurn();
	void AddSummaryString(std::string text);
	std::string GetSummaryString();
	void SetAttack(General& gen, unsigned solders, unsigned target);

};

//если встретились два атакующих значит атакующий цели не достиг и из списка не удаляется, если он растерял все войско то он должен удалиться при следующей итерации, 
//один генерал бьется не более 2ух раз за ход

class WarGameObj : public EngineGameObjInterface
{
	friend class Kingdoom_defense;
	MapGameObj* map_obj_ = nullptr;
	ScienceGameObj* science_obj = nullptr;
	std::vector<Kingdoom_defense> vkingdoom_def_;   // список игроков (они идут по номерам соответсвующим номерам в map.h GetMyId) 
	//std::vector<std::pair<Kingdoom_defense&, Kingdoom_defense& >> vlocal_wars_; TODO: not work
	std::vector<std::pair<unsigned, unsigned>> vlocal_wars_; // содержит id

	void ClearLocalWars();
	void SortLocalWarsByGeneralSpeed();
	bool LocalWarNoAttackers(std::vector<std::pair<unsigned, unsigned>>::iterator it);
	std::pair<General&, General&> GetPairBattleGeneral(std::vector<std::pair<unsigned, unsigned>>::iterator it);
	int SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number);  // return number index, else -1

	std::pair<unsigned, unsigned> MaxSpeedGeneral(std::pair<unsigned, unsigned> kd);

	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);  // получаю игровые объекты исп RTTI
	virtual void GetLocalWars();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState(unsigned num_players, unsigned map_size); //, MapGameObj& map_obj);
	virtual void NextTurn();

	int Battle(General& attacker, General& defender);  // расчет битвы вызывается в NextTurn() возвращает территориальный коэффициент битвы от -100 до 0 или +100 (исп при обмене территорией) 
	unsigned GetWarCraftLevel(unsigned my_id_);
	std::string GetSummariesString();

public:
	~WarGameObj();
	WarGameObj(unsigned num_players); //TODO: consructor
	std::string summaries_;
	WarGameObj() :summaries_("") {}; // TODO: initialization args? 
};

#endif
