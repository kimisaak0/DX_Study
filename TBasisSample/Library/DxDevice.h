#pragma once
#include "stdHeader_L.h"
#include "RenderTarget.h"

namespace Lypi
{
	class DxDevice
	{
	protected:
		RenderTarget               m_DefaultRT;

		ID3D11Device*              m_pD3dDevice;           // ����̽� ��ü
		ID3D11DeviceContext*       m_pD3dContext;          // ����̽� ���ؽ�Ʈ ��ü
		IDXGISwapChain*            m_pSwapChain;           // ����ü�� ��ü
		DXGI_SWAP_CHAIN_DESC       m_pSwapChainDesc;

		D3D_DRIVER_TYPE            m_d3dDriverType;        // ����̽� Ÿ�� (����Ʈ : �ϵ���� ����)
		D3D_FEATURE_LEVEL          m_d3dFeatureLevel;	   // DX�� ��� ����

		IDXGIFactory*              m_pGIFactory;		   // DXGI ��ü
		ID3D11RenderTargetView*    m_pRenderTagetView;	   // ���� ����Ÿ�� ��
		ID3D11DepthStencilView*    m_pDepthStencilView;    // ���� ���ٽ� ��

		D3D11_VIEWPORT             m_d3dViewPort;		   // �� ��Ʈ

	protected:
		//����̽� ����
		HRESULT InitDevice();                   // ��ġ�� ������� �����Ѵ�.

		HRESULT CreateDevice();                 // ����̽� �� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
		HRESULT	CreateGIFactory();	 			// IDXGIFactory ��ü ����
		HRESULT	CreateSwapChain();	            // IDXGIFactory�� �̿��Ͽ� ����ü�� ����
		HRESULT CreateDpethStencilView();       // ���� ���ٽ� �� ����
		
		HRESULT	SetRenderTargetView();	// Ÿ�� �� ����
		HRESULT	SetViewPort();     		// �� ��Ʈ ����

	public:
		bool CreanupDevice();      // ������ ���� �������� �����Ѵ�.

		ID3D11RenderTargetView*	    GetRenderTargetView() { return m_DefaultRT.m_pRTV.Get(); }
		ID3D11RenderTargetView**	GetRenderTargetViewAddress() { return  m_DefaultRT.m_pRTV.GetAddressOf(); }
		ID3D11DepthStencilView*		GetDepthStencilView() { return m_DefaultRT.m_pDSV.Get(); }
		ID3D11DepthStencilView**	GetDepthStencilViewAddress() { return  m_DefaultRT.m_pDSV.GetAddressOf(); }

	public:
		DxDevice();
		virtual ~DxDevice();
	};
}