#pragma once
#include "00_header_DX.h"

struct FlustumPlane
{
	float x, y, z, d;

	void Create(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	void Create(D3DXVECTOR3 v0, D3DXVECTOR3 vNormal);

	FlustumPlane();
	virtual ~FlustumPlane();
};

class Flustum_DX
{
private:
	D3DXMATRIX m_mWorld;
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;

public:
	FlustumPlane  m_Plane[6];
	D3DXVECTOR3   m_vVertex[8];

public:
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	
	bool CreateFlustum();
	bool ClassifyPoint(D3DXVECTOR3 v);
	bool ClassifySphere(D3DXVECTOR3 v, float fRadius);

public:
	Flustum_DX();
	virtual ~Flustum_DX();
};