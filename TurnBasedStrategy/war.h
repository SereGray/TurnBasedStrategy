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

class General
{
	friend class Kingdoom_defense; // only kingdom may create own generals
	float skill_float_;
	General();
	Kingdoom_defense & my_master_;
	General(Kingdoom_defense& my_master, std::string name,unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);
	public:
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

class Defense: public EngineGameObjInterface 
{
	string summaries_;
	std::vector<Kingdoom_defense> vkingdoom_def;   // ������ ������� (��� ���� �� ������� �������������� ������� � map.h my_N)
	std::queue<General*> q_fight_generals_; // ������ ���������� �� ����������� ���������
	std::queue<General*> GetFightGenerals();
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
	int Battle(General & attacker, float attacker_force, General & defender, float defender_force);  // ������ ����� ���������� � NextTurn() ���������� ��������������� ����������� ����� �� -100 �� 0 ��� +100 (��� ��� ������ �����������) 
	std::string GetSummariesString();
public:
	Defense():summaries_(""); // TODO: initialization args? 
	unsigned DefenseBattle(); // return territory area
	unsigned AttackBattle();  // return territory area
};

#endif
