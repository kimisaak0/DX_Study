#pragma once
#include "WinL.h"
#include "DxWrite.h"
#include "DxTimer.h"
#include "DxInput.h"

namespace Lypi
{
	class zCore : public winL
	{
	protected:
		DxTimer    m_GameTimer;
		DxWrite    m_Font;


		bool m_swTimerRender;
		bool m_swKeyRender;
	public:
		bool ResetRT();
	//	bool SetMainCamera(int i);

	public:
		//게임 전체적인 처리 순서에 대한 함수들. 게임에 관한 부분과 윈도우 생성에 관한 부분을 분리
		bool gameInit() override;
		bool gameRun() override;
		bool gameFrame() override;
		bool gamePreRender() override;
		bool gameRender() override;
		bool gamePostRender() override;
		bool gameRelease() override;

	public:
		//클래스 각각에 대한 처리 순서에 관한 함수들. 
		virtual bool Init() { return true; };
		virtual bool Frame() { return true; };
		virtual bool PreRender() { return true; };
		virtual bool Render() { return true; };
		virtual bool PostRender() { return true; };
		virtual bool Release() { return true; };

		LRESULT	MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		zCore(LPCTSTR LWndName);
		virtual ~zCore();
	};

}