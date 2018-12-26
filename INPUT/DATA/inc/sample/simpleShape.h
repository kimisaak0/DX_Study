#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	class simpleShape   
	{
		// 버텍스 버퍼 및 레이아웃
		ComPtr<ID3D11InputLayout>	  m_pVertexLayout;    //정점 레이아웃 인터페이스
									  
		ComPtr<ID3D11Buffer>          m_pVertexBuffer;    //정점 버퍼 인터페이스
		ComPtr<ID3D11Buffer>          m_pIndexBuffer;     //인덱스 버퍼 인터페이스
		ID3D11Buffer*                 m_pStreamTo;        //SO에서 IA로 되돌릴 버퍼
		ID3D11Buffer*                 m_pDrawFrom;        //출력용 버퍼

		UINT m_uCull_S;
		UINT m_uFill_S;

		// 버텍스 및 픽셀 쉐이더
		ComPtr<ID3D11VertexShader>     m_pVS;    //정점 쉐이더 인터페이스
		ComPtr<ID3D11PixelShader>      m_pPS;	 //픽셀 쉐이더 인터페이스
		ComPtr<ID3D11GeometryShader>   m_pGS;    //기하 쉐이더 인터페이스
		ComPtr<ID3D11GeometryShader>   m_pSO;    //Stream Output Stage용

		ComPtr<ID3D11RasterizerState>  m_pRS;   //래스터라이저 상태

	public:
		HRESULT		CreateVertexBuffer(PC_VERTEX* vertexArray, int aSize);        // 정점 버퍼 생성
		HRESULT     CreateIndexBuffer(DWORD* indexArray, int aSize);         // 인덱스 버퍼 생성
		HRESULT		LoadShaderAndInputLayout();  // 정점 및 픽쉘 쉐이더 로딩 및 생성

		HRESULT		RSChange(); // 래스터라이저 세팅 변경

		HRESULT     HandleEffects(ID3D11Buffer* pBuffer); // 

	public:
		bool Init(PC_VERTEX* vertexArray, int vaSize, DWORD* indexArray, int iaSize);
		bool Frame();
		bool Render();
		bool Release();

	public:
		simpleShape();
		virtual ~simpleShape();
	};
}