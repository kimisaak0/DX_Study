#pragma once
#include "00_header_DX.h"

//------------------------------------------------------------------------------------//
//-DX11 Device�� �����Ѵ�. -----------------------------------------------------------// 
//-wndC_DX���� DX11�� ��� ������ ���� �����ϱ� ���ؼ� deviceC_DX�� �� ���� �ִ�.-----//
//------------------------------------------------------------------------------------//

class deviceC_DX
{
protected:
	D3D_DRIVER_TYPE            m_d3dDriverType;        // ����̽� Ÿ�� (����Ʈ : �ϵ���� ����)
	D3D_FEATURE_LEVEL          m_d3dFeatureLevel;	   // DX�� ��� ����

	IDXGIFactory*              m_pGIFactory;		   // DXGI ��ü
	ID3D11RenderTargetView*    m_pRenderTagetView;	   // ���� ����Ÿ�� ��
	
	ID3D11Texture2D*           m_pDepthStencilBuffer;  // ���� ���ٽ� ����
	ID3D11DepthStencilView*    m_pDepthStencilView;    // ���� ���ٽ� ��

	D3D11_VIEWPORT             m_d3dViewPort;		   // �� ��Ʈ

	UINT                       m_i4XMsaaQuality;
	bool                       m_4XMsaaSw;

public:
	HRESULT CreateDevice();                 // ����̽� �� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	HRESULT	CreateGIFactory();	 			// IDXGIFactory ��ü ����
	HRESULT	CreateSwapChain();	            // IDXGIFactory�� �̿��Ͽ� ����ü�� ����
//	HRESULT CreateDpethStencilView();       // ���� ���ٽ� �� ����
	HRESULT	SetRenderTargetView();			// Ÿ�� �� ����
	HRESULT	SetViewPort();     				// �� ��Ʈ ����

public:
	HRESULT InitDevice();      // ��ġ�� ������� �����Ѵ�.
	bool CreanupDevice();      // ������ ���� �������� �����Ѵ�.

public:
	deviceC_DX();
	virtual ~deviceC_DX(

	);
};