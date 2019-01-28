#include "zCore.h"

namespace Lypi
{
	//float g_dSPF;

	zCore::zCore(LPCTSTR LWndName) : winL(LWndName)
	{
		m_swTimerRender = false;
		m_swKeyRender = false;
	}

	HRESULT zCore::SetRasterizerState()
	{
		HRESULT hr;
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
		desc.DepthClipEnable = TRUE;

		hr = g_pD3dDevice->CreateRasterizerState(&desc, &m_pRSSolid);
		return hr;
	}

	bool zCore::gameInit()
	{
		//����̽� ���� �۾� ����.
		InitDevice();

		//SwapChain�� ����� ������ DXWrite��ü ���� 
		IDXGISurface1* pBackBuffer = nullptr;
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
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

		g_pWindow->CenterWindow(); //�����츦 ȭ�� �߾����� �̵���Ų��.

		//init
		{
			SetRasterizerState();
		}

		Init();


		return true;
	}

	bool zCore::gameRun()
	{
		gameFrame();
		gamePreRender();
		gameRender();
		gamePostRender();
		return true;
	}

	bool zCore::gameFrame()
	{
		m_GameTimer.Frame();

		g_dSPF = m_GameTimer.getSPF();
		I_Input.Frame();

		if (I_Input.IsKeyDownOnce(0x0d)) {
			m_swTimerRender = !m_swTimerRender;
		}

		if (I_Input.IsKeyDownOnce(DIK_0)) {
			m_swKeyRender = !m_swKeyRender;
		}

		Frame();

		return true;
	}

	bool zCore::gamePreRender()
	{
		m_Font.Begin();
		return true;
	}

	bool zCore::gameRender()
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
			m_Font.Drawtxt(pBuffer);
		}

		if (m_swKeyRender) {
			m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			//m_Font.SetTextPos(Matrix3x2F::Rotation(g_GameTimer*100, Point2F(400, 300)));
			m_Font.SetTextColor(ColorF(1, 0.3f, 0, 1));

			int iCount = 0;

			MouseInfo Mouse = I_Input.getMouseInfo();

			_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld"), Mouse.xy.x, Mouse.xy.y);

			UINT iStartX = 0;
			UINT iStartY = 30 + (20 * iCount);
			m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
			m_Font.Drawtxt(pBuffer);
			iCount++;

			for (int iKey = 0; iKey < KeyStateCount; iKey++) {
				if (I_Input.m_KeyCurState[iKey] & 0x80) {
					_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey]);
					UINT iStartX = 0;
					UINT iStartY = 30 + (20 * iCount);
					m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
					m_Font.Drawtxt(pBuffer);

					iCount++;
				}
			}
		}

		//render
		{
			g_pD3dContext->RSSetState(m_pRSSolid);

		}

		Render();

		return true;
	}

	bool zCore::gamePostRender()
	{
		//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
		//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
		m_Font.End();
		g_pSwapChain->Present(0, 0);
		return true;
	}

	bool zCore::gameRelease()
	{
		Release();

		if (!I_Input.Release()) { return false; }
		if (!m_Font.Release()) { return false; }
		if (!m_GameTimer.Release()) { return false; }
		if (!CreanupDevice()) { return false; }
		return true;
	}
	zCore::~zCore()
	{
	}


}