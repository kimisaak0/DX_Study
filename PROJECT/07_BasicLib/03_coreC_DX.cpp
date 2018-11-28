#include "03_coreC_DX.h"



coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
	m_swTimerRender = false;
	m_swKeyRender = false;
}

//HRESULT coreC_DX::SetRasterizerState()
//{
//	HRESULT hr;
//	D3D11_RASTERIZER_DESC desc;
//	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
//	desc.FillMode = D3D11_FILL_SOLID;
//	desc.CullMode = D3D11_CULL_NONE;
//	desc.DepthClipEnable = TRUE;
//
//	hr = g_pD3dDevice->CreateRasterizerState(&desc, &m_pRSSolid);
//	return hr;
//}


bool coreC_DX::gameInit()
{
	//����̽� ���� �۾� ����.
	InitDevice();
	m_GameTimer.Init();

	g_pWindow->CenterWindow();

	//SwapChain�� ����� ������ DXWrite��ü ���� 
	IDXGISurface1* pBackBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Init();
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	//DXInput Device ����
	if (!I_Input.InitDirectInput(true, true)) {
		return false;
	}
	
	//DXInput �ʱ�ȭ
	if (!I_Input.Init()) {
		return false;
	}

	//g_pD3dContext->RSSetState(m_pRSSolid);

	Init();

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

	if (!I_Input.Frame()) { return false; }
	
	if (I_Input.IsKeyDownOnce(0x0d)) {
		m_swTimerRender = !m_swTimerRender;
	}

	if (I_Input.IsKeyDownOnce(DIK_0)) {
		m_swKeyRender = !m_swKeyRender;
	}

	Frame();

	return true;
}

bool coreC_DX::gamePreRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	g_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(g_hWnd, &g_rtClient);

	m_Font.DrawTextBegin();
	return true;
}

bool coreC_DX::gameRender()
{
	//ID3D11RenderTargetView ��ü�� �÷��� ä���. (BackBuffer�� �����.)
	float r = 0.21f;
	float g = 0.32f;
	float b = 0.45f;

	float ClearColor[4] = { r, g, b, 0.0f }; //r,g,b,a
	g_pD3dContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);

	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);	

	m_Font.SetTextPos();
	m_Font.SetlayoutRt(0, 0, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);

	if (m_swTimerRender) {
		m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		m_Font.SetTextColor(ColorF(1, 1, 1, 1));

		_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"),
			m_GameTimer.getFPS(), m_GameTimer.getSPF(), m_GameTimer.getGameTime());
		m_Font.DrawText(pBuffer);
	}

	if (m_swKeyRender) {
		m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		//m_Font.SetTextPos(Matrix3x2F::Rotation(g_GameTimer*100, Point2F(400, 300)));
		m_Font.SetTextColor(ColorF(1, 0, 0, 1));

		int iCount = 0;

		static LONG MousePosX = I_Input.m_MouseCurState.lX;
		static LONG MousePosY = I_Input.m_MouseCurState.lY;
		static LONG MousePosZ = I_Input.m_MouseCurState.lZ;

		MousePosX += I_Input.m_MouseCurState.lX;
		MousePosY += I_Input.m_MouseCurState.lY;
		MousePosZ += I_Input.m_MouseCurState.lZ;

		_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld, Z:%ld"), MousePosX, MousePosY, MousePosZ);

		FLOAT iStartX = 0;
		FLOAT iStartY = (FLOAT)(50 + (20 * iCount));
		m_Font.SetlayoutRt(iStartX, iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
		m_Font.DrawText(pBuffer);
		iCount++;

		for (int iKey = 0; iKey < KeyStateCount; iKey++) {
			if (I_Input.m_KeyCurState[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey]);
				UINT iStartX = 0;
				UINT iStartY = 50 + (20 * iCount);
				m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
				m_Font.DrawText(pBuffer);

				iCount++;
			}
		}

		for (int iKey = 0; iKey < 4; iKey++) {
			if (I_Input.m_MouseCurState.rgbButtons[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Mouse Button State : %02d"), iKey);
				UINT iStartX = 0;
				UINT iStartY = 50 + (20 * iCount);
				m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
				m_Font.DrawText(pBuffer);

				iCount++;
			}
		}
	}
	
	Render();

	return true;
}

bool coreC_DX::gamePostRender()
{
	//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
	//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
	m_Font.DrawTextEnd();
	g_pSwapChain->Present(0, 0);
	return true;
}

bool coreC_DX::gameRelease()
{
	Release();
	if (!I_Input.Release()) { return false; }
	if (!m_Font.Release()) { return false; }
	if (!m_GameTimer.Release()) { return false; }
	if (!CreanupDevice()) { return false; }
	return true;
}

bool coreC_DX::ResetRT()
{
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	return true;
}


coreC_DX::~coreC_DX()
{
}
