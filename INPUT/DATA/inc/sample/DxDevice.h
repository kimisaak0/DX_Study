#pragma once
#include "stdHeader_L.h"
#include "RenderTarget.h"

namespace Lypi
{
	class DxDevice
	{
	protected:
		D3D_DRIVER_TYPE            m_d3dDriverType;        // ����̽� Ÿ�� (����Ʈ : �ϵ���� ����)
		D3D_FEATURE_LEVEL          m_d3dFeatureLevel;	   // DX�� ��� ����

		IDXGIFactory*              m_pGIFactory;		   // DXGI ��ü
		ID3D11RenderTargetView*    m_pRenderTagetView;	   // ���� ����Ÿ�� ��
		D3D11_VIEWPORT             m_d3dViewPort;		   // ����Ʈ

	public:
		HRESULT CreateDevice();                 // ����̽� �� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
		HRESULT	CreateGIFactory();	 			// IDXGIFactory ��ü ����
		HRESULT	CreateSwapChain();	            // IDXGIFactory�� �̿��Ͽ� ����ü�� ����
		HRESULT	SetRenderTargetView();			// Ÿ�� �� ����
		HRESULT	SetViewPort();     				// �� ��Ʈ ����

	public:
		HRESULT InitDevice();      // ��ġ�� ������� �����Ѵ�.
		bool CreanupDevice();      // ������ ���� �������� �����Ѵ�.

	public:
		DxDevice();
		virtual ~DxDevice(
		);
	};
}