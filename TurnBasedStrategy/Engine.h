// ����� ��������� ����� ���
// ��������� ������������� �����
// 
// ������ ����� ����
// �������� �����
// ��������� �����

// ����� ������� �.�. ����� ���� �����
// ������� ���� - ��������� �.�. �
// ���������� ����� �� ������� �����

// ����� ��������� ���� �������� �������� � � �
// ������������ �� ���� ����
#ifndef ENGINE
#define ENGINE
#include"tbs_interface.h"

// ������ �������� ��������

// ����� NextTurn : ����� ������� �������� �� ������ � ����� ������ NextTurnObj
// ����� ������� �������� ��� �������� EngineInterface � ����� �� ������ NextTurn

// ����� GameLoop : ������������ �������� �����


// ����� �������������� ������� �������� ������ ����� �����
class EngineGameObjInterface {
	public:
	virtual void NextTurn();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState();
	virtual unsigned GetCountSpecialists(); // �������� ���������� ������� ������������
};

class Engine: public TbsInterface{
	void NextTurn(); // ��������� ������� �������� ���������� 
};

#endif 
