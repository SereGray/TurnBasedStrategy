// ����� ������� �.�. ��� �� ���� �����
// ������� ���� - ��������� �.�. �
// ���������� ����� �� ������� �����

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
public:
	virtual void NextTurn();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState(unsigned num_players, unsigned map_size);
	virtual unsigned GetCountSpecialists(); // �������� ���������� ������� ������������
	virtual KingdoomScience& GetScience_from_Kingdom(unsigned kingdom_n);  // �������� ������� ����� 
	virtual std::string GetSummariesString(); // ������ �� ���������� ���
	virtual Map& GetMap();
};

class Engine: public TbsInterface{
public:
	ScienceGameObj science_game_obj_;
	void NextTurn(); // ��������� ������� �������� ���������� 
};
#endif

