#include "09_IndexShader.h"

VertexSample::VertexSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pVertexLayout   = nullptr;
	m_pVertexBuffer   = nullptr;
	m_pIndexBuffer    = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVS             = nullptr;
	m_pPS             = nullptr;
	m_pPS2            = nullptr;
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

		//-0.5f, 0.5f, 0.5f,
		//0.5f, 0.5f, 0.5f,
		//0.5f, -0.5f, 0.5f,
		//-0.5f, -0.5f, 0.5f,

	};

	//D3D11_BUFFER_DESC bd;
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(SimpleVertex) * (sizeof(vertices) / sizeof(vertices[0]));
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;

	CD3D11_BUFFER_DESC cbc(sizeof(SimpleVertex) * (sizeof(vertices) / sizeof(vertices[0])), D3D11_BIND_VERTEX_BUFFER);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	
	V_FRETURN(g_pD3dDevice->CreateBuffer(&cbc, &InitData, &m_pVertexBuffer));

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
	ibDesc.ByteWidth = (iNumIndex + 1) * sizeof(WORD);
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

HRESULT VertexSample::CreateContantBuffer()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(VSCB);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	
	V_FRETURN(g_pD3dDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer));

	return hr;
	
}

HRESULT VertexSample::LoadShaderAndInputLayout()
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	ID3DBlob* pBufErr = nullptr;

	ID3DBlob* pVSBuf = nullptr;
	hr = D3DX11CompileFromFile(_T("Vertex.vsh"), NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, &pBufErr, NULL);
	if (FAILED(hr)) {
		TCHAR pErrMsg[500];
		size_t st;
		mbstowcs_s(&st, pErrMsg, (CHAR*)pBufErr->GetBufferPointer(), 500);
		MessageBox(NULL, pErrMsg, _T("ERROR"), MB_OK);
		return hr;
	}
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

	g_pD3dContext->IASetPrimitiveTopology(topology);

	return hr;
}

bool VertexSample::Init()
{
	if (FAILED(CreateTriangle())) {
		MessageBox(0, _T("CreateTrangle 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (FAILED(CreateContantBuffer())) {
		MessageBox(0, _T("CreateContantBuffer 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	return true;
}

bool VertexSample::Frame()
{
	float fTime = m_GameTimer.getGameTime();
	float fBoundedTime = cosf(fTime)*0.5 + 0.5f;

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	g_pD3dContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);

	VSCB* pConstData = (VSCB*)MappedResource.pData;
	pConstData->vColor = D3DXVECTOR4(sinf(3*fTime), cosf(3 * fTime), 1-sinf(3 * fTime), 1.0f);
	pConstData->fTime = fBoundedTime;
	
	g_pD3dContext->Unmap(m_pConstantBuffer, 0);

	return true;
}

bool VertexSample::Render()
{
	g_pD3dContext->IASetInputLayout(m_pVertexLayout);

	g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
	g_pD3dContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//m_pImmediateContext->HSSetShader(NULL, NULL, 0);
	//m_pImmediateContext->DSSetShader(NULL, NULL, 0);
	g_pD3dContext->GSSetShader(NULL, NULL, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//m_pImmediateContext->IASetPrimitiveTopology(m_PrimType);
	
	

	g_pD3dContext->PSSetShader(m_pPS, NULL, 0);
	g_pD3dContext->DrawIndexed(9, 0, 0);

	g_pD3dContext->PSSetShader(m_pPS2, NULL, 0);
	g_pD3dContext->DrawIndexed(6, 10, 0);


	return true;
}

bool VertexSample::Release()
{
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pPS2);

	return true;
}


VertexSample::~VertexSample()
{

}