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
		//���� ��ü���� ó�� ������ ���� �Լ���. ���ӿ� ���� �κа� ������ ������ ���� �κ��� �и�
		bool gameInit() override;
		bool gameRun() override;
		bool gameFrame() override;
		bool gamePreRender() override;
		bool gameRender() override;
		bool gamePostRender() override;
		bool gameRelease() override;

	public:
		//Ŭ���� ������ ���� ó�� ������ ���� �Լ���. 
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