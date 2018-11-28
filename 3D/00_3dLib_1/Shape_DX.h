#pragma once
#include "Obj3d_Header.h"
#include "dxState.h"

//기본 도형 클래스
class Shape_DX
{
protected:
	D3D_PRIMITIVE_TOPOLOGY m_Primitive;

	Obj3d_DX m_dxObj;

	UINT                m_iVertexSize;

	UINT                m_iNumVertex;
	vector<PNCT_VERTEX> m_VertexList;

	UINT                m_iNumIndex;
	vector<DWORD>       m_IndexList;

	T_CB_DATA m_cbData;

public:
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vLook;
	D3DXVECTOR3 m_vSide;
	D3DXVECTOR3 m_vUp;

protected:
	virtual HRESULT CreateVertexData(); 
	virtual HRESULT CreateIndexData();
	
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();

	virtual HRESULT CreateInputLayout();

	virtual HRESULT LoadVertexShader(T_STR szName);
	virtual HRESULT LoadPixelShader(T_STR szName);
	virtual HRESULT LoadGeoShader(T_STR szName);			

	virtual HRESULT LoadTexture(T_STR szName);

public:
	virtual void SetMatrix(D3DXMATRIX* pWorld = nullptr, D3DXMATRIX* pView = nullptr, D3DXMATRIX* pProj = nullptr);
	void SetColor(D3DXVECTOR4 vColor);
	bool Create(T_STR szVSName, T_STR szPSName, T_STR szGSName, T_STR szTextureName);

public:
	virtual bool Init();

	virtual bool Frame();

	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();

	virtual bool Release();

public:
	Shape_DX();
	~Shape_DX();
};