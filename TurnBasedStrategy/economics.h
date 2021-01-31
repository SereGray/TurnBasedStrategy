/*
* ��������� ������ ������ � ���������� �����(���������) ���������� �������� � ���, ���������� ����� � ���-�, ���������� ������,
* ��������� ������/����� ����� � ������
* ������������ � ������ ������ � ����� ������, ������ �� ������, ������� ������, ������ (� ����� �� �������� � ������)
*/
#ifndef ECONOMICS
#define ECONOMICS
#include"tbs_interface.h"
#include"engine.h"
// ������ ���������: (+����������)
// ����� ���������� ����� (�� �������� ��� ���������)
// �� ��������� ����������
// ��������� ����������� ��������
// ������� ����������� �����
// ������� ������ ������ ��������� ...
// 
// ����������:
//������� ��������
//��������� ��������
class Demography {
public:
	uint64_t all_people_; // ����� ���������� ����� TODO: ������������ ??
	uint32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// ����� ���������� ����� ������� � ���������
	
private:
	void TncreaseFermersPeople(); // ������� �������� ���������(����� ���� ������������� �������)
	void DecreaseFermersPeople(); // ������� ����� �������� (������ � �������� ����)
};

class Economics : public TbsInterface, public EngineGameObjInterface {
public:
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
private:
	void NextTurn(); //  ����� �������� �� �������
	std::string GetSummariesString();
	void ResourseConsumption();   // 1 man eat 1 resourse (corn)
	uint64_t CalculationConsumption(); // ����� ������ �������� ������ �� ����������    
	uint64_t CalculationSpecialistSalary(); // ������ ��������� ����������� 
	//( ��� ������ ������ ��� ������ �� ��������� (��������������� �����������?)) �� ��������� ~3
	uint32_t CalculationSpecialistHiring(); // ��������� ����� ������� �� ���������� ��� ����������
};
#endif
