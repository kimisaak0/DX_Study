#pragma once
#include "stdHeader_L.h"
#include "DxWrite.h"

namespace Lypi
{
	class DxTimer
	{
	private:
		LARGE_INTEGER  m_liFrequency;  //�ʴ� ���ļ�
		LARGE_INTEGER  m_liCurTime;    //���� �����ӿ����� �ð�
		LARGE_INTEGER  m_liBefTime;    //���� �����ӿ����� �ð�
		LARGE_INTEGER  m_liBef1sTime;  //1���� �ð�

		float m_dGameTime;
		float m_dSPF;
		int   m_iFPS;

		int   m_iFPSGether;   //�ʴ� ������ ������

							  
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