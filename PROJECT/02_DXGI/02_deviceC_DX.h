#pragma once
#include "01_enumCs_DX.h"


class deviceC_DX
{
protected:
	D3D_DRIVER_TYPE            m_d3dDriverType;        // 디바이스 타입 (디폴트 : 하드웨어 가속)
	D3D_FEATURE_LEVEL          m_d3dFeatureLevel;	   // DX의 기능 수준

	ID3D11Device*              m_pD3dDevice;           // 디바이스 객체
	ID3D11DeviceContext*       m_pImmediateContext;	   // 디바이스 컨텍스트
	IDXGIFactory*              m_pGIFactory;		   // DXGI 객체
	IDXGISwapChain*            m_pSwapChain;		   // 스왑체인 객체

	ID3D11RenderTargetView*    m_pRenderTagetView;	   // 메인 렌더타켓 뷰
	D3D11_VIEWPORT             m_d3dViewPort;		   // 뷰포트

protected:
	enumeratoinC_DX    m_enumeratoin;

public:
	//추가 함수
	bool   Start();
	DXGI_MODE_DESC FindClosesMatchingMode(DXGI_MODE_DESC& Desc, ID3D11Device* pd3dDevice);

	//객체 생성
	HRESULT CreateDevice();
	HRESULT	CreateGIFactory();
	HRESULT	CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);
	//뷰 설정
	HRESULT	SetRenderTargetView();
	HRESULT	SetViewPort();

public:
	bool CreanupDevice();

public:
	deviceC_DX();
	virtual ~deviceC_DX();
};