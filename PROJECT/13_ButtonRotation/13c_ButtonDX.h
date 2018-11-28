#pragma once
#include "13b_ActorDX.h"

class ButtonDX : public ActorDX
{
public:
	RECT m_rtInit;
	PCT_VERTEX m_vertexList[6];

public:
	D3DXVECTOR3 Get(float x, float y);
	void MoveX(float fDis);
	void MoveY(float fDis);
	void GetCenter();
	void SetVertexData();
	bool SetData(RECT rt);
	bool SetData(UINT left, UINT top, UINT width, UINT height);
	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile);

	bool Init();

public:
	ButtonDX();
	virtual ~ButtonDX();
};