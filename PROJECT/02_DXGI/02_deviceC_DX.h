#pragma once
#include "01_enumCs_DX.h"


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

protected:
	enumeratoinC_DX    m_enumeratoin;

public:
	//�߰� �Լ�
	bool   Start();
	DXGI_MODE_DESC FindClosesMatchingMode(DXGI_MODE_DESC& Desc, ID3D11Device* pd3dDevice);

	//��ü ����
	HRESULT CreateDevice();
	HRESULT	CreateGIFactory();
	HRESULT	CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);
	//�� ����
	HRESULT	SetRenderTargetView();
	HRESULT	SetViewPort();

public:
	bool CreanupDevice();

public:
	deviceC_DX();
	virtual ~deviceC_DX();
};