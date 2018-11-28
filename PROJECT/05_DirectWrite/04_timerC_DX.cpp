#include "04_timerC_DX.h"

double g_GameTimer = 0;

timerC_DX::timerC_DX()
{
	m_liFrequency.QuadPart = 0;
	m_liCurTime.QuadPart = 0;
	m_liBefTime.QuadPart = 0;
	m_liBef1sTime.QuadPart = 0;

	m_dSPF     	  = 0;
	m_iFPS        = 0;
	m_iFPSGether  = 0;
	m_dGameTime   = 0;
	

	//시스템의 주파수 변동폭을 얻어옴 //
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_liFrequency);
}

bool	timerC_DX::Init()
{
	//일단 카운터 가져오기
	QueryPerformanceCounter(&m_liBefTime);
	QueryPerformanceCounter(&m_liBef1sTime);

	//타이머 지원 여부 확인
	if (m_liBefTime.QuadPart == 0) {
		return false;
	}

	m_dSPF         = 0;
	m_iFPS         = 0;
	m_iFPSGether   = 0;
	m_dGameTime    = 0;
	
	return true;

}

bool	timerC_DX::Frame()
{
	//타이머 정밀도
	double precision = 0.001;

	//현재 시간 확인
	QueryPerformanceCounter(&m_liCurTime);
	m_dSPF = static_cast<double>(m_liCurTime.QuadPart - m_liBefTime.QuadPart) / static_cast<double>(m_liFrequency.QuadPart);

	if (((m_liCurTime.LowPart-m_liBefTime.LowPart) / (m_liFrequency.LowPart/1000) ) >= precision) {
		m_liBefTime = m_liCurTime;
		m_dGameTime += precision;
		g_GameTimer = m_dGameTime;
	}

	if (((m_liCurTime.LowPart - m_liBef1sTime.LowPart) / (m_liFrequency.LowPart)) >= 1.0) {
		m_liBef1sTime = m_liCurTime;
		m_iFPS = m_iFPSGether;
		m_iFPSGether = 0;
	}


	m_iFPSGether++;

	return true;
}
bool	timerC_DX::Render()
{
	return true;
}
bool	timerC_DX::Release()
{
	return true;
}

// get
double	timerC_DX::GetSPF()
{
	return m_dSPF;
}
int		timerC_DX::GetFPS()
{
	return m_iFPS;
}

double           timerC_DX::GetGameTime()
{
	return m_dGameTime;
}
LARGE_INTEGER    timerC_DX::GetCurrent()
{
	return m_liCurTime;
}

timerC_DX::~timerC_DX()
{

}