#pragma once
#include "06_inputC_DX.h"
#include "15_Flustum_DX.h"

class Camera_DX : public Flustum_DX
{
public:
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

protected:
	D3DXVECTOR4 m_vYawPitchRoll;

	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vTarget;
	D3DXVECTOR3 m_vDefalutUp;

	D3DXVECTOR3 m_vLook;
	D3DXVECTOR3 m_vSide;
	D3DXVECTOR3 m_vUp;

	float m_fYaw;
	float m_fPitch;

	float m_fFov;
	float m_fAspect;

	float m_fNear;
	float m_fFar;
	
	float m_fSpeed;

public:
	void SetSpeed(float fValue);
	void MoveLook(float fValue);
	void MoveSide(float fValue);

	bool UpdateVector();

	D3DXMATRIX SetViewMatrix(D3DXVECTOR3 vPos = D3DXVECTOR3(0, 0, -10.0f), D3DXVECTOR3 vTarget = D3DXVECTOR3(0, 0, 1), D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0));
	
	D3DXMATRIX SetProjMatrix(float fFov, float fAspect, float fNear = 1.0f, float fFar = 100.0f);
	void       UpdateProjMatrix(UINT width, UINT height);

public:
	virtual bool Frame();
	virtual bool Update();

public:
	Camera_DX();
	virtual ~Camera_DX();
};