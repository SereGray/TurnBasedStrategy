/* ������ ��������� ��������� ������ 
* ��������� �������� �����,  
*/
#ifndef WAR 
#define WAR
#include<string>
#include"engine.h"
#include<vector>


// ������� �����
// ������ ��������
class General
{
	float skill_float_;
public:
	unsigned skill_; // max 100
	unsigned intelegence_; // max 100
	unsigned spirit_; // max 100
	unsigned speed_; // max 100
	unsigned age_;   // max 100
	unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4 ... attack to kingdom  TODO: action Generall
	unsigned target_;  // number of kingdom to attack
	unsigned count_solders_;
	std::string name_;
	General(std::string name,unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);
	void AttackTo(unsigned count_attack, unsigned number_kingd);
	void Rest();
	void Workout();
	void Study();
	void Defense(unsigned count_defenders);
	void NextTurn(); // change general condition 

};

class Kingdoom_defense {
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_n_;
	Kingdoom_defense(unsigned my_number):solders_(10), solder_force_(1.0), my_n_ = (my_number);
	std::vector<General> vGeneral_list;
	void AddGeneral(std::string name, unsigned skill, unsigned intelegence, unsigned age);
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	void NextTurn();
};

class Defense: public EngineGameObjInterface 
{
	std::vector<Kingdoom_defense> vkingdoom_def;   // ������ �������
	General landaun_ // default bad general TODO: inicialization
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	unsigned GetCountSpecialists();
	float GetSolderForce();
	int Battle(General & attacker, float attacker_force, General & defender, float defender_force);  // ������ ����� ���������� � NextTurn() ���������� ��������������� ����������� ����� �� -100 �� 0 ��� +100 (��� ��� ������ �����������) 
	std::string GetSummariesString();
public:
	unsigned DefenseBattle(); // return territory area
	unsigned AttackBattle();  // return territory area
};

#endif
