#pragma once
#include "00_header_DX.h"

class timerC_DX
{
private:
	LARGE_INTEGER  m_liFrequency;  //초당 주파수
	LARGE_INTEGER  m_liCurTime;    //현재 프레임에서의 시간
	LARGE_INTEGER  m_liBefTime;    //이전 프레임에서의 시간
	LARGE_INTEGER  m_liBef1sTime;  //1초전 시간

	double         m_dSPF;         //1프레임당 시간
	int            m_iFPS;         //1초당 프레임
	int            m_iFPSGether;   //초당 프레임 누적용

	double         m_dGameTime;    //게임 진행 시간

	//개별 타이머는 타이머 클래스를 상속받아서 만드는걸로...

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