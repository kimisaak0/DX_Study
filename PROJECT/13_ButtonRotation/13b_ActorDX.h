#pragma once
#include "13a_ObjectDX.h"

class ActorDX
{
public:
	ObjectDX m_dxObj;
	D3DXVECTOR3 m_v3Center;

public:
	virtual bool Init();
	virtual bool Frame(float fGameTimer, float fFps);
	virtual bool PreRender(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool PostRender(ID3D11DeviceContext* pContext);
	virtual bool Release();

public:
	ActorDX();
	virtual ~ActorDX();
};