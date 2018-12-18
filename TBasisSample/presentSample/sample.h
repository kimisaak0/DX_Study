#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{
	struct V3
	{
		float x, y, z;
	};

	class Sample : public zCore
	{
		// 버텍스 버퍼 및 레이아웃
		ID3D11Buffer*         m_pVertexBuffer;    //정점 버퍼 인터페이스
		ID3D11Buffer*         m_pIndexBuffer;     //인덱스 버퍼 인터페이스
		ID3D11InputLayout*	  m_pVertexLayout;    //정점 레이아웃 인터페이스

		// 버텍스 및 픽셀 쉐이더
		ID3D11VertexShader*     m_pVS;   //정점 쉐이더 인터페이스
		ID3D11PixelShader*      m_pPS;	 //픽셀 쉐이더 인터페이스
		ID3D11GeometryShader*   m_pGS;   //기하 쉐이더 인터페이스
	
		// 이미지 디버그용
		UINT    m_uPrimType;    //토폴로지 타입
		UINT    m_uCullMode;    //컬링모드
		UINT    m_uFillMode;    //와이어 프레임만 렌더링

		ID3D11RasterizerState*      m_pRS;   //래스터라이저 상태

	public:
		HRESULT		CreateVertexBuffer();        // 정점 버퍼 생성
		HRESULT     CreateIndexBuffer();         // 인덱스 버퍼 생성
		HRESULT		LoadShaderAndInputLayout();  // 정점 및 픽쉘 쉐이더 로딩 및 생성
		HRESULT		RSChange();                  // 래스터라이저 세팅 변경

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Sample(LPCTSTR LWndName);
		virtual ~Sample();
	};

}

//namespace Lypi
//{
//
//
//	class Sample :public zCore
//	{
//	public:
//		//--------------------------------------------------------------------------------------
//		// 버텍스 버퍼 및 레이아웃
//		//--------------------------------------------------------------------------------------
//		ID3D11InputLayout*		m_pVertexLayout;
//		ID3D11Buffer*           m_pVertexBuffer;
//		ID3D11Buffer*			m_pIndexBuffer;
//
//		//--------------------------------------------------------------------------------------
//		// 버텍스 및 픽셀 쉐이더
//		//--------------------------------------------------------------------------------------
//		ID3D11VertexShader*     m_pVS;
//		ID3D11PixelShader*      m_pPS;
//		ID3D11GeometryShader*   m_pGS;
//
//		//--------------------------------------------------------------------------------------
//		// 디버그용으로 사용하는 상태 변수
//		//--------------------------------------------------------------------------------------
//		bool					m_bWireFrameRender;
//		int						m_iPrimitiveType;
//
//		//--------------------------------------------------------------------------------------
//		// 버텍스 및 픽셀 쉐이더
//		//--------------------------------------------------------------------------------------
//		ID3D11RasterizerState*      m_pRasterizerStateNoCull;
//
//	public:
//		bool		Init();
//		bool		Render();
//		bool		Release();
//		//--------------------------------------------------------------------------------------
//		// 정점 및 픽쉐 쉐이덩 로딩 및 생성
//		//--------------------------------------------------------------------------------------
//		HRESULT		LoadShaderAndInputLayout();
//		//--------------------------------------------------------------------------------------
//		// 정점 버퍼 생성
//		//--------------------------------------------------------------------------------------
//		HRESULT		CreateVertexBuffer();
//		//--------------------------------------------------------------------------------------
//		// 레스터라이저 상태값 지정
//		//--------------------------------------------------------------------------------------
//		HRESULT		SetRasterizerState(D3D11_FILL_MODE d3dFillMode = D3D11_FILL_SOLID);
//		//--------------------------------------------------------------------------------------
//		// WndProc : Sample 클래스 멤버함수
//		//--------------------------------------------------------------------------------------
//		LRESULT             MsgProcA(HWND, UINT, WPARAM, LPARAM);
//	public:
//		Sample(LPCTSTR LWndName);
//		virtual ~Sample();
//	};
//
//}