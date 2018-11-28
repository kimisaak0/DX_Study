#include "13a_ObjectDX.h"

ObjectDX::ObjectDX()
{

}

HRESULT ObjectDX::CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList, int iNumCount)
{
	HRESULT hr;
	
	D3D11_BUFFER_DESC sDesc;
	ZeroMemory(&sDesc, sizeof(D3D11_BUFFER_DESC));
	sDesc.ByteWidth = sizeof(PCT_VERTEX) * iNumCount;
	sDesc.Usage = D3D11_USAGE_DEFAULT;
	sDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sInitData;
	ZeroMemory(&sInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	sInitData.pSysMem = pVertexList;

	if (FAILED(hr = pd3dDevice->CreateBuffer(&sDesc, &sInitData, &m_pVertexBuffer))) {
		return hr;
	}

	m_iNumVertex = iNumCount;

	return hr;
}

HRESULT ObjectDX::CreateVertexShader(ID3D11Device* pd3dDevice, const TCHAR* pName)
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(pName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &m_pVSBlop, &m_pErrorBlob, NULL);
	if (FAILED(hr)) {
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());
		return false;
	}

	if (FAILED(hr = pd3dDevice->CreateVertexShader(m_pVSBlop->GetBufferPointer(), m_pVSBlop->GetBufferSize(), NULL, &m_pVertexShader))) {
		return hr;
	}

	return hr;
}

HRESULT ObjectDX::CreatePixelShader(ID3D11Device* pd3dDevice, const TCHAR* pName)
{
	HRESULT hr; 
	hr = D3DX11CompileFromFile(pName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &m_pPSBlop, &m_pErrorBlob, NULL);
	if (FAILED(hr)) {
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());
		return false;
	}

	if (FAILED(hr = pd3dDevice->CreatePixelShader(m_pPSBlop->GetBufferPointer(), m_pPSBlop->GetBufferSize(), NULL, &m_pPixelShader))) {
		SAFE_RELEASE(m_pPSBlop);
		return NULL;
	}

	SAFE_RELEASE(m_pPSBlop);
	return hr;
}

HRESULT ObjectDX::CreateLayout(ID3D11Device* pd3dDevice, ID3DBlob* pVSBlop)
{
	HRESULT hr;
	if (pVSBlop == NULL) return E_FAIL;

	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	int iNumElement = sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	if (FAILED(hr = pd3dDevice->CreateInputLayout(ied, iNumElement, pVSBlop->GetBufferPointer(), pVSBlop->GetBufferSize(), &m_pInputLayout))) {
		return hr;
	}

	return hr;
}

HRESULT ObjectDX::LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile)
{
	HRESULT hr;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pLoadFile, NULL, NULL, &m_pTextureSRV, NULL))) {
		return hr;
	}

	return hr;
}

bool ObjectDX::PreRender(ID3D11DeviceContext* pContext)
{
	pContext->PSSetShader(m_pPixelShader, NULL, NULL);
	pContext->VSSetShader(m_pVertexShader, NULL, NULL);
	
	UINT pStrides = sizeof(PCT_VERTEX);
	UINT pOffsets = 0;

	pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &pStrides, &pOffsets);
	pContext->IASetInputLayout(m_pInputLayout);
	pContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
	
	return true;
}

bool ObjectDX::Render(ID3D11DeviceContext* pContext)
{
	PreRender(pContext);
	PostRender(pContext);
	return true;
}

bool ObjectDX::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->Draw(m_iNumVertex, 0);
	return true;
}

bool ObjectDX::Release()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVSBlop);
	SAFE_RELEASE(m_pPSBlop);
	SAFE_RELEASE(m_pErrorBlob);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pTextureSRV);
	
	return true;
}


ObjectDX::~ObjectDX()
{

}