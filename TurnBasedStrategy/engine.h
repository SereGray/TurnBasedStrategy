// ����� ������� �.�. ��� �� ���� �����
// ������� ���� - ��������� �.�. �
// ���������� ����� �� ������� �����
// ������� ������� � �������� ������ ���� �� �����

//TODO: ���������� � ������� ���������� ��� ������� ���� ( �������� ������� �����-�����, �����
//	����������, ����� ���������, ����� �����-���������, ����� �����
//TODO: �������������� ���. ��������
//	��������� ����������
//	�������: �����-��������� ������ � ��� ���
//		�����-��������� �������������� � ��� ��������� ������ �����
//		�������� ���������� ������(������) � ��� ��� ������������(���������)
//		��� ���-�� ������ ...
//		���������-�������� ����� � ��� ���������� ����������
#ifndef ENGINE
#define ENGINE

#include<vector>
#include"tbs_interface.h"
#include<string>
#include"science.h"
#include"war.h"
#include"map.h"
#include"economics.h"
// ������ �������� ��������

// ����� NextTurn : ����� ������� �������� �� ������ � ����� ������ NextTurnObj
// ����� ������� �������� ��� �������� EngineInterface � ����� �� ������ NextTurn

// ����� GameLoop : ������������ �������� �����


// ����� �������������� ������� �������� ������ ����� �����
class EngineGameObjInterface {
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);  // ������� ������� ������� ��� RTTI
	virtual void NextTurn();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState(unsigned num_players, unsigned map_size);
	virtual std::string GetSummariesString(); // ������ �� ���������� ���
	public:
	virtual ~EngineGameObjInterface();
};

EngineGameObjInterface::~EngineGameObjInterface(){}; 

class Engine: public TbsInterface{
public:
	ScienceGameObj science_game_obj_;
	void NextTurn(); // ��������� ������� �������� ���������� 
#endif
};

