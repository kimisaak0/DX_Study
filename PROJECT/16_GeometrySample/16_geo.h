#pragma once
#include "00_header.h"

using namespace Microsoft; 
using namespace WRL;

struct SimpleVertex
{
	float x;
	float y;
	float z;
};

class GeoSample : public coreC_DX
{
protected:
	
	//버퍼와 레이아웃
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11InputLayout> m_pVertexLayout;
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

	//쉐이더
	ComPtr<ID3D11VertexShader> m_pVS;
	ComPtr<ID3D11PixelShader> m_pPS;
	ComPtr<ID3D11GeometryShader> m_pGS;

	//RS
	ComPtr<ID3D11RasterizerState> m_pRSNoCull;

	//그리기 형태 (디버그용)
	int m_iPrimType;
	bool m_bWireRender;


public:
	//RS 상태값 지정
	HRESULT SetRS(D3D11_FILL_MODE d3dFillMode = D3D11_FILL_WIREFRAME);

	//버퍼 생성
	HRESULT CreateVertexBuffer();
	HRESULT LoadShaderAndInputLayout();

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	GeoSample(LPCTSTR LWndName);
	virtual ~GeoSample();
};