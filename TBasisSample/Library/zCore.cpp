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

		//상태값 설정
		//xDxState::SetState();

		//m_DefaultCamera.SetViewMatrix(); // 뷰행렬 설정
		//m_DefaultCamera.SetProjMatrix((float)D3DX_PI * 0.5f, ClinetRatio); // 투영행렬 설정

		//m_ModelCamera.SetViewMatrix(); // 뷰행렬 설정
		//m_ModelCamera.SetProjMatrix((float)D3DX_PI * 0.5f, ClinetRatio); // 투영행렬 설정

		//m_pMainCamera = &m_DefaultCamera; //메인 카메라를 디폴트 카메라로 설정

		//m_dirAxis.Create(L"../../INPUT/DATA/shader/vs.hlsl",
		//	L"../../INPUT/DATA/shader/ps.hlsl",
		//	L"../../INPUT/DATA/shader/gs.hlsl",
		//	L"NULL"); //기준 선 만들기.

		//m_SkyBox.Create(L"../../INPUT/DATA/shader/vs.hlsl",
		//	L"../../INPUT/DATA/shader/ps.hlsl",
		//	L"../../INPUT/DATA/shader/gs.hlsl",
		//	L"NULL",
		//	100.0f);

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

		//m_pMainCamera->Frame();
		//m_pMainCamera->Update();

		//m_SkyBox.Frame();

		Frame();

	/*	m_dirAxis.Frame();*/

		return true;
	}

	bool zCore::gamePreRender()
	{
		float ClearColor[4] = {1.f, 1.f, 1.f, 1.f }; //r,g,b,a
		g_pD3dContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);
		g_pD3dContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		g_pD3dContext->OMSetRenderTargets(1, &m_pRenderTagetView, m_pDepthStencilView);

		DXGI_SWAP_CHAIN_DESC CurrentSD;
		g_pSwapChain->GetDesc(&CurrentSD);

		I_Font.DrawTextBegin();

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

		I_Font.SetlayoutRt(0, 0, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
		I_Font.Drawtxt(pBuffer);

		////IDXGISwapChain 객체를 사용하여 시연(출력)한다.
		////모든 렌더링 작업들은 present앞에서 이뤄져야 한다.
		I_Font.DrawTextEnd();

		PreRender();

		return true;
	}

	bool zCore::gameRender()
	{
		//m_SkyBox.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_SkyBox.Render();

		//m_dirAxis.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_dirAxis.Render();

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

		//if (!m_ModelCamera.Release()) { return false; }
		//if (!m_DefaultCamera.Release()) { return false; }

		//if (!m_SkyBox.Release()) { return false; }
		if (!I_Input.Release()) { return false; }
		if (!I_Font.Release()) { return false; }
		if (!m_GameTimer.Release()) { return false; }
		//if (!m_dirAxis.Release()) { return false; }
		//if (!xDxState::Release()) { return false; }
		if (!CreanupDevice()) { return false; }

		return true;
	}


	zCore::~zCore()
	{
	}

}