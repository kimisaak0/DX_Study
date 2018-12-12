#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
	class DxDevice
	{
	protected:
		ID3D11Device*              m_pD3dDevice;           // 디바이스 객체
		ID3D11DeviceContext*       m_pD3dContext;          // 디바이스 컨텍스트 객체
		IDXGISwapChain*            m_pSwapChain;           // 스왑체인 객체

		D3D_DRIVER_TYPE            m_d3dDriverType;        // 디바이스 타입 (디폴트 : 하드웨어 가속)
		D3D_FEATURE_LEVEL          m_d3dFeatureLevel;	   // DX의 기능 수준

		IDXGIFactory*              m_pGIFactory;		   // DXGI 객체
		ID3D11RenderTargetView*    m_pRenderTagetView;	   // 메인 렌더타켓 뷰
		ID3D11DepthStencilView*    m_pDepthStencilView;    // 깊이 스텐실 뷰

		D3D11_VIEWPORT             m_d3dViewPort;		   // 뷰 포트

	protected:
		//디바이스 생성
		HRESULT InitDevice();                   // 장치를 순서대로 생성한다.

		HRESULT CreateDevice();                 // 디바이스 및 디바이스 컨텍스트를 생성한다.
		HRESULT	CreateGIFactory();	 			// IDXGIFactory 객체 생성
		HRESULT	CreateSwapChain();	            // IDXGIFactory를 이용하여 스왑체인 생성
		HRESULT CreateDpethStencilView();       // 깊이 스텐실 뷰 생성
		
		virtual HRESULT	SetRenderTargetView();	// 타겟 뷰 설정
		virtual HRESULT	SetViewPort();     		// 뷰 포트 설정

	protected:
		bool CreanupDevice();      // 생성한 것을 역순으로 삭제한다.

	public:
		DxDevice();
		virtual ~DxDevice();
	};
}