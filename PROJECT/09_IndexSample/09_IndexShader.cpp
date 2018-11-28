#include "09_IndexShader.h"

VertexSample::VertexSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pVertexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pVS           = nullptr;
	m_pPS           = nullptr;
	m_PrimType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


HRESULT VertexSample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	SimpleVertex vertices[] = {
		{    0.f,   0.f, 0.f },
		{    0.f,   1.f, 0.f },
	    {  0.95f, 0.31f, 0.f },
	    {  0.59f,-0.81f, 0.f },
	    { -0.59f,-0.81f, 0.f },
	    { -0.95f, 0.31f, 0.f },

	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * (sizeof(vertices) / sizeof(vertices[0]));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	CD3D11_BUFFER_DESC cbc(sizeof(SimpleVertex) * 4, D3D11_BIND_VERTEX_BUFFER);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	
	V_FRETURN(g_pD3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer));

	return hr;
}

HRESULT VertexSample::CreateIndexBuffer()
{
	HRESULT hr = S_OK;

	WORD indices[] = {
		0,1,2,
	    0,2,3,
		0,3,4,
		0,4,5,
		0,5,1,
	};

	UINT iNumIndex = sizeof(indices) / sizeof(indices[0]);

	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = iNumIndex * sizeof(WORD);
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA ibInitData;
	ZeroMemory(&ibInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibInitData.pSysMem = indices;
	
	V_FRETURN(g_pD3dDevice->CreateBuffer(&ibDesc, &ibInitData, &m_pIndexBuffer));

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

	ID3DBlob* pPSBuf2 = nullptr;
	V_FRETURN(D3DX11CompileFromFile(_T("Pixel.psh"), NULL, NULL, "PS2", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf2, NULL, NULL));
	V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf2->GetBufferPointer(), pPSBuf2->GetBufferSize(), NULL, &m_pPS2));

	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pVertexLayout));

	SAFE_RELEASE(pVSBuf);
	SAFE_RELEASE(pPSBuf);
	SAFE_RELEASE(pPSBuf2);

	return hr;
}

HRESULT VertexSample::CreateTriangle(D3D_PRIMITIVE_TOPOLOGY topology)
{
	HRESULT hr = S_OK;

	V_FRETURN(CreateVertexBuffer());
	V_FRETURN(CreateIndexBuffer());
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

bool VertexSample::Render()
{
	g_pD3dContext->IASetInputLayout(m_pVertexLayout);

	g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
	//m_pImmediateContext->HSSetShader(NULL, NULL, 0);
	//m_pImmediateContext->DSSetShader(NULL, NULL, 0);
	//m_pImmediateContext->GSSetShader(NULL, NULL, 0);
	g_pD3dContext->PSSetShader(m_pPS, NULL, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	g_pD3dContext->IASetPrimitiveTopology(m_PrimType);
	g_pD3dContext->DrawIndexed(9, 0, 0);

	g_pD3dContext->PSSetShader(m_pPS2, NULL, 0);
	g_pD3dContext->DrawIndexed(6, 10, 0);


	return true;
}

bool VertexSample::Release()
{
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
	return true;
}

VertexSample::~VertexSample()
{

}