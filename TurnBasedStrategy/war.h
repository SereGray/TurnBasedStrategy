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

class General //TODO: �������� id ?
{
	friend class Kingdoom_defense; // only kingdom may create own generals
	float skill_float_;
	General();
	Kingdoom_defense & my_master_;
	General(Kingdoom_defense& my_master, std::string name,unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age, unsigned id);
	public:
	General(Kingdoom_defense& my_master); // constructor for landaun general 
	unsigned ID_;
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

// ����� ��� �������� � ��������� ������ ���������(����)
class ListGeneral // TODO: this
{
	unsigned current_key; // ��������� ������� ����
	map<unsigned,General> v_general_list_;// unsigned (key(ID)) is general indificator (unique)
	public:
	General& GetGeneral(unsigned id); // return General ref from key
	unsigned AddGeneral(General in); // return key in map(ID) and give to general it ID

};

// TODO: set attack
class Kingdoom_defense {
	Defense& master_;
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_n_;
	Kingdoom_defense(unsigned my_number, Defense& master):solders_(10), solder_force_(1.0), my_n_(my_number), master_(master);
	std::vector<General> vgeneral_list;
	General landaun_; // default bad general
	void AddGeneral(std::string name, unsigned skill, unsigned intelegence,unsigned speed, unsigned age);
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	float GetSolderForce();
	void NextTurn();
	void AddSummaryString(string text);
};
// struct ����� ����� ���-��
// ��������� ���� ���������� ��� �� ��������� ������ ����� ����� ��� �����
// localWar exists if exists one attacker
struct LocalWar
{
	vector<General&> first_kd_attacers_; // TODO: ��������� � ���� ����������� ������ � ������ ������� (��� ��������
	vector<General&> second_kd_attacers_;
	std::pair<Kingdoom_defense&,Kingdoom_defense&> ref_to_kingd_defense_;// 
	LocalWar(Kingdoom_defense& first, Kingdoom_defense& second): ref_to_kingd_defense_(std::make_pair(first, second){}; 
	std::pair<General&, General&> GetPairBattleGeneral();
	General& GetDefener(); // or lose area or landaun if solders > 0
	General& GetAttacer(); // sort attacers_ and get first by speed if no attacker return defender  TODO: ���� ����������� ��� ��������� ������ ��������� ���� �� ������ � �� ������ �� ���������, ���� �� �������� ��� ������ �� �� ������ ��������� ��� ��������� ��������, ���� ������� ������ �� ����� 2�� ��� �� ���
};

//���� ��� ������������� ������ ��������� ����
class ListLocalWar
{
	std::vector<LocalWar> v_local_wars_;
	General& GetMaxSpeedGeneral();
	bool AttackersEmpty(); // ����� ��� ����� � nextturn
	std::vector<LocalWar> GetLocalWars();
	// TODO: ����� �� ���� ��������� ���-�
	int SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number);  // return number index, else -1
};

class Defense: public EngineGameObjInterface 
{
	friend class Kingdoom_defense;
	std::vector<Kingdoom_defense> vkingdoom_def;   // ������ ������� (��� ���� �� ������� �������������� ������� � map.h my_N) 
	ListLocalWar list_local_war_;
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
	int Battle(General & attacker, float attacker_force, General & defender, float defender_force);  // ������ ����� ���������� � NextTurn() ���������� ��������������� ����������� ����� �� -100 �� 0 ��� +100 (��� ��� ������ �����������) 
	std::string GetSummariesString();
public:
	string summaries_;
	Defense():summaries_(""); // TODO: initialization args? 
	unsigned DefenseBattle(); // return territory area
	unsigned AttackBattle();  // return territory area
};

#endif
