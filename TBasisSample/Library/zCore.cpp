#include "zCore.h"

namespace Lypi
{

	zCore::zCore(LPCTSTR LWndName) : winL(LWndName)
	{
		m_swTimerRender = true;
		m_swKeyRender = true;

	}

	LRESULT	zCore::MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}

	bool zCore::ResetRT()
	{
		IDXGISurface1* pBackBuffer = nullptr;
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);

		I_Font.Set(pBackBuffer);

		if (pBackBuffer) {
			pBackBuffer->Release();
		}

		return true;
	}

	HRESULT zCore::CreateDxResource()
	{
		IDXGISurface1* pBackBuffer = nullptr;
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);
		I_Font.Set(g_hWnd, m_rtWindow.right, m_rtWindow.bottom, pBackBuffer);

		if (pBackBuffer) { pBackBuffer->Release(); }

		hr = g_pSwapChain->GetDesc(&m_pSwapChainDesc);
		V_FRETURN(hr);

		hr = m_DefaultRT.UpdateDepthStencilView(m_pSwapChainDesc.BufferDesc.Width, m_pSwapChainDesc.BufferDesc.Height);
		V_FRETURN(hr);

		return CreateResource();
	}

	HRESULT zCore::DeleteDxResource()
	{
		
		return DeleteResource();
	}


	HRESULT zCore::DeleteResource()
	{
		return S_OK;
	}

	HRESULT zCore::CreateResource()
	{
		return S_OK;
	}



	bool zCore::gameInit()
	{
		//디바이스 생성 작업 실행.
		InitDevice();
		m_GameTimer.Init();

		ResetRT();
		g_pWindow->CenterWindow();

		//SwapChain의 백버퍼 정보로 DXWrite객체 생성 
		IDXGISurface1* pBackBuffer = nullptr;
		g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
		I_Font.Init();
		I_Font.Set(pBackBuffer);

		if (pBackBuffer) { pBackBuffer->Release(); }

		I_Input.InitDirectInput(true, true); //DXInput Device 생성
		I_Input.Init();	//DXInput 초기화


		Init();
		g_pD3dContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)g_uPrimType);

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

		I_Input.Frame();
		if (I_Input.IsKeyDownOnce(DIK_9)) { m_swTimerRender = !m_swTimerRender; }
		if (I_Input.IsKeyDownOnce(DIK_0)) { m_swKeyRender = !m_swKeyRender; }

		if (I_Input.IsKeyDownOnce(DIK_F1)) {
			(g_uPrimType + 1 > 5) ? (g_uPrimType = 1) : (g_uPrimType += 1);
		}

		if (I_Input.IsKeyDownOnce(DIK_F2)) {
			(g_uCullMode + 1 > 3) ? (g_uCullMode = 1) : (g_uCullMode += 1);
		}

		if (I_Input.IsKeyDownOnce(DIK_F3)) {
			(g_uFillMode + 1 > 3) ? (g_uFillMode = 2) : (g_uFillMode += 1);
		}

		Frame();

		return true;
	}

	bool zCore::gamePreRender()
	{
		float ClearColor[4] = {0.f, 0.f, 0.f, 1.f }; //r,g,b,a
		g_pD3dContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);
		g_pD3dContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		g_pD3dContext->OMSetRenderTargets(1, &m_pRenderTagetView, m_pDepthStencilView);

		DXGI_SWAP_CHAIN_DESC CurrentSD;
		g_pSwapChain->GetDesc(&CurrentSD);

		I_Font.Begin();

		TCHAR pBuffer[256];
		memset(pBuffer, 0, sizeof(TCHAR) * 256);

		I_Font.SetTextPos();
		I_Font.SetlayoutRt(0, 0, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);

		if (m_swTimerRender) {
			m_GameTimer.Render();
		}

		if (m_swKeyRender) {
			I_Input.Render();
		}

		I_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		I_Font.SetTextColor(ColorF(0.0f, 0.0f, 0.0f, 1.0f));

		TCHAR TopologyBuffer[256];
		ZeroMemory(TopologyBuffer, sizeof(TCHAR) * 256);

		switch (g_uPrimType) {
			case 1: { _tcscpy_s(TopologyBuffer, L"POINTLIST"); } break;
			case 2: { _tcscpy_s(TopologyBuffer, L"LINELIST"); } break;
			case 3: { _tcscpy_s(TopologyBuffer, L"LINESTRIP"); } break;
			case 4: { _tcscpy_s(TopologyBuffer, L"TRIANGLELIST"); } break;
			case 5: { _tcscpy_s(TopologyBuffer, L"TRIANGLESTRIP"); } break;
		}

		TCHAR CullModeBuffer[256];
		ZeroMemory(CullModeBuffer, sizeof(TCHAR) * 256);

		switch (g_uCullMode) {
			case 1: { _tcscpy_s(CullModeBuffer, L"CULL_NONE"); } break;
			case 2: { _tcscpy_s(CullModeBuffer, L"CULL_FRONT"); } break;
			case 3: { _tcscpy_s(CullModeBuffer, L"CULL_BACK"); } break;
		}

		TCHAR FillModeBuffer[256];
		ZeroMemory(FillModeBuffer, sizeof(TCHAR) * 256);

		switch (g_uFillMode) {
			case 2: { _tcscpy_s(FillModeBuffer, L"WIREFRAME"); } break;
			case 3: { _tcscpy_s(FillModeBuffer, L"SOLID"); } break;
		}

		_stprintf_s(pBuffer, L"%s\n%s\n%s", TopologyBuffer, CullModeBuffer, FillModeBuffer);

		I_Font.Drawtxt(pBuffer);

		////IDXGISwapChain 객체를 사용하여 시연(출력)한다.
		////모든 렌더링 작업들은 present앞에서 이뤄져야 한다.
		I_Font.End();

		PreRender();

		return true;
	}

	bool zCore::gameRender()
	{

		Render();

		return true;
	}

	bool zCore::gamePostRender()
	{
		PostRender();

		g_pSwapChain->Present(0, 0);
		return true;
	}

	bool zCore::gameRelease()
	{
		Release();

		if (!I_Input.Release()) { return false; }
		if (!I_Font.Release()) { return false; }
		if (!m_GameTimer.Release()) { return false; }

		if (!CreanupDevice()) { return false; }

		return true;
	}


	zCore::~zCore()
	{
	}

}