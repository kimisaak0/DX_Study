#include "SkyBox.h"

#define textureNum 6

SkyBox::SkyBox(){ }

HRESULT SkyBox::LoadTexture(T_STR szName)
{
	const TCHAR* g_szSkyTextures[] = {
		L"../../INPUT/DATA/image/st00_cm_front.bmp",
		L"../../INPUT/DATA/image/st00_cm_back.bmp",
		L"../../INPUT/DATA/image/st00_cm_right.bmp",
		L"../../INPUT/DATA/image/st00_cm_left.bmp",
		L"../../INPUT/DATA/image/st00_cm_up.bmp",
		L"../../INPUT/DATA/image/st00_cm_down.bmp"
	};

	int iNumTexture = sizeof(g_szSkyTextures) / sizeof(g_szSkyTextures[0]);

	for (int iTex = 0; iTex < iNumTexture; iTex++) {
		m_pTexSRV[iTex].Attach(D3D::CreateSRV(g_szSkyTextures[iTex]));
	}

	return S_OK;
}

HRESULT SkyBox::LoadVertexShader(T_STR szName)
{
	m_dxObj.m_pVertexShader.Attach(D3D::LoadVertexShaderFile(szName.c_str(), m_dxObj.m_pVSBlob.GetAddressOf(), "vssky"));

	return S_OK;
}

HRESULT SkyBox::LoadPixelShader(T_STR szName)
{
	if (szName != L"NULL") {
		HRESULT hr = S_OK;
		m_dxObj.m_pPixelShader.Attach(D3D::LoadPixelShaderFile(szName.c_str(), nullptr, "pssky"));
		return hr;
	}
	return S_OK;
}

bool  SkyBox::Create(T_STR szVSName, T_STR szPSName, T_STR szGSName, T_STR szTextureName, float scale)
{
	D3DXMatrixScaling(&m_matWorld, scale, scale, scale);
	
	Shape_DX::Create(szVSName, szPSName, szGSName, szTextureName);

	//LoadVertexShader(szVSName);
	//LoadPixelShader(szPSName);

	return true;
}
bool  SkyBox::Render()
{
	D3D::ApplySS(xDxState::g_pSSWrapPoint);

	D3DXMATRIX matView = m_matView;
	matView._41 = matView._42 = matView._43 = 0;
	SetMatrix(&m_matWorld, &matView, &m_matProj);

	g_pD3dContext->UpdateSubresource(m_dxObj.m_pConstantBuffer.Get(), 0, nullptr, &m_cbData, 0, 0);
	g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	PreRender();

	//한장씩 렌더링하기
	for (int iTex = 0; iTex < textureNum; iTex++) {
		if (m_pTexSRV[iTex] == nullptr) { break; }
		g_pD3dContext->PSSetShaderResources(0, 1, m_pTexSRV[iTex].GetAddressOf());

		g_pD3dContext->DrawIndexed(6, 6 * iTex, 0); //인덱스 버퍼 갯수, 인덱스 버퍼 시작, 버텍스 버퍼 시작.
	}

	D3D::ApplySS(xDxState::g_pSSWrapLinear);

	return true;
}

bool  SkyBox::Release()
{
	Shape_DX::Release();
	return true;
}



SkyBox::~SkyBox(){ }
