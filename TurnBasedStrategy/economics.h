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
	uint32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// ����� ���������� ����� ������� � ���������
	Demography(KingdoomEconomics* master);
	void NextTurn();
private:
	Demography()=default;
	KingdoomEconomics* my_master_ = nullptr;
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
	UnitCost<Gold> gold;
	UnitCost<Food> food;
	BaseCost& gold_;
	BaseCost& food_;
	Specialist();
	template<typename Visitor>
	void Accept(Visitor f, unsigned count = 1) {
		f(gold_, count);
		f(food_, count);
	};
};

// 
class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	Gold gold_;
	Food food_;
	Demography nation_; // 
	//uint64_t gold_; // ������������� ������
	uint64_t profit_gold_; // ������� �� ��������� ��� ??
	uint64_t consumption_gold_; // ������
	uint64_t resourse;  // ��������������� ������ -- � ������ ������ ��� (�����)
	uint64_t increase_resourse_;
	uint64_t consumption_resourse_; //  ��������� � ����������� ������� 

	void SellResourse();
	void BuyResourse();
	void CostToCropsResourse();
	void BuyThing();  // solder, scienist, General ...
	unsigned GetDensityLvl();
	void BuySpecialist(unsigned);
	unsigned MyArea();
private:
	struct Visiter {
		KingdoomEconomics& e_;
		void (*ptrFunct_)(KingdoomEconomics&, BaseCost&, int);
		Visiter(KingdoomEconomics& e, void (*ptrFunct)(KingdoomEconomics&, BaseCost&, int)) :e_(e), ptrFunct_(ptrFunct) {};
		void operator()(BaseCost& cost, int count) {
			ptrFunct_(e_, cost, count);
		}
	};
	Specialist pikiner_; //test
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
	static void VisitorBuySpecialist(KingdoomEconomics& eco, BaseCost& cost, int count);
};

class EconomicsGameObj : public EngineGameObjInterface{
	std::vector<KingdoomEconomics> v_economics_;
	ScienceGameObj* science_obj_ = nullptr;
	MapGameObj* map_obj_ = nullptr;	
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	public:
	EconomicsGameObj();
	~EconomicsGameObj();
	KingdoomEconomics& GetKingdoomEconomics(unsigned by_id);
	unsigned MyArea(unsigned by_id);
	unsigned GetDensityLvl(unsigned by_id);

};	
#endif


