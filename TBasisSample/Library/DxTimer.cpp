#include "DxTimer.h"

namespace Lypi
{
	float g_dSPF;

	DxTimer::DxTimer()
	{
		m_liFrequency.QuadPart = 0;
		m_liCurTime.QuadPart = 0;
		m_liBefTime.QuadPart = 0;
		m_liBef1sTime.QuadPart = 0;

		m_iFPSGether = 0;

		m_BefTickTime.QuadPart = 0;
		m_curTickTime.QuadPart = 0;

		//시스템의 주파수 변동폭을 얻어옴 //
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_liFrequency);
	}

	bool	DxTimer::Init()
	{
		//일단 카운터 가져오기
		QueryPerformanceCounter(&m_liBefTime);
		QueryPerformanceCounter(&m_liBef1sTime);
		QueryPerformanceCounter(&m_BefTickTime);

		//타이머 지원 여부 확인
		if (m_liBefTime.QuadPart == 0) {
			return false;
		}

		m_iFPSGether = 0;

		return true;
	}

	bool	DxTimer::Frame()
	{
		//현재 시간 확인
		QueryPerformanceCounter(&m_liCurTime);
		m_dSPF = static_cast<float>(m_liCurTime.QuadPart - m_liBefTime.QuadPart) / static_cast<float>(m_liFrequency.QuadPart);
		g_dSPF = m_dSPF;
		m_liBefTime = m_liCurTime;

		m_dGameTime += m_dSPF;

		static double fpsPivot;

		fpsPivot += m_dSPF;
		m_iFPSGether++;
		if (fpsPivot >= 1.0)
		{
			m_iFPS = m_iFPSGether;
			m_iFPSGether = 0;
			fpsPivot -= 1.0;
		}

		return true;
	}

	bool	DxTimer::Render()
	{
		I_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		I_Font.SetTextColor(ColorF(0, 0, 1, 1));

		TCHAR pBuffer[256];
		memset(pBuffer, 0, sizeof(TCHAR) * 256);

		_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"),
			m_iFPS, m_dSPF, m_dGameTime);
	
		I_Font.Drawtxt(pBuffer);

		return true;
	}
	bool	DxTimer::Release()
	{
		return true;
	}

	bool    DxTimer::tickAlram(double tick)
	{
		QueryPerformanceCounter(&m_curTickTime);
		if (((m_curTickTime.LowPart - m_BefTickTime.LowPart) / (m_liFrequency.LowPart)) >= tick) {
			m_BefTickTime = m_curTickTime;
			return true;
		}
		return false;
	}


	float  DxTimer::getGameTime()
	{
		return m_dGameTime;
	}
	float  DxTimer::getSPF()
	{
		return m_dSPF;
	}
	int     DxTimer::getFPS()
	{
		return m_iFPS;
	}

	DxTimer::~DxTimer()
	{

	}
}