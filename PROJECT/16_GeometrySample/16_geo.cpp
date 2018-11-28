#include "16_geo.h"

GeoSample::GeoSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pRSNoCull = nullptr;
	m_bWireRender = false;
	m_iPrimType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

HRESULT GeoSample::SetRS(D3D11_FILL_MODE d3dFillMode)
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

HRESULT GeoSample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	hr = g_pD3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))       return hr;

	// Create an Index Buffer
	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = 6 * sizeof(DWORD);
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;

	DWORD indices[] =
	{
		0,1,2,
		0,2,3,
	};

	D3D11_SUBRESOURCE_DATA ibInitData;
	ZeroMemory(&ibInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibInitData.pSysMem = indices;
	V_FRETURN(g_pD3dDevice->CreateBuffer(&ibDesc, &ibInitData, &m_pIndexBuffer));
	return hr;
}

HRESULT GeoSample::LoadShaderAndInputLayout()
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ComPtr<ID3DBlob> pErrorBuf = nullptr;

	ComPtr<ID3DBlob> pVSBuf = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("Vertex.vsh"), NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, &pErrorBuf, NULL));
	V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), NULL, &m_pVS));

	ComPtr<ID3DBlob> pPSBuf = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("Pixel.psh"), NULL, NULL, "PS", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf, &pErrorBuf, NULL));
	V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &m_pPS));

	ComPtr<ID3DBlob> pGSBuf = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("geo.gsh"), NULL, NULL, "GS", "gs_5_0", dwShaderFlags, NULL, NULL, &pGSBuf, &pErrorBuf, NULL));
	V_FRETURN(g_pD3dDevice->CreateGeometryShader((DWORD*)pGSBuf->GetBufferPointer(), pGSBuf->GetBufferSize(), NULL, &m_pGS));

	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pVertexLayout));

	SetRS();

	return hr;
}

bool GeoSample::Init()
{
	if (FAILED(CreateVertexBuffer())) {
		MessageBox(0, _T("정점 생성 실패"), _T("fatal error"), MB_OK);
		return false;
	}

	if (FAILED(LoadShaderAndInputLayout())) {
		MessageBox(0, _T("쉐이더 생성 실패"), _T("fatal error"), MB_OK);
		return false;
	}

	return true;
}

bool GeoSample::Frame()
{
	BYTE temp = 0;

	if (temp = I_Input.IsKeyDownOnce(0x02)) {
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

bool GeoSample::Render()
{
	g_pD3dContext->IASetInputLayout(m_pVertexLayout.Get());

	g_pD3dContext->VSSetShader(m_pVS.Get(), NULL, 0);
	g_pD3dContext->GSSetShader(m_pGS.Get(), NULL, 0);
	g_pD3dContext->PSSetShader(m_pPS.Get(), NULL, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_iPrimType);

	g_pD3dContext->RSSetState(m_pRSNoCull.Get());

	g_pD3dContext->DrawIndexed(6, 0, 0);

	return true;
}

bool GeoSample::Release()
{
	return true;
}



GeoSample::~GeoSample()
{

}