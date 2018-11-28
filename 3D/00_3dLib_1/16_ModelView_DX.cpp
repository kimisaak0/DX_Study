#include "16_ModelView_DX.h"

ModleView_DX::ModleView_DX()
{
	D3DXMatrixIdentity(&m_mModelRot);
	D3DXMatrixIdentity(&m_mModelLastRot);
}

LRESULT	ModleView_DX::MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_LBUTTONDOWN)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnBegin(iMouseX, iMouseY);
	}

	if (msg == WM_MOUSEMOVE)
	{
		short iMouseX = LOWORD(lParam);
		short iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnMove(iMouseX, iMouseY);
	}
	if (msg == WM_LBUTTONUP)
	{
		m_WorldArcBall.OnEnd();
	}

	return 1;
}

bool ModleView_DX::Update()
{
	Camera_DX::Update();

	D3DXMATRIX mModelRot, mModelLastRotInv, mInvView;

	D3DXMatrixInverse(&mInvView, nullptr, &m_matView);
	mInvView._41 = mInvView._42 = mInvView._43 = 0.0f;

	D3DXMatrixInverse(&mModelLastRotInv, nullptr, &m_mModelLastRot);

	mModelRot = m_WorldArcBall.GetRotationMatrix();
	m_mModelRot = m_mModelRot * m_matView * mModelLastRotInv * mModelRot * mInvView;
	m_mModelLastRot = mModelRot;

	m_mModelRot._41 = m_mModelRot._42 = m_mModelRot._43 = 0.0f;
	m_matWorld = m_mModelRot;

	return true;
}


ModleView_DX::~ModleView_DX() { }