#ifndef ECONOMICS
#define ECONOMICS
#include"TbsInterface.h"
//
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

class Economics : public TbsInterface {
public:
	uint64_t gold; // ������������� ������
	uint64_t profit_gold; // ������� �� ��������� ���
	uint64_t consumption_gold; // ������
	uint64_t resourse;  // ��������������� ������ -- � ������ ������ ��� (�����)
	uint64_t increase_resourse;
	uint64_t consumption_resourse; //  ��������� � ����������� ������� 
private:

};
#endif
