#pragma once
#include "06_inputC_DX.h"
#include "13_Camera_DX.h"
#include "14_ArcBall_DX.h"

class ModleView_DX : public Camera_DX
{
	ArcBall_DX m_WorldArcBall;

	D3DXMATRIX m_mModelRot;
	D3DXMATRIX m_mModelLastRot;

public:
	LRESULT	MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Update() override;

public:
	ModleView_DX();
	virtual ~ModleView_DX();
};