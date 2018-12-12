#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
	class DxDevice
	{
	protected:
		ID3D11Device*              m_pD3dDevice;           // ����̽� ��ü
		ID3D11DeviceContext*       m_pD3dContext;          // ����̽� ���ؽ�Ʈ ��ü
		IDXGISwapChain*            m_pSwapChain;           // ����ü�� ��ü

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
		
		virtual HRESULT	SetRenderTargetView();	// Ÿ�� �� ����
		virtual HRESULT	SetViewPort();     		// �� ��Ʈ ����

	protected:
		bool CreanupDevice();      // ������ ���� �������� �����Ѵ�.

	public:
		DxDevice();
		virtual ~DxDevice();
	};
}