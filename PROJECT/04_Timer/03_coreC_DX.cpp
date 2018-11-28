#include "03_coreC_DX.h"



coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
}

bool coreC_DX::gameInit()
{
	//����̽� ���� �۾� ����.
	InitDevice();
	m_GameTimer.Init();

	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Init();
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

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
	m_GameTimer.Frame();
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
	float r = 0.21f;
	float g = 0.32f;
	float b = 0.45f;

	float ClearColor[4] = { r, g, b, 0.0f }; //r,g,b,a
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);


	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"), 
		m_GameTimer.GetFPS(), m_GameTimer.GetSPF(), m_GameTimer.GetGameTime() );

	m_Font.setTextFormat(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	
	RECT rc1 = { 0,0, (LONG)g_uClientWidth, (LONG)g_uClientHegiht };
	m_Font.DrawText(rc1, pBuffer, D2D1::ColorF(1, 0, 0, 1)); // a�� ��밡��..?
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
	if (!m_Font.Release()) { return false; }
	if (!m_GameTimer.Release()) { return false; }
	if (!CreanupDevice()) { return false; }
	return true;
}

bool coreC_DX::ResetRT()
{
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	return true;
}


coreC_DX::~coreC_DX()
{
}
