#pragma once
#include "00a_ObjStd.h"

class ObjectDX
{
public:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3DBlob* m_pVSBlop;
	ID3DBlob* m_pPSBlop;
	ID3DBlob* m_pErrorBlob;
	ID3D11InputLayout* m_pInputLayout;
	ID3D11ShaderResourceView* m_pTextureSRV;

public:
	UINT m_iNumVertex;
	UINT m_iVertexSize;

public:
	HRESULT CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList, int iNumCount);
	HRESULT CreateVertexShader(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT CreatePixelShader(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT CreateLayout(ID3D11Device* pd3dDevice, ID3DBlob* pVSBlop);
	HRESULT LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile);

public:
	bool PreRender(ID3D11DeviceContext* pContext);
	bool Render(ID3D11DeviceContext* pContext);
	bool PostRender(ID3D11DeviceContext* pContext);
	bool Release();

public:
	ObjectDX();
	virtual ~ObjectDX();
};