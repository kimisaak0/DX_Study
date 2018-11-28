#include "11_PrimitiveSample.h"

VertexSample::VertexSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pVertexBuffer  = nullptr;
	m_pVertexLayout  = nullptr;
	m_pVS            = nullptr;
	m_pPS            = nullptr;
	m_pRSNoCull      = nullptr;
	m_bWireRender    = false;
	m_iPrimType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


HRESULT VertexSample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	SimpleVertex vertices[] = {
		{ 0.f,   1.f, 0.f },
		{ 0.95f, 0.31f, 0.f },
		{ 0.59f,-0.81f, 0.f },
		{ -0.59f,-0.81f, 0.f },
		{ -0.95f, 0.31f, 0.f },
		{ 0.f,   1.f, 0.f },

	};

	UINT numVertices = (sizeof(vertices) / sizeof(vertices[0]));

	CD3D11_BUFFER_DESC cbc(sizeof(SimpleVertex) * numVertices, D3D11_BIND_VERTEX_BUFFER);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	
	V_FRETURN(g_pD3dDevice->CreateBuffer(&cbc, &InitData, m_pVertexBuffer.GetAddressOf()));

	return hr;
}


HRESULT VertexSample::SetRS(D3D11_FILL_MODE d3dFillMode)
{
	HRESULT hr = S_OK;

	D3D11_RASTERIZER_DESC RSDesc;
	ZeroMemory(&RSDesc, sizeof(D3D11_RASTERIZER_DESC));
	RSDesc.DepthClipEnable = TRUE;
	RSDesc.FillMode = d3dFillMode;
	RSDesc.CullMode = D3D11_CULL_NONE;

	V_FRETURN(g_pD3dDevice->CreateRasterizerState(&RSDesc, &m_pRSNoCull));

	return hr;
}

HRESULT VertexSample::LoadShaderAndInputLayout()
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	ID3DBlob* pVSBuf = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("Vertex.vsh"), NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, NULL, NULL));
	V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), NULL, &m_pVS));

	ID3DBlob* pPSBuf = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("Pixel.psh"), NULL, NULL, "PS", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf, NULL, NULL));
	V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &m_pPS));

	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pVertexLayout));

	SAFE_RELEASE(pVSBuf);
	SAFE_RELEASE(pPSBuf);

	SetRS();

	return hr;
}

HRESULT VertexSample::CreateTriangle(D3D_PRIMITIVE_TOPOLOGY topology)
{
	HRESULT hr = S_OK;

	V_FRETURN(CreateVertexBuffer());
	V_FRETURN(LoadShaderAndInputLayout());

	return hr;
}


bool VertexSample::Init()
{
	if (FAILED(CreateTriangle())) {
		MessageBox(0, _T("CreateTrangle ½ÇÆÐ"), _T("Fatal error"), MB_OK);
		return false;
	}

	return true;
}

bool VertexSample::Frame()
{
	BYTE temp = 0;

	if ( temp = I_Input.IsKeyDownOnce(0x02)) {
		m_bWireRender = !m_bWireRender;
		(m_bWireRender) ? SetRS(D3D11_FILL_WIREFRAME) : SetRS(D3D11_FILL_SOLID);
	}

	if (temp = I_Input.IsKeyDownOnce(0x03)) {
		++m_iPrimType;
		if (m_iPrimType > 5) {
			m_iPrimType = 1;
		}

		g_pD3dContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_iPrimType);
	}

	return true;
}

bool VertexSample::Render()
{
	g_pD3dContext->IASetInputLayout(m_pVertexLayout.Get());
	
	g_pD3dContext->VSSetShader(m_pVS.Get(), NULL, 0);
	g_pD3dContext->PSSetShader(m_pPS.Get(), NULL, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	g_pD3dContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	g_pD3dContext->RSSetState(m_pRSNoCull.Get());
	
	g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_iPrimType);

	g_pD3dContext->Draw(6, 0);

	return true;
}

bool VertexSample::Release()
{
	return true;
}


VertexSample::~VertexSample()
{

}