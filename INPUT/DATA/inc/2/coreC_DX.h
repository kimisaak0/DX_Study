#pragma once
#include "wndC_DX.h"
#include "timerC_DX.h"
#include "writeC_DX.h"
#include "inputC_DX.h"
#include "Shapes_ext.h"
#include "ModelView_DX.h"
#include "SkyBox.h"

class coreC_DX : public wndC_DX
{
protected:
	timerC_DX    m_GameTimer;
	writeC_DX    m_Font;
	
	Camera_DX*   m_pMainCamera;
	
	Camera_DX    m_DefaultCamera;
	ModleView_DX m_ModelCamera;

	Dir_Line     m_dirAxis;

	SkyBox       m_SkyBox;

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

