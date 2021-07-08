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

// Gold class
class Gold : public Resource {
public:
	Gold(int);
};

// Eat class
class Food : public Resource {
public:
	Food(int);
};

//
class BaseCost {
public:
	virtual ~BaseCost();
	virtual Resource& Buy();
};

template<typename TypeResource>
class UnitCost : public BaseCost {
public:
	TypeResource buy_, consumption_, sell_; //in 0.01
public:
	UnitCost(int buy, int consumption, int sell);
	Resource& Buy() override;
	Resource& Consumption(); 
	Resource& Sell();
};



class Specialist {
public:
	UnitCost<Gold> gold_;
	UnitCost<Food> food_;
	BaseCost& r_gold_;
	BaseCost& r_food_;
	Specialist(UnitCost<Gold> gold, UnitCost<Food> food);
	template<class Visitor>
	bool Accept(Visitor f, unsigned count = 1) {
		if (!f(r_gold_, count)) {
			return false;
		}
		if (!f(r_food_, count)) {
			return false;
		}
	};
};

struct Specialist1Compare
{
	bool operator() (const Specialist& lhs, const Specialist& rhs) const
	{
		return lhs.gold_.buy_.count_ < rhs.gold_.buy_.count_;
	}
};
// 
class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	std::map<Specialist, unsigned, Specialist1Compare> m_specialists_;
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
	void BuySpecialist(Specialist&, unsigned);
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
	static bool VisitorBuySpecialist(KingdoomEconomics& eco, BaseCost& cost, int count);
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


