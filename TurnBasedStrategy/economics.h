#ifndef ECONOMICS
#define ECONOMICS
#include"TbsInterface.h"
#include"Engine.h"
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
	uint64_t all_people; // ����� ���������� ����� TODO: ������������ ??
	uint32_t increase_people;  
	uint64_t maximum_people; 
	uint64_t fermers_people;// ����� ���������� ����� ������� � ���������
	
private:
	void increaseFermersPeople(); // ������� �������� ���������
	void decreaseFermersPeople(); // ������� 
};

class Economics : public TbsInterface, public EngineGameObjInterface {
public:
	uint64_t gold; // ������������� ������
	uint64_t profit_gold; // ������� �� ��������� ��� ??
	uint64_t consumption_gold; // ������
	uint64_t resourse;  // ��������������� ������ -- � ������ ������ ��� (�����)
	uint64_t increase_resourse;
	uint64_t consumption_resourse; //  ��������� � ����������� ������� 
	void SellResourse();
	void BuyResourse();
	void BuyThing();
private:
	void NextTurn(); //  ����� �������� �� �������
	uint64_t CalculationConsumption(); // ����� ������ �������� �� ����������    
	uint64_t CalculationSpecialistSalary(); // ������ ��������� ����������� 
	//( ��� ������ ������ ��� ������ �� ��������� (��������������� �����������?))
	uint32_t CalculationSpecialistHiring(); // ��������� ����� ������� �� ���������� ��� ����������
};
#endif
