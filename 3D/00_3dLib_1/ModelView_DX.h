#pragma once
#include "inputC_DX.h"
#include "Camera_DX.h"
#include "ArcBall_DX.h"

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