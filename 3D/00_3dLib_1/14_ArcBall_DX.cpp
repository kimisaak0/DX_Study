#include "14_ArcBall_DX.h"

ArcBall_DX::ArcBall_DX()
{
	m_bDrag = false;
	
	m_vDownPt = { 0,0,0 };
	m_vCurrPt = { 0,0,0 };
	
	D3DXQuaternionIdentity(&m_qNow);
	D3DXQuaternionIdentity(&m_qDown);
}

D3DXMATRIX     ArcBall_DX::GetRotationMatrix()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &m_qNow);
	return matRot;
}

D3DXQUATERNION ArcBall_DX::GetQurtFromBallPt(D3DXVECTOR3 m_vDownPt, D3DXVECTOR3 m_vCurrPt)
{
	float fDot = D3DXVec3Dot(&m_vDownPt, &m_vCurrPt);
	D3DXVECTOR3 vPart;
	D3DXVec3Cross(&vPart, &m_vDownPt, &m_vCurrPt);
	D3DXQUATERNION qRet(vPart.x, vPart.y, vPart.z, fDot);
	return qRet;
}
D3DXVECTOR3    ArcBall_DX::GetScreenVector(float fX, float fY)
{
	//구의 방정식 이용
	float fHalfX = g_rtClient.right / 2.0f;
	float fHalfY = g_rtClient.bottom / 2.0f;
	float x = -(fX - fHalfX) / fHalfX;
	float y = -(fY - fHalfY) / fHalfY;
	float z = 0.f;
	float fXY = x * x + y * y;
	if (fXY > 1.0f) {
		x *= (1.0f / sqrtf(fXY));
		y *= (1.0f / sqrtf(fXY));
	}
	else {
		z = sqrtf(1.0f - fXY);
	}

	return D3DXVECTOR3(x, y, z);
}

void ArcBall_DX::OnBegin(int x, int y)
{
	m_bDrag = true;
	m_qDown = m_qNow;
	m_vDownPt = GetScreenVector((float)x, (float)y);
}

void ArcBall_DX::OnMove(int x, int y)
{
	if (m_bDrag) {
		m_vCurrPt = GetScreenVector((float)x, (float)y);
		m_qNow = m_qDown * GetQurtFromBallPt(m_vDownPt, m_vCurrPt);
	}
}

void ArcBall_DX::OnEnd()
{
	m_bDrag = false;
}


ArcBall_DX::~ArcBall_DX() { }
