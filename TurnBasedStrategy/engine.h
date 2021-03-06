// ������� ��������� �� �������� ����������� "���������� ����������"(��) �������
// ��������(��) ����� ��� �����, �����, ���������...
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

#include<vector>
#include"tbs_interface.h"
#include<string>
// ������ �������� ��������

// ����� NextTurn : ����� ������� �������� �� ������ � ����� ������ NextTurnObj
// ����� ������� �������� ��� �������� EngineInterface � ����� �� ������ NextTurn

// ����� GameLoop : ������������ �������� �����


// ������� ��������� ������� � ����������� ����� ����� ����� SetInterface
class GameObjFactory {

};


// ����� ��������� ������� �������� ������ 
class EngineGameObjInterface {
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in)=0;  // ������� ������� ������� ��� RTTI
	/*virtual void NextTurn()=0;
	virtual void SaveState()=0;
	virtual void LoadState()=0;
	virtual void CreateState(unsigned num_players, unsigned map_size)=0;
	virtual std::string GetSummariesString()=0; // ������ �� ���������� ���
	*/
	public:
	virtual ~EngineGameObjInterface()=0;
};



class Engine: public TbsInterface{
public:
	void NextTurn(); // ��������� ������� �������� ���������� 
	virtual void CreateObjects(); 

};
#endif

