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
	//���ۿ� ���̾ƿ�
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11InputLayout> m_pVertexLayout;

	//���̴�
	ComPtr<ID3D11VertexShader> m_pVS;
	ComPtr<ID3D11PixelShader> m_pPS;

	//RS
	ComPtr<ID3D11RasterizerState> m_pRSNoCull;

	//�׸��� ����
	int m_iPrimType;
	bool m_bWireRender;


public:
	//���� ����
	HRESULT CreateVertexBuffer();
	HRESULT LoadShaderAndInputLayout();

	//RS ���°� ����
	HRESULT SetRS(D3D11_FILL_MODE d3dFillMode = D3D11_FILL_SOLID);

	//�ﰢ�� �׸���
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