/* ������ ��������� ��������� ������
* ��������� �������� �����,
*/
#ifndef WAR 
#define WAR
#include<string>
#include"engine.h"
#include<vector>
#include"science.h"
#include<memory>

// ������� �����
// ������ ��������

class Kingdoom_defense;// forward declaration
class Defense;

class Game_Map;

class General
{
	friend class Kingdoom_defense; // only kingdom may create own generals
	static unsigned next_general_id; // inline ?
	unsigned my_id_;
	float skill_float_;
	General();
	Kingdoom_defense& my_master_;
	General(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);

public:
	unsigned skill_; // max 100
	unsigned intelegence_; // max 100
	unsigned spirit_; // max 100
	unsigned speed_; // max 100
	unsigned age_;   // max 100
	unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4 ... attack to kingdom 5 - dead TODO: action Generall
	unsigned target_;  // number of kingdom to attack TODO: set targer
	unsigned count_solders_;
	std::string name_;

	General(Kingdoom_defense& my_master); // constructor for landaun general 
	void AttackTo(unsigned count_attack, unsigned number_kingd);
	void Rest();
	void Workout();
	void Study();
	void Defense(unsigned count_defenders);
	void NextTurn(); // change general condition 
	void Dead();
	Kingdoom_defense& GetMaster();

};


// TODO: set attack
class Kingdoom_defense {
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_id_;
	Defense& master_;
	std::vector<General> v_general_; //  kingdom generals
	General landaun_; // default bad general

	void DeleteGeneral(unsigned my_id);
	Kingdoom_defense(unsigned my_number, Defense& master) :solders_(10), solder_force_(1.0), my_id_(my_number), master_(master) {};
	General& GetSpeedestGeneral(unsigned target);
	void AddGeneral(std::string name, unsigned skill, unsigned intelegence, unsigned speed, unsigned age); // TODO: refractor there
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	float GetSolderForce();
	void NextTurn();
	void AddSummaryString(std::string text);
	std::string GetSummaryString();
	void SetAttack(General& gen, unsigned target);
};

//���� ����������� ��� ��������� ������ ��������� ���� �� ������ � �� ������ �� ���������, ���� �� �������� ��� ������ �� �� ������ ��������� ��� ��������� ��������, 
//���� ������� ������ �� ����� 2�� ��� �� ���

class Defense : public EngineGameObjInterface
{
	friend class Kingdoom_defense;
	Game_Map* map_obj_;
	std::vector<Kingdoom_defense> vkingdoom_def_;   // ������ ������� (��� ���� �� ������� �������������� ������� � map.h my_N) 
	std::vector<std::pair<Kingdoom_defense&, Kingdoom_defense& >> vlocal_wars_;

	void SortLocalWarsByGeneralSpeed();
	bool LocalWarNoAttackers(std::vector<std::pair<Kingdoom_defense&, Kingdoom_defense&>>::iterator it);
	std::pair<General&, General&> GetPairBattleGeneral(std::vector<std::pair<Kingdoom_defense&, Kingdoom_defense&>>::iterator it);
	int SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number);  // return number index, else -1

	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);  // ������� ������� ������� ��� RTTI
	virtual void GetLocalWars();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState(unsigned num_players, unsigned map_size); //, Game_Map& map_obj);
	virtual void NextTurn();

	int Battle(General& attacker, General& defender);  // ������ ����� ���������� � NextTurn() ���������� ��������������� ����������� ����� �� -100 �� 0 ��� +100 (��� ��� ������ �����������) 

	std::string GetSummariesString();

public:
	~Defense();
	Defense(unsigned num_players); //TODO: consructor
	std::string summaries_;
	Defense() :summaries_("") {}; // TODO: initialization args? 
};

#endif
