#pragma once
#include "02_wndC_DX.h"
#include "04_timerC_DX.h"
#include "05_writeC_DX.h"
#include "06_inputC_DX.h"
#include "12_Shapes_ext.h"
#include "16_ModelView_DX.h"

class coreC_DX : public wndC_DX
{
protected:
	timerC_DX    m_GameTimer;
	writeC_DX    m_Font;
	
	Camera_DX*   m_pMainCamera;
	
	Camera_DX    m_DefaultCamera;
	ModleView_DX m_ModelCamera;

	Dir_Line     m_dirAxis;

	bool m_swTimerRender;
	bool m_swKeyRender;

public:
	bool ResetRT();
	bool SetMainCamera(int i);

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
	coreC_DX(LPCTSTR LWndName);
	virtual ~coreC_DX();
};

