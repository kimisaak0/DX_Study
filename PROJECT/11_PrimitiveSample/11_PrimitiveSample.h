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

class VertexSample : public coreC_DX
{
protected:
	//버퍼와 레이아웃
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11InputLayout> m_pVertexLayout;

	//쉐이더
	ComPtr<ID3D11VertexShader> m_pVS;
	ComPtr<ID3D11PixelShader> m_pPS;

	//RS
	ComPtr<ID3D11RasterizerState> m_pRSNoCull;

	//그리기 형태
	int m_iPrimType;
	bool m_bWireRender;


public:
	//버퍼 생성
	HRESULT CreateVertexBuffer();
	HRESULT LoadShaderAndInputLayout();

	//RS 상태값 지정
	HRESULT SetRS(D3D11_FILL_MODE d3dFillMode = D3D11_FILL_SOLID);

	//삼각형 그리기
	HRESULT CreateTriangle(D3D_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	VertexSample(LPCTSTR LWndName);
	virtual ~VertexSample();
};