#include "03_coreC_DX.h"

#ifndef V_FRETURN
  #define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
}

bool coreC_DX::gameInit()
{
	//����̽� ���� �۾� ����.
	HRESULT hr;
	V_FRETURN(CreateGIFactory());
	V_FRETURN(CreateDevice());
	V_FRETURN(CreateSwapChain(g_hWnd, g_uClientWidth, g_uClientHegiht));
	V_FRETURN(SetRenderTargetView());
	V_FRETURN(SetViewPort());

	return true;
}

bool coreC_DX::gameRun()
{
	gameFrame();
	gamePreRender();
	gameRender();
	gamePostRender();
	return true;
}

bool coreC_DX::gameFrame()
{
	return true;
}

bool coreC_DX::gamePreRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(g_hWnd, &g_rtClient);
	return true;
}

bool coreC_DX::gameRender()
{
	//ID3D11RenderTargetView ��ü�� �÷��� ä���. (BackBuffer�� �����.)
	float ClearColor[4] = { 0.5f, 0.3f, 1.0f, 0.0f }; //r,g,b,a
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);
	return true;
}

bool coreC_DX::gamePostRender()
{
	//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
	//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
	m_pSwapChain->Present(0, 0);
	return true;
}

bool coreC_DX::gameRelease()
{
	if (!CreanupDevice()) { return false; }
	return true;
}

coreC_DX::~coreC_DX()
{
}
