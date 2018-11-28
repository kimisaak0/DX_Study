#pragma once
#include "00_header.h"

//정점 버퍼 구조체
struct SimpleVertex
{
	float x;
	float y;
	float z;
	float w;
};

class VertexSample : public coreC_DX
{
protected:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;

public:
	HRESULT CreateVertexBuffer();  // 정점 버퍼 생성
	HRESULT LoadShaderAndInputLayout();  //쉐이더 컴파일 및 입력 레이아웃 생성


public:
	bool Init() override;
	bool Render() override;
	bool Release() override;

public:
	VertexSample(LPCTSTR LWndName);
	virtual ~VertexSample();
};