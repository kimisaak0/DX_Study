#include "03_coreC_DX.h"



coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
}

bool coreC_DX::gameInit()
{
	//����̽� ���� �۾� ����.
	InitDevice();
	m_GameTimer.Init();


	//SwapChain�� ����� ������ DXWrite��ü ���� 
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
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
	
	return true;
}

bool coreC_DX::gamePreRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
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
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);

	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);	

	m_Font.SetTextPos();
	m_Font.SetlayoutRt(0, 0, g_uClientWidth, g_uClientHeight);
	m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	m_Font.SetTextColor(ColorF(1, 1, 1, 1));

	_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"), 
		m_GameTimer.GetFPS(), m_GameTimer.GetSPF(), m_GameTimer.GetGameTime() );
	m_Font.DrawText(pBuffer);


	
	m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	//m_Font.SetTextPos(Matrix3x2F::Rotation(g_GameTimer*100, Point2F(400, 300)));
	m_Font.SetTextColor(ColorF(1, 0, 0, 1));

	int iCount = 0;
	if (I_Input.m_bImmediate) {
		for (int iKey = 0; iKey < KeyStateCount; iKey++) {
			if (I_Input.m_KeyCurState[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey] );
				UINT iStartX = g_uClientWidth / 2;
				UINT iStartY = g_uClientHeight / 2 + (30 * iCount);
				m_Font.SetlayoutRt(iStartX, iStartY, g_uClientWidth, g_uClientHeight);
				m_Font.DrawText(pBuffer);

				iCount++;
			}
		}
	}
	else {
	
	}

	for (int iKey = 0; iKey < 4; iKey++) {
		if (I_Input.m_MouseCurState.rgbButtons[iKey] & 0x80) {
			_stprintf_s(pBuffer, _T("Mouse Button State : %02d"), iKey);
			UINT iStartX = g_uClientWidth / 2;
			UINT iStartY = g_uClientHeight / 2 + (30 * iCount);
			m_Font.SetlayoutRt(iStartX, iStartY, g_uClientWidth, g_uClientHeight);
			m_Font.DrawText(pBuffer);

			iCount++;
		}
	}
	
	static LONG MousePosX = I_Input.m_MouseCurState.lX;
	static LONG MousePosY = I_Input.m_MouseCurState.lY;
	static LONG MousePosZ = I_Input.m_MouseCurState.lZ;

	MousePosX += I_Input.m_MouseCurState.lX;
	MousePosY += I_Input.m_MouseCurState.lY;
	MousePosZ += I_Input.m_MouseCurState.lZ;

	_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld, Z:%ld"), MousePosX, MousePosY, MousePosZ);
	
	UINT iStartX = g_uClientWidth / 2;
	UINT iStartY = g_uClientHeight / 2 + (30 * iCount);
	m_Font.SetlayoutRt(iStartX, iStartY, g_uClientWidth, g_uClientHeight);
	m_Font.DrawText(pBuffer);

	return true;
}

bool coreC_DX::gamePostRender()
{
	//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
	//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
	m_Font.DrawTextEnd();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool coreC_DX::gameRelease()
{
	if (!I_Input.Release()) { return false; }
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
