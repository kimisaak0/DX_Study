#pragma once
#include "stdHeader_L.h"
#include "DxWrite.h"

namespace Lypi
{
	class DxTimer
	{
	private:
		LARGE_INTEGER  m_liFrequency;  //초당 주파수
		LARGE_INTEGER  m_liCurTime;    //현재 프레임에서의 시간
		LARGE_INTEGER  m_liBefTime;    //이전 프레임에서의 시간
		LARGE_INTEGER  m_liBef1sTime;  //1초전 시간

		float m_dGameTime;
		float m_dSPF;
		int   m_iFPS;

		int   m_iFPSGether;   //초당 프레임 누적용

							  
		LARGE_INTEGER m_BefTickTime;
		LARGE_INTEGER m_curTickTime;

	public:
		bool	Init();
		bool	Frame();
		bool	Render();
		bool	Release();

		bool    tickAlram(double tick);

		float  getGameTime();
		float  getSPF();
		int     getFPS();
	public:
		DxTimer();
		virtual ~DxTimer();
	};
}