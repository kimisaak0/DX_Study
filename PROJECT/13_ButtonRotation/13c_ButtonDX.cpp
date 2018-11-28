#include "13c_ButtonDX.h"

ButtonDX::ButtonDX()
{
}

D3DXVECTOR3 ButtonDX::Get(float x, float y)
{
	D3DXVECTOR3 vRet;

	vRet.x = x / 1360;
	vRet.y = y / 917;

	vRet.x = vRet.x * 2.0f - 1.0f;
	vRet.y = -(vRet.y * 2.0f - 1.0f);

	return vRet;
}

void ButtonDX::GetCenter()
{
	m_v3Center.x = 0.0f;
	m_v3Center.y = 0.0f;

	for (int iV = 0; iV < 6; iV++) {
		D3DXVECTOR3 vertex = m_vertexList[iV].p;
		m_v3Center.x += vertex.x;
		m_v3Center.y += vertex.y;
	}

	m_v3Center.x /= 6.0f;
	m_v3Center.y /= 6.0f;
}

void ButtonDX::SetVertexData()
{
	D3DXVECTOR3 pos;
	
	pos = Get(m_rtInit.left, m_rtInit.top);
	m_vertexList[0].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_vertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	pos = Get(m_rtInit.left + m_rtInit.right, m_rtInit.top);
	m_vertexList[1].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_vertexList[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	pos = Get(m_rtInit.left, m_rtInit.top + m_rtInit.bottom);
	m_vertexList[2].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[2].t = D3DXVECTOR2(0.0f, 1.0f);
	m_vertexList[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	m_vertexList[3] = m_vertexList[2];

	m_vertexList[4] = m_vertexList[1];

	pos = Get(m_rtInit.left + m_rtInit.right, m_rtInit.top + m_rtInit.bottom);
	m_vertexList[5].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[5].t = D3DXVECTOR2(1.0f, 1.0f);
	m_vertexList[5].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	GetCenter();

}

void ButtonDX::MoveX(float fDis)
{
	for (int iV = 0; iV < 6; iV++) {
		m_vertexList[iV].p.x += fDis;
	}

	GetCenter();
}

void ButtonDX::MoveY(float fDis)
{
	for (int iV = 0; iV < 6; iV++) {
		m_vertexList[iV].p.y += fDis;
	}

	GetCenter();
}


bool ButtonDX::SetData(RECT rt)
{
	m_rtInit.left = rt.left;
	m_rtInit.right = rt.right;
	m_rtInit.top = rt.top;
	m_rtInit.bottom = rt.bottom;

	SetVertexData();

	return true;
}

bool ButtonDX::SetData(UINT left, UINT top, UINT width, UINT height)
{
	RECT rt;
	rt.left = left;
	rt.top = top;
	rt.right = width;
	rt.bottom = height;

	SetData(rt);

	return true;
}

bool ButtonDX::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	m_dxObj.CreateVertexBuffer(pd3dDevice, m_vertexList, 6);
	m_dxObj.CreateVertexShader(pd3dDevice, pVsFile);
	m_dxObj.CreatePixelShader(pd3dDevice, pPsFile);
	m_dxObj.CreateLayout(pd3dDevice, m_dxObj.m_pVSBlop);
	m_dxObj.LoadTexture(pd3dDevice, pTexFile);

	return true;
}

bool ButtonDX::Init()
{
	return true;
}



ButtonDX::~ButtonDX()
{
}