#pragma once
#include "00_header.h"

struct SimpleVertex
{
	float x;
	float y;
	float z;
};

class VertexSample : public coreC_DX
{
protected:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3D11PixelShader* m_pPS2;

	D3D_PRIMITIVE_TOPOLOGY m_PrimType;

public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT LoadShaderAndInputLayout();
	HRESULT CreateTriangle(D3D_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

public:
	bool Init() override;
	bool Render() override;
	bool Release() override;

public:
	VertexSample(LPCTSTR LWndName);
	virtual ~VertexSample();
};