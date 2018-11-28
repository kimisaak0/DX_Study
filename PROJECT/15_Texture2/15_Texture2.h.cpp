#include "15_Texture2.h"

Texture2::Texture2()
{
	m_pTextureSRV = nullptr;
}

HRESULT Texture2::Load(ID3D11Device* pDevice, TCHAR* strFilePath)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pDevice, strFilePath, NULL, NULL, &m_pTextureSRV, NULL);

	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

bool Texture2::Apply(ID3D11DeviceContext* pImmediateContext)
{
	assert(pImmediateContext);

	if (m_pTextureSRV == nullptr) {
		return false;
	}

	pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
	return true;
}

Texture2::~Texture2()
{
	SAFE_RELEASE(m_pTextureSRV);
}