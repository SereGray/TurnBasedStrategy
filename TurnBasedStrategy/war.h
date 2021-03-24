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
#include<map>

// ������� �����
// ������ ��������

class Kingdoom_defense;// forward declaration
class Defense;

class General
{
	friend class Kingdoom_defense; // only kingdom may create own generals
	float skill_float_;
	General();
	Kingdoom_defense & my_master_;
	General(Kingdoom_defense& my_master, std::string name,unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age);
	public:
	General(Kingdoom_defense& my_master); // constructor for landaun general 
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
	Kingdoom_defense& GetMaster();

};


// TODO: set attack
class Kingdoom_defense {
	unsigned solders_;
	float solder_force_; // 1.0 at def , always > 1.0
public:
	const unsigned my_id_;
	Kingdoom_defense(unsigned my_number, Defense& master):solders_(10), solder_force_(1.0), my_id_(my_number), master_(master);
	std::vector<General> v_general_; //  kingdom generals
	General landaun_; // default bad general
	Geneal& GetSpeedestGeneral(unsigned target);
	void AddGeneral(std::string name, unsigned skill, unsigned intelegence,unsigned speed, unsigned age); // TODO: refractor there
	void SortGeneralBySpeed();
	void AddSolder(unsigned count);
	unsigned GetCountSpecialists();
	float GetSolderForce();
	void NextTurn();
	void AddSummaryString(string text);
	string GetSummaryString();
};

	//���� ����������� ��� ��������� ������ ��������� ���� �� ������ � �� ������ �� ���������, ���� �� �������� ��� ������ �� �� ������ ��������� ��� ��������� ��������, 
	//���� ������� ������ �� ����� 2�� ��� �� ���
//���� ��� ������������� ������ ��������� ����
class LocalWar
{

public:
	std::pair<General&, General&> GetPairBattleGeneral();
	bool AttackersEmpty(); // ����� ��� �������� ����� ������������ �������
	// TODO: ����� �� ���� ��������� ���-�
	LocalWar& SearchLocalWarByGeneral(General& gen);
	bool Empty();
};

class Defense: public EngineGameObjInterface 
{
	friend class Kingdoom_defense;
	std::vector<Kingdoom_defense> vkingdoom_def_;   // ������ ������� (��� ���� �� ������� �������������� ������� � map.h my_N) 
	int SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number);  // return number index, else -1
	std::vector<std::pair<Kingdoom_defense&, Kingdoom_defense& >> vlocal_wars_;
	SortLocalWarsByGeneralSpeed();
	LocalWarNoAttackers(vector<pair<Kingdoom_defense&,Kingdoom_defense&>::iterator it);
	pair<General&,General&> GetPairBattleGeneral(vector<pair<Kingdoom_defense&,Kingdoom_defense&>>::iterator it);
	void GetLocalWars()
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
};

#endif
