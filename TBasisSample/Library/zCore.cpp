#include "zCore.h"

namespace Lypi
{

	zCore::zCore(LPCTSTR LWndName) : winL(LWndName)
	{
	}

	LRESULT	zCore::MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}

	bool zCore::ResetRT()
	{
		IDXGISurface1* pBackBuffer = nullptr;
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);

		m_Font.Set(pBackBuffer);

		if (pBackBuffer) {
			pBackBuffer->Release();
		}

		return true;
	}

	bool zCore::gameInit()
	{
		//����̽� ���� �۾� ����.
		InitDevice();
		m_GameTimer.Init();

		ResetRT();
		g_pWindow->CenterWindow();

		//SwapChain�� ����� ������ DXWrite��ü ���� 
		IDXGISurface1* pBackBuffer = nullptr;
		g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
		m_Font.Init();
		m_Font.Set(pBackBuffer);

		if (pBackBuffer) { pBackBuffer->Release(); }

		I_Input.InitDirectInput(true, true); //DXInput Device ����
		I_Input.Init();	//DXInput �ʱ�ȭ

		//				//���°� ����
		//xDxState::SetState();

		//m_DefaultCamera.SetViewMatrix(); // ����� ����
		//m_DefaultCamera.SetProjMatrix((float)D3DX_PI * 0.5f, ClinetRatio); // ������� ����

		//m_ModelCamera.SetViewMatrix(); // ����� ����
		//m_ModelCamera.SetProjMatrix((float)D3DX_PI * 0.5f, ClinetRatio); // ������� ����

		//m_pMainCamera = &m_DefaultCamera; //���� ī�޶� ����Ʈ ī�޶�� ����

		//m_dirAxis.Create(L"../../INPUT/DATA/shader/vs.hlsl",
		//	L"../../INPUT/DATA/shader/ps.hlsl",
		//	L"../../INPUT/DATA/shader/gs.hlsl",
		//	L"NULL"); //���� �� �����.

		//m_SkyBox.Create(L"../../INPUT/DATA/shader/vs.hlsl",
		//	L"../../INPUT/DATA/shader/ps.hlsl",
		//	L"../../INPUT/DATA/shader/gs.hlsl",
		//	L"NULL",
		//	100.0f);

		Init();

		g_pD3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
		float ClearColor[4] = { 0.1f, 0.2f, 0.3f, 1.0f }; //r,g,b,a
		g_pD3dContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);
		g_pD3dContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		g_pD3dContext->OMSetRenderTargets(1, &m_pRenderTagetView, m_pDepthStencilView);

		//D3D::ApplyDSS(xDxState::g_pDSVStateEnableLessEqual);
		//D3D::ApplyBS(xDxState::g_pBSAlphaBlend);
		//D3D::ApplySS(xDxState::g_pSSWrapLinear);

		//if (I_Input.IsKeyDownOnce(DIK_P)) {
		//	D3D::ApplyRS(xDxState::g_pRSNoneWireFrame);
		//}
		//else {
		//	D3D::ApplyRS(xDxState::g_pRSNoneSolid);
		//}

		DXGI_SWAP_CHAIN_DESC CurrentSD;
		g_pSwapChain->GetDesc(&CurrentSD);

		m_Font.DrawTextBegin();

		//m_SkyBox.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_SkyBox.Render();

		PreRender();

		return true;
	}

	bool zCore::gameRender()
	{
		//m_dirAxis.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_dirAxis.Render();

		Render();

		return true;
	}

	bool zCore::gamePostRender()
	{
		PostRender();

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

		//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
		//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
		m_Font.DrawTextEnd();
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
		if (!m_Font.Release()) { return false; }
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