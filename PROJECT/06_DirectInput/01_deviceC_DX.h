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

	ID3D11Device*              m_pD3dDevice;           // ����̽� ��ü
	ID3D11DeviceContext*       m_pImmediateContext;	   // ����̽� ���ؽ�Ʈ
	IDXGIFactory*              m_pGIFactory;		   // DXGI ��ü
	IDXGISwapChain*            m_pSwapChain;		   // ����ü�� ��ü

	ID3D11RenderTargetView*    m_pRenderTagetView;	   // ���� ����Ÿ�� ��
	D3D11_VIEWPORT             m_d3dViewPort;		   // ����Ʈ

	BOOL m_bFullScrFlag; //Ǯ��ũ�� ���� ����ġ


public:
	HRESULT CreateDevice();                                         // ����̽� �� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	HRESULT	CreateGIFactory();										// IDXGIFactory ��ü ����
	HRESULT	CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);	// IDXGIFactory�� �̿��Ͽ� ����ü�� ����

	HRESULT	SetRenderTargetView();									// Ÿ�� �� ����
	HRESULT	SetViewPort();     										// �� ��Ʈ ����

	//������ ����
public:
	ID3D11Device *           getDevice();
	ID3D11DeviceContext*   	 getContext();
	IDXGIFactory*          	 getGIFactory();
	IDXGISwapChain*          getSwapChain();
	ID3D11RenderTargetView*	 getRenderTargetView();

	//Ǯ��ũ�� ����
public:
	bool GetFullScrFlag();
	void SetFullScrFlag(bool bFlag);

public:
	HRESULT InitDevice();      // ��ġ�� ������� �����Ѵ�.
	bool CreanupDevice();      // ������ ���� �������� �����Ѵ�.

	//ȭ�� ũ�Ⱑ ����Ǹ� �׿� ���缭 ���۹��� ũ�⸦ �����ϰ� �׿� �´� ����Ʈ�� �ٽ� �����Ѵ�.
	HRESULT ResizeDevice(UINT iWidth, UINT iHeight);

public:
	deviceC_DX();
	virtual ~deviceC_DX(

	);
};