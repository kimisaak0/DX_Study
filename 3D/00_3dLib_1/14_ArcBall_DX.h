#pragma once
#include "00_header_DX.h"

class ArcBall_DX
{
private:
	bool m_bDrag;

	D3DXVECTOR3 m_vDownPt;
	D3DXVECTOR3 m_vCurrPt;

	D3DXQUATERNION m_qNow;
	D3DXQUATERNION m_qDown;

public:
	D3DXMATRIX GetRotationMatrix();
	D3DXQUATERNION GetQurtFromBallPt(D3DXVECTOR3 m_vDownPt, D3DXVECTOR3 m_vCurrPt);
	D3DXVECTOR3 GetScreenVector(float fX, float fY);

	void OnBegin(int x, int y);
	void OnMove(int x, int y);
	void OnEnd();

public:
	ArcBall_DX();
	virtual ~ArcBall_DX();
};