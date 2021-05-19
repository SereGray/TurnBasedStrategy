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

// 
class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	unsigned MyArea();
	Demography nation_; // 
	uint64_t gold_; // ������������� ������
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
private:
	unsigned my_id_;
	EconomicsGameObj& my_master_;
	void NextTurn(); //  ����� �������� �� �������
	std::string GetSummariesString();
	void ResourseConsumption();   // 1 man eat 1 resourse (corn)
	uint64_t CalculationConsumption(); // ����� ������ �������� ������ �� ����������    
	uint64_t CalculationSpecialistSalary(); // ������ ��������� ����������� 
	//( ��� ������ ������ ��� ������ �� ��������� (��������������� �����������?)) �� ��������� ~3
	uint32_t CalculationSpecialistHiring(); // ��������� ����� ������� �� ���������� ��� ����������
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
