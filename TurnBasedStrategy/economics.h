/*
* ��������� ������ ������ � ���������� �����(���������) ���������� �������� � ���, ���������� ����� � ���-�, ���������� ������,
* ��������� ������/����� ����� � ������
* ������������ � ������ ������ � ����� ������, ������ �� ������, ������� ������, ������ (� ����� �� �������� � ������)
*/
#ifndef ECONOMICS
#define ECONOMICS
#include"tbs_interface.h"
#include"engine.h"
#include"science.h"
#include"map.h"
#include"resource.h"
#include"units.h"
#include<map>

// ������ ���������: (+����������)
// ����� ���������� ����� (�� �������� ��� ���������)
// �� ��������� ����������
// ��������� ����������� ��������
// ������� ����������� �����
// ������� ������ ������ ��������� ...
// 
class KingdoomEconomics;
class EconomicsGameObj;
// ����������:
//������� ��������
//��������� ��������
class Demography {
public:
	uint64_t all_people_; // ����� ���������� ����� TODO: ������������ ??
	int32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// ����� ���������� ����� ������� � ���������
	Demography();
	void NextTurn(unsigned area, unsigned increasing_lvl, unsigned densety_lvl);
private:


public:
	void IncreaseFermersPeople(); // ������� �������� ���������(����� ���� ������������� �������)
	void DecreaseFermersPeople(unsigned decrease_count); // ������� ����� �������� (������ � �������� ����)
};



class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	Gold gold_; // ������������� ������
	Food food_;
	Demography nation_; // 
	int profit_gold_; // ������� �� ��������� ��� ??
	int consumption_gold_; // ������
	int increase_resourse_;
	int consumption_resourse_; //  ��������� � ����������� ������� 

	bool SellResourse(Resource&,int);
	bool BuyResourse(Resource&,int);
	unsigned GetDensityLvl();
	unsigned GetIncreasingLvl();
	void ChangeCountSpecialists(Unit&, unsigned);
	unsigned MyArea();
	unsigned GetMyId();
private: 

	struct Visiter {
		KingdoomEconomics& e_;
		bool (*ptrFunct_)(KingdoomEconomics&, BaseCost&, int);
		Visiter(KingdoomEconomics& e, bool (*ptrFunct)(KingdoomEconomics&, BaseCost&, int)) :e_(e), ptrFunct_(ptrFunct) {};
		bool operator()(BaseCost& cost, int count) {
			return ptrFunct_(e_, cost, count);
		}
	};

	Visiter visiter_;
	unsigned my_id_;
	EconomicsGameObj& my_master_;
	void NextTurn(); //  ����� �������� �� �������
	std::string GetSummariesString();
	void ResourseConsumption();   // 1 man eat 1 resourse (corn)
	uint64_t CalculationConsumption(); // ����� ������ �������� ������ �� ����������    
	uint64_t CalculationSpecialistSalary(); // ������ ��������� ����������� 
	//( ��� ������ ������ ��� ������ �� ��������� (��������������� �����������?)) �� ��������� ~3
	uint32_t CalculationSpecialistHiring(); // ��������� ����� ������� �� ���������� ��� ����������
	static bool VisitorChangeCountSpecialists(KingdoomEconomics& eco, BaseCost& cost, int count);
};

class EconomicsGameObj : public EngineGameObjInterface{
	std::vector<KingdoomEconomics> v_economics_;
	ScienceGameObj* science_obj_ = nullptr;
	MapGameObj* map_obj_ = nullptr;	
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
public:
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	EconomicsGameObj();
	~EconomicsGameObj();
	KingdoomEconomics* GetKingdoomEconomics(unsigned by_id);
	void AddKingdomEconomics(unsigned by_id);
	unsigned MyArea(unsigned by_id);
	unsigned GetDensityLvl(unsigned by_id);
	unsigned GetIncreasingLvl(unsigned by_id);

};

#endif


