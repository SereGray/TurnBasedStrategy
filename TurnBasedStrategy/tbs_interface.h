// ����������� �����
// ����������� ������� (�����������) ����� ���� ����� ���������� ��������������
// �� � �������� (���������� ������� ��� �� ������),������������� � ���������
// �������� �������� � ������ ������� �� ���������
// 
//  �������� �������� ����������:
//  �.�. �������� ������(������), ������ �������� ( ����� �����)
//  ������ ���������(��������������) ��� ��� ���� ��������( ����� �� �.� (����������� �����))
//  �.�. ������������� ������ ��� ��
//
#ifndef TBS_INTERFACE   // ������ �� �������������� ���������
#define TBS_INTERFACE

//      TODO: EngineInterface vs TbsInterface �������� ������� ������� �� �� ����������� ����� �������� ��������


// ����� �������������� ������� �������� � ��� ����� ����� ���������� �� ����� � ���� � ���� � �. �.
class TbsInterface {/*
	virtual void CreateObjects()=0; // ������������� ������
	virtual void GetGameObjList(); // �������� ������ ������� ��������
	virtual void View(); // ����������� ( ������ �.�)
	virtual void SendMess(); // ���� ��������� ��� ���� ������ �����
	virtual void GetDifference(); // �������� ������� ��������� ������� ��� �������� �� ����
	virtual void SendMessDiff(); //(����)���� ��������� ��� ���� � ����������� ��� �������� ����
	*/
public:
	virtual ~TbsInterface()=0;
	
   // TODO: for AI methods
	// �������� ���������� ������ ����� �����������
	// �������� ������ ���������� ���
	// ���� ����� �������
	// ��� �������� ����� ���
};



#endif
