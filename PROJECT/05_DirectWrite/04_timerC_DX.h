#pragma once
#include "00_header_DX.h"

class timerC_DX
{
private:
	LARGE_INTEGER  m_liFrequency;  //�ʴ� ���ļ�
	LARGE_INTEGER  m_liCurTime;    //���� �����ӿ����� �ð�
	LARGE_INTEGER  m_liBefTime;    //���� �����ӿ����� �ð�
	LARGE_INTEGER  m_liBef1sTime;  //1���� �ð�

	double         m_dSPF;         //1�����Ӵ� �ð�
	int            m_iFPS;         //1�ʴ� ������
	int            m_iFPSGether;   //�ʴ� ������ ������

	double         m_dGameTime;    //���� ���� �ð�

	//���� Ÿ�̸Ӵ� Ÿ�̸� Ŭ������ ��ӹ޾Ƽ� ����°ɷ�...

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	// get
	double	         GetSPF();
	int		         GetFPS();
	double           GetGameTime();
	LARGE_INTEGER    GetCurrent();

public:
	timerC_DX();
	virtual ~timerC_DX();
};