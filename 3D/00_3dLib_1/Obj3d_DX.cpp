#include "Obj3d_DX.h"

namespace D3D
{
	ID3D11Buffer* CreateVertexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data)
	{
		ID3D11Buffer* pBuffer = nullptr;
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = iNumVertex * iVertexSize;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = data;

		g_pD3dDevice->CreateBuffer(&bd, &sd, &pBuffer);

		return pBuffer;
	}

	ID3D11Buffer* CreateIndexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data)
	{
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = iNumVertex * iVertexSize;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = data;

		g_pD3dDevice->CreateBuffer(&bd, &sd, &pBuffer);

		return pBuffer;
	}

	ID3D11Buffer* CreateConstantBuffer(UINT iBufferSize, VOID* data, bool bDynamic)
	{
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		if (bDynamic) {
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else {
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iBufferSize;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = data;
		if (data != nullptr) { g_pD3dDevice->CreateBuffer(&bd, &sd, &pBuffer); }
		else { g_pD3dDevice->CreateBuffer(&bd, NULL, &pBuffer); }

		return pBuffer;
	}

	ID3D11ShaderResourceView* CreateSRV(const TCHAR* szFileName)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		
		D3DX11_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory(&loadinfo, sizeof(loadinfo));
		loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		loadinfo.Format = DXGI_FORMAT_FROM_FILE;
		
		HRESULT hr = S_OK;
		D3DX11CreateShaderResourceViewFromFile(g_pD3dDevice, szFileName, &loadinfo, NULL, &pSRV, &hr);
		
		if (FAILED(hr)) { return nullptr; }
		
		return pSRV;
	}

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG) 
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* pErrorBlob;

		hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
		if (FAILED(hr)) {
			if (pErrorBlob) {
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
				pErrorBlob->Release();
			}
			return hr;
		}

		if (pErrorBlob) { pErrorBlob->Release(); }

		return hr;
	}

	ID3D11VertexShader*  LoadVertexShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char*  pFuntionName)
	{
		ID3D11VertexShader* pVertexShader;
		ID3DBlob* pBlob;

		HRESULT hr;
		hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "vs_5_0", &pBlob);
		if (FAILED(hr)) { return nullptr; }

		hr = g_pD3dDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pVertexShader);
		if (FAILED(hr)) { 
			if (pBlob) { pBlob->Release(); }
			return nullptr; 
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pVertexShader;
	}

	ID3D11PixelShader*  LoadPixelShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char*  pFuntionName)
	{
		ID3D11PixelShader* pPixelShader;
		ID3DBlob* pBlob;

		HRESULT hr;
		hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "ps_5_0", &pBlob);
		if (FAILED(hr)) { return nullptr; }

		hr = g_pD3dDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pPixelShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pPixelShader;
	}

	ID3D11GeometryShader*  LoadGeoShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char*  pFuntionName)
	{
		ID3D11GeometryShader* pGeoShader;
		ID3DBlob* pBlob;

		HRESULT hr;
		hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "gs_5_0", &pBlob);
		if (FAILED(hr)) { return nullptr; }

		hr = g_pD3dDevice->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pGeoShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pGeoShader;
	}
}


Obj3d_DX::Obj3d_DX()
{

}

bool  Obj3d_DX::PreRender(UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;


	g_pD3dContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset); //정점 버퍼 세팅
	g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);            //인덱스 버퍼 세팅
	
	g_pD3dContext->IASetInputLayout(m_pInputLayout.Get()); //인풋 레이아웃 세팅
																							   
	g_pD3dContext->VSSetShader(m_pVertexShader.Get(), NULL, 0);                                // 정점 쉐이더 세팅
	g_pD3dContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());			   // 정점 쉐이더에 상수 버퍼 세팅
																							   
	g_pD3dContext->GSSetShader(m_pGeoShader.Get(), NULL, 0);								   // 기하 쉐이더 세팅
	g_pD3dContext->GSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());			   // 기하 쉐이더에 상수 버퍼 세팅
																							   
	g_pD3dContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);								   // 픽셀 쉐이더 세팅
	g_pD3dContext->PSSetShaderResources(0, 1, m_pTextureRV.GetAddressOf());					   // 픽셀 쉐이더에 텍스쳐 리소스 세팅

	return true;
}

bool  Obj3d_DX::Render(UINT iVertexSize, UINT iNumVertex, UINT iNumIndex)
{
	PreRender(iVertexSize);
	PostRender(iNumVertex, iNumIndex);
	return true;
}

bool  Obj3d_DX::PostRender(UINT iNumVertex, UINT iNumIndex)
{
	// 인덱스 버퍼를 이용해서 그리기
	if (m_pIndexBuffer != nullptr) { g_pD3dContext->DrawIndexed(iNumIndex, 0, 0); }
	// 정점 버퍼를 이용해서 직접 그리기
	else {	g_pD3dContext->Draw(iNumVertex, 0); }

	return true;
}

bool  Obj3d_DX::Release()
{
	return true;
}

Obj3d_DX::~Obj3d_DX()
{
	Release();
}