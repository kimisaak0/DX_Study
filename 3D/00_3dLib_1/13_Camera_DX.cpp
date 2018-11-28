#include "13_Camera_DX.h"

Camera_DX::Camera_DX()
{
	m_fSpeed = 1.0f;
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	D3DXMatrixIdentity(&m_matWorld);
	m_vYawPitchRoll = { 0, 0, 0, 0 };
}

void Camera_DX::SetSpeed(float fValue)
{
	m_fSpeed += fValue;
}

void Camera_DX::MoveLook(float fValue)
{
	m_vPos += m_vLook * fValue * m_fSpeed;
}

void Camera_DX::MoveSide(float fValue)
{
	m_vPos += m_vSide * fValue * m_fSpeed;
}

bool Camera_DX::UpdateVector()
{
	D3DXMATRIX TView;
	D3DXMatrixTranspose(&TView, &m_matView);

	m_vSide = { TView._11, TView._12, TView._13 };
	m_vUp = { TView._21, TView._22, TView._23 };
	m_vLook = { TView._31, TView._32, TView._33 };

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	D3DXVec3Normalize(&m_vSide, &m_vSide);

	Flustum_DX::SetMatrix(nullptr, &m_matView, &m_matProj);
	Flustum_DX::CreateFlustum();

	return true;
}

D3DXMATRIX Camera_DX::SetViewMatrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
{
	m_vPos = vPos;  
	m_vTarget = vTarget; 
	m_vUp = vUp;
	D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
	UpdateVector();

	// 뷰 행렬을 새로 생성 할 때 1번씩만 호출한다. 
	// 업데이트마다 바꿔주면 카메라가 뒤집어 질 경우에 문제가 생긴다.
	D3DXMATRIX mInvView;
	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	D3DXVECTOR3* pZBasis = (D3DXVECTOR3*)&mInvView._31;

	m_fYaw = atan2f(pZBasis->x, pZBasis->z);
	float fLen = sqrtf(pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x);
	m_fPitch = -atan2f(pZBasis->y, fLen);

	return m_matView;
}

D3DXMATRIX Camera_DX::SetProjMatrix(float fFov, float fAspect, float fNear, float fFar)
{
	m_fFov = fFov; m_fAspect = fAspect; m_fNear = fNear; m_fFar = fFar;
	D3DXMatrixPerspectiveFovLH(&m_matProj, fFov, fAspect, fNear, fFar);

	return m_matProj;
}

void       Camera_DX::UpdateProjMatrix(UINT width, UINT height)
{
	m_fAspect = (float)width / (float)height;
	SetProjMatrix(m_fFov, m_fAspect, m_fNear, m_fFar);
}

bool Camera_DX::Frame()
{
	if (I_Input.IsKeyDown(DIK_W)) {MoveLook(g_dSPF *  5.0f); }
	if (I_Input.IsKeyDown(DIK_S)) {MoveLook(g_dSPF * -5.0f); }
	if (I_Input.IsKeyDown(DIK_A)) {MoveSide(g_dSPF * -5.0f); }
	if (I_Input.IsKeyDown(DIK_D)) {MoveSide(g_dSPF *  5.0f); }

	if (I_Input.getMouseInfo().right == p_HOLD)
	{
		m_vYawPitchRoll.x = 0.1f * (FLOAT)D3DXToRadian(I_Input.m_MouseCurState.lY);
		m_vYawPitchRoll.y = 0.1f * (FLOAT)D3DXToRadian(I_Input.m_MouseCurState.lX);
	}
	float fZValue = (float)I_Input.m_MouseCurState.lZ;
	m_vYawPitchRoll.w = fZValue * g_dSPF;


	m_fSpeed -= g_dSPF;
	if (m_fSpeed < 0.5f) { m_fSpeed = 0.5f; }
	return true;
}

bool Camera_DX::Update()
{
	D3DXMATRIX matRotation;
	D3DXQUATERNION qRotation;
	D3DXQuaternionRotationYawPitchRoll(&qRotation, m_fYaw += m_vYawPitchRoll.y, m_fPitch += m_vYawPitchRoll.x, m_vYawPitchRoll.z);

	m_vPos += m_vLook * m_vYawPitchRoll.w * m_fSpeed;
	D3DXMatrixAffineTransformation(&matRotation, 1.0f, nullptr, &qRotation, &m_vPos);
	D3DXMatrixInverse(&m_matView, nullptr, &matRotation);
	UpdateVector();

	return true;
}


Camera_DX::~Camera_DX()
{

}
