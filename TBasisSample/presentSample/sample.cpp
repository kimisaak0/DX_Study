#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
	
		m_pVertexLayout = nullptr;
	
		m_pVS = nullptr;
		m_pGS = nullptr;
		m_pPS = nullptr;
	
		m_uPrimType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_uCullMode = D3D11_CULL_BACK;
		m_uFillMode = D3D11_FILL_SOLID;
	}

	HRESULT Sample::LoadShaderAndInputLayout()
	{
		HRESULT hr = S_OK;
	
		ID3DBlob* pErrors = nullptr;
	
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	
#if defined( _DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* pVSBuf = nullptr;
		V_FRETURN(D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/VS.hlsl", nullptr, nullptr, "VS", "vs_5_0", dwShaderFlags, NULL, nullptr, &pVSBuf, &pErrors, nullptr));
		V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), nullptr, &m_pVS));

		ID3DBlob* pGSBuf = nullptr;
		V_FRETURN(D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/GS.hlsl", nullptr, nullptr, "GS", "gs_5_0", dwShaderFlags, NULL, nullptr, &pGSBuf, &pErrors, nullptr));
		V_FRETURN(g_pD3dDevice->CreateGeometryShader((DWORD*)pGSBuf->GetBufferPointer(), pGSBuf->GetBufferSize(), nullptr, &m_pGS));

		ID3DBlob* pPSBuf = nullptr;
		V_FRETURN(D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/PS.hlsl", nullptr, nullptr, "PS", "ps_5_0", dwShaderFlags, NULL, nullptr, &pPSBuf, &pErrors, nullptr));
		V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), nullptr, &m_pPS));

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//정점쉐이더안의 POSITION시멘틱의 의미를 지정.
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pVertexLayout));

		SAFE_RELEASE(pVSBuf);
		SAFE_RELEASE(pGSBuf);
		SAFE_RELEASE(pPSBuf);
		SAFE_RELEASE(pErrors);

		RSChange();
		return hr;
	}

	HRESULT		Sample::RSChange()
	{
		HRESULT hr = S_OK;
		SAFE_RELEASE(m_pRS);
	
		D3D11_RASTERIZER_DESC RSDesc;
		ZeroMemory(&RSDesc, sizeof(D3D11_RASTERIZER_DESC));
		RSDesc.DepthClipEnable = TRUE;
		RSDesc.FillMode = (D3D11_FILL_MODE)m_uFillMode;
		RSDesc.CullMode = (D3D11_CULL_MODE)m_uCullMode;
		V_FRETURN(g_pD3dDevice->CreateRasterizerState(&RSDesc, &m_pRS));
	
		return hr;
	}


	HRESULT Sample::CreateVertexBuffer()
	{
	
		HRESULT hr = S_OK;
	
		//시계 방향으로 지정할 것.
		V3 vertices[] =
		{
			{-1.0f, +1.0f, 0.5f},
			{+1.0f, +1.0f, 0.5f},
			{+1.0f, -1.0f, 0.5f},
			{-1.0f, -1.0f, 0.5f},
		};
	
		UINT numVertices = sizeof(vertices) / sizeof(vertices[0]);
		//// CD3D11_BUFFER_DESC : 버퍼 크기와 버퍼 용도만 결정하면 나머지는 기본값으로 생성해주는 구조체.
		CD3D11_BUFFER_DESC cbc(sizeof(V3) * numVertices, D3D11_BIND_VERTEX_BUFFER);
	
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
	
		V_FRETURN(g_pD3dDevice->CreateBuffer(&cbc, &InitData, &m_pVertexBuffer));
		return hr;
	}
	
	HRESULT Sample::CreateIndexBuffer()
	{
		HRESULT hr = S_OK;
	
		DWORD indices[] =
		{
			0,1,2,
			0,2,3,
		};
	
		UINT iNumIndex = sizeof(indices) / sizeof(indices[0]);
	
		// Create an Index Buffer
		CD3D11_BUFFER_DESC cib(iNumIndex * sizeof(DWORD), D3D11_BIND_INDEX_BUFFER);
	
		D3D11_SUBRESOURCE_DATA ibInitData;
		ZeroMemory(&ibInitData, sizeof(D3D11_SUBRESOURCE_DATA));
		ibInitData.pSysMem = indices;
	
		V_FRETURN(g_pD3dDevice->CreateBuffer(&cib, &ibInitData, &m_pIndexBuffer));
	
		return hr;

	}

	bool Sample::Init()
	{
		if (FAILED(CreateVertexBuffer()))
		{
			MessageBox(0, _T("CreateTrangle  실패"), _T("Fatal error"), MB_OK);
			return false;
		}

		if (FAILED(CreateIndexBuffer()))
		{
			MessageBox(0, _T("CreateTrangle2  실패"), _T("Fatal error"), MB_OK);
			return false;
		}

		if (FAILED(LoadShaderAndInputLayout()))
		{
			MessageBox(0, _T("CreateTrangle  실패"), _T("Fatal error"), MB_OK);
			return false;
		}
		return true;
	}

	bool Sample::Frame()
	{
		if (I_Input.IsKeyDownOnce(DIK_F1)) {
			(m_uPrimType + 1 > 5) ? (m_uPrimType = 1) : (m_uPrimType += 1);
		}

		if (I_Input.IsKeyDownOnce(DIK_F2)) {
			(m_uCullMode + 1 > 3) ? (m_uCullMode = 1) : (m_uCullMode += 1);
			RSChange();
		}

		if (I_Input.IsKeyDownOnce(DIK_F3)) {
			(m_uFillMode + 1 > 3) ? (m_uFillMode = 2) : (m_uFillMode += 1);
			RSChange();
		}

		return true;
	}

	bool Sample::Render()
	{
		m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		m_Font.SetTextColor(ColorF(0.0f, 0.0f, 0.0f, 1.0f));
		m_Font.SetlayoutRt(0, 0, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
	
		TCHAR TopologyBuffer[256];
		ZeroMemory(TopologyBuffer, sizeof(TCHAR) * 256);
	
		switch (m_uPrimType) {
			case 1: { _tcscpy_s(TopologyBuffer, L"POINTLIST"); } break;
			case 2: { _tcscpy_s(TopologyBuffer, L"LINELIST"); } break;
			case 3: { _tcscpy_s(TopologyBuffer, L"LINESTRIP"); } break;
			case 4: { _tcscpy_s(TopologyBuffer, L"TRIANGLELIST"); } break;
			case 5: { _tcscpy_s(TopologyBuffer, L"TRIANGLESTRIP"); } break;
		}
	
		TCHAR CullModeBuffer[256];
		ZeroMemory(CullModeBuffer, sizeof(TCHAR) * 256);
	
		switch (m_uCullMode) {
			case 1: { _tcscpy_s(CullModeBuffer, L"CULL_NONE"); } break;
			case 2: { _tcscpy_s(CullModeBuffer, L"CULL_FRONT"); } break;
			case 3: { _tcscpy_s(CullModeBuffer, L"CULL_BACK"); } break;
		}
	
		TCHAR FillModeBuffer[256];
		ZeroMemory(FillModeBuffer, sizeof(TCHAR) * 256);
	
		switch (m_uFillMode) {
			case 2: { _tcscpy_s(FillModeBuffer, L"WIREFRAME"); } break;
			case 3: { _tcscpy_s(FillModeBuffer, L"SOLID"); } break;
		}
	
		TCHAR pBuffer[256];
		ZeroMemory(pBuffer, sizeof(TCHAR) * 256);
	
		_stprintf_s(pBuffer, L"%s\n%s\n%s", TopologyBuffer, CullModeBuffer, FillModeBuffer);
	
		m_Font.DrawText(pBuffer);
	
		// Shaders
		g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
		g_pD3dContext->GSSetShader(m_pGS, NULL, 0);
		g_pD3dContext->PSSetShader(m_pPS, NULL, 0);
	
		// Set the input layout
		g_pD3dContext->IASetInputLayout(m_pVertexLayout);
	
		UINT stride = sizeof(V3);
		UINT offset = 0;
	
		// Set vertex buffer
		g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		g_pD3dContext->RSSetState(m_pRS);
		g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_uPrimType);
		
		g_pD3dContext->DrawIndexed(6, 0, 0);
		//g_pD3dContext->DrawAuto();
		return true;
	}


	bool Sample::Release()
	{
		SAFE_RELEASE(m_pVertexBuffer);    // 정점 버퍼 릴리즈
	
		SAFE_RELEASE(m_pVertexLayout);    // 정점 레이아웃 릴리즈
	
		SAFE_RELEASE(m_pVS);              // 정점 쉐이더 릴리즈
		SAFE_RELEASE(m_pGS);              // 기하 쉐이더 릴리즈
		SAFE_RELEASE(m_pPS);              // 픽쉘 쉐이더 릴리즈
	
		SAFE_RELEASE(m_pRS);
	
		return true;
	}



	Sample::~Sample(void)
	{
	}


}





