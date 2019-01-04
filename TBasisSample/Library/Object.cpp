#include "Object.h"

namespace Lypi
{
	Object::Object()
	{

	}

	bool Object::Init(const TCHAR* pTexFile)
	{
		HRESULT hr;

		// 정점 버퍼 생성
		D3D11_BUFFER_DESC sDesc;
		ZeroMemory(&sDesc, sizeof(D3D11_BUFFER_DESC));
		sDesc.Usage = D3D11_USAGE_DEFAULT;
		sDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		sDesc.ByteWidth = sizeof(PT_VERTEX) * 4;

		D3D11_SUBRESOURCE_DATA sInitData;
		ZeroMemory(&sInitData, sizeof(D3D11_SUBRESOURCE_DATA));
		sInitData.pSysMem = m_pVertexList;

		if (FAILED(hr = g_pD3dDevice->CreateBuffer(&sDesc, &sInitData, &m_pVertexBuffer))) {
			return hr;
		}

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
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		int iNumElement = sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC);

		hr = g_pD3dDevice->CreateInputLayout(ied, iNumElement, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout);
		if (FAILED(hr)) {
			return hr;
		}

		//픽셀 쉐이더 생성
		ID3DBlob*  pPSBlop;
		hr = D3DX11CompileFromFile(L"PixelShader.psh", NULL, NULL, "PS", "ps_5_0", NULL, NULL, NULL, &pPSBlop, &pErrorBlob, NULL);
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

		return true;
	}


	bool Object::Frame()
	{
		
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

		g_pD3dContext->Draw(4, 0);

		return true;
	}

	bool Object::Release()
	{
		return true;
	}




	Object::~Object()
	{

	}
}