#pragma once
#include "00_header.h"

struct SimpleVertex
{
	float x;
	float y;
	float z;
};

struct VSCB
{
	D3DXVECTOR4 vColor;

	float fTime;
	float fy;
	float fz;
	float fw;
};

class VertexSample : public coreC_DX
{
protected:
	//���ۿ� ���̾ƿ�
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	//���̴�
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3D11PixelShader* m_pPS2;

	//�׸��� ����
	D3D_PRIMITIVE_TOPOLOGY m_PrimType;

public:
	//���� ����
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateContantBuffer();

	HRESULT LoadShaderAndInputLayout();

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