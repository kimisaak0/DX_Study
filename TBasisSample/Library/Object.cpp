#include "Object.h"

namespace Lypi
{
	Object::Object()
	{

	}

	void    Object::VertexSetting(uint3 center, uWH size)
	{
		m_center = center;
		m_HarpWidth  = size.width  / 2;
		m_HarpHeight = size.height / 2;

		m_uSRegion.left	   = center.x - m_HarpWidth;
		m_uSRegion.top     = center.y - m_HarpHeight;
		m_uSRegion.right   = center.x + m_HarpWidth;
		m_uSRegion.bottom  = center.y + m_HarpHeight;

		m_fPRegion.left    =  1.0f * ( (m_uSRegion.left   / (float)g_rtClient.right)  * 2 - 1.0f);
		m_fPRegion.top     = -1.0f * ( (m_uSRegion.top    / (float)g_rtClient.bottom) * 2 - 1.0f);
		m_fPRegion.right   =  1.0f * ( (m_uSRegion.right  / (float)g_rtClient.right)  * 2 - 1.0f);
		m_fPRegion.bottom  = -1.0f * ( (m_uSRegion.bottom / (float)g_rtClient.bottom) * 2 - 1.0f );

		m_pVertexList[0].p = D3DXVECTOR3( m_fPRegion.left,  m_fPRegion.top,     0.0f );
		m_pVertexList[1].p = D3DXVECTOR3( m_fPRegion.left,  m_fPRegion.bottom,  0.0f );
		m_pVertexList[2].p = D3DXVECTOR3( m_fPRegion.right, m_fPRegion.top,     0.0f );
		m_pVertexList[3].p = D3DXVECTOR3( m_fPRegion.right, m_fPRegion.bottom,  0.0f );

		for (int pl = 0; pl < 4; pl++) {
			m_pVertexList[pl].c = D3DXVECTOR4(1, 1, 1, 1);
		}

		m_pVertexList[0].t = D3DXVECTOR2(0, 0);
		m_pVertexList[1].t = D3DXVECTOR2(0, 1);
		m_pVertexList[2].t = D3DXVECTOR2(1, 0);
		m_pVertexList[3].t = D3DXVECTOR2(1, 1);
	}

	HRESULT Object::Create(const TCHAR* pTexFile, uint3 center, uWH size)
	{
		HRESULT hr = S_OK;

		VertexSetting(center, size);

		// CD3D11_BUFFER_DESC : 버퍼 크기와 버퍼 용도만 결정하면 나머지는 기본값으로 생성해주는 구조체.
		CD3D11_BUFFER_DESC cbc(sizeof(PCT_VERTEX) * 4, D3D11_BIND_VERTEX_BUFFER);

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(D3D11_SUBRESOURCE_DATA));
		InitData.pSysMem = m_pVertexList;

		V_FRETURN(g_pD3dDevice->CreateBuffer(&cbc, &InitData, &m_pVertexBuffer));

		//정점 쉐이더 생성
		ID3DBlob*  pErrorBlob;
		ID3DBlob*  pVSBlob;

		hr = D3DX11CompileFromFile(L"VS.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, NULL, NULL, &pVSBlob, &pErrorBlob, NULL);
		if (FAILED(hr)) {
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			return false;
		}

		hr = g_pD3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVS);
		if (FAILED(hr)) {
			return hr;
		}

		//레이아웃 생성
		if (pVSBlob == NULL) { return E_FAIL; }

		D3D11_INPUT_ELEMENT_DESC ied[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		int iNumElement = sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC);

		hr = g_pD3dDevice->CreateInputLayout(ied, iNumElement, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout);
		if (FAILED(hr)) {
			return hr;
		}

		//픽셀 쉐이더 생성
		ID3DBlob*  pPSBlop;
		hr = D3DX11CompileFromFile(L"PS.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, NULL, NULL, &pPSBlop, &pErrorBlob, NULL);
		if (FAILED(hr)) {
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			return false;
		}

		hr = g_pD3dDevice->CreatePixelShader(pPSBlop->GetBufferPointer(), pPSBlop->GetBufferSize(), NULL, &m_pPS);
		if (FAILED(hr)) {
			SAFE_RELEASE(pPSBlop);
			return NULL;
		}

		SAFE_RELEASE(pErrorBlob);
		SAFE_RELEASE(pPSBlop);
		SAFE_RELEASE(pVSBlob);

		//블렌드 스테이트 생성
		D3D11_BLEND_DESC BlendState;
		ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));

		BlendState.AlphaToCoverageEnable = FALSE;
		BlendState.IndependentBlendEnable = FALSE;

		BlendState.RenderTarget[0].BlendEnable = TRUE;

		BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (FAILED(hr = g_pD3dDevice->CreateBlendState(&BlendState, &m_pAlphaBlend)))
		{
			return hr;
		}

		//텍스쳐 로드
		hr = D3DX11CreateShaderResourceViewFromFile(g_pD3dDevice, pTexFile, NULL, NULL, &m_pTextureSRV, NULL);
		if (FAILED(hr)) {
			return hr;
		}

		return hr;
	}

	bool Object::Init(const TCHAR* pTexFile, uint3 center, uWH size)
	{
		Create(pTexFile, center, size);
		return true;
	}


	bool Object::Frame()
	{
		g_pD3dContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList, 0, 0);
		return true;
	}

	bool Object::Render()
	{
		UINT pStrides = sizeof(PCT_VERTEX);
		UINT pOffsets = 0;

		g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &pStrides, &pOffsets);
		g_pD3dContext->IASetInputLayout(m_pInputLayout);
		g_pD3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		g_pD3dContext->VSSetShader(m_pVS, NULL, NULL);
		g_pD3dContext->PSSetShader(m_pPS, NULL, NULL);
		g_pD3dContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
		g_pD3dContext->OMSetBlendState(m_pAlphaBlend, 0, -1);

		g_pD3dContext->Draw(4, 0);

		return true;
	}

	bool Object::Release()
	{
		SAFE_RELEASE(m_pVertexBuffer);
		SAFE_RELEASE(m_pVS);
		SAFE_RELEASE(m_pPS);
		SAFE_RELEASE(m_pInputLayout);
		SAFE_RELEASE(m_pTextureSRV);

		return true;
	}




	Object::~Object()
	{

	}
}