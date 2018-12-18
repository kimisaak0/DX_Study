#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{

	class Sample : public zCore
	{
		// 버텍스 버퍼 및 레이아웃
		ID3D11Buffer*         m_pVertexBuffer;    //정점 버퍼 인터페이스
		ID3D11Buffer*         m_pIndexBuffer;    //인덱스 버퍼 인터페이스
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