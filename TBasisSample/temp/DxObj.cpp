#include "DxObj.h"

namespace Lypi
{
	void ClearD3D11DeviceContext()
	{
		//unbind all objects from the immediate context
		if (g_pD3dContext == nullptr) {
			return;
		}

		ID3D11ShaderResourceView* pSRVs[16] = { 0, };
		ID3D11RenderTargetView* pRTVs[16] = { 0, };
		ID3D11DepthStencilView* pDSV = nullptr;
		ID3D11Buffer* pBuffers[16] = { 0, };
		ID3D11SamplerState* pSamplers[16] = { 0, };
		UINT StrideOffset[16] = { 0, };

		// Shaders
		g_pD3dContext->VSSetShader(nullptr, nullptr, 0);
		g_pD3dContext->HSSetShader(nullptr, nullptr, 0);
		g_pD3dContext->DSSetShader(nullptr, nullptr, 0);
		g_pD3dContext->GSSetShader(nullptr, nullptr, 0);
		g_pD3dContext->PSSetShader(nullptr, nullptr, 0);

		// IA clear
		g_pD3dContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
		g_pD3dContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
		g_pD3dContext->IASetInputLayout(NULL);

		// Constant buffers
		g_pD3dContext->VSSetConstantBuffers(0, 14, pBuffers);
		g_pD3dContext->HSSetConstantBuffers(0, 14, pBuffers);
		g_pD3dContext->DSSetConstantBuffers(0, 14, pBuffers);
		g_pD3dContext->GSSetConstantBuffers(0, 14, pBuffers);
		g_pD3dContext->PSSetConstantBuffers(0, 14, pBuffers);

		// Resources
		g_pD3dContext->VSSetShaderResources(0, 16, pSRVs);
		g_pD3dContext->HSSetShaderResources(0, 16, pSRVs);
		g_pD3dContext->DSSetShaderResources(0, 16, pSRVs);
		g_pD3dContext->GSSetShaderResources(0, 16, pSRVs);
		g_pD3dContext->PSSetShaderResources(0, 16, pSRVs);

		// Samplers
		g_pD3dContext->VSSetSamplers(0, 16, pSamplers);
		g_pD3dContext->HSSetSamplers(0, 16, pSamplers);
		g_pD3dContext->DSSetSamplers(0, 16, pSamplers);
		g_pD3dContext->GSSetSamplers(0, 16, pSamplers);
		g_pD3dContext->PSSetSamplers(0, 16, pSamplers);

		// Render targets
		g_pD3dContext->OMSetRenderTargets(8, pRTVs, pDSV);

		// States
		FLOAT blendFactor[4] = { 0,0,0,0 };
		g_pD3dContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
		g_pD3dContext->OMSetDepthStencilState(NULL, 0);
		g_pD3dContext->RSSetState(NULL);

	}

	ID3D11InputLayout* CreateInputlayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements, LPCVOID lpData, DWORD dwSize)
	{
		HRESULT hr = S_OK;
		ID3D11InputLayout* pInputLayout = nullptr;

		hr = g_pD3dDevice->CreateInputLayout(layout, numElements, lpData, dwSize, &pInputLayout);

		if (FAILED(hr)) {
			H(hr);
			return nullptr;
		}

		return pInputLayout;
	}

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
		HRESULT hr = S_OK;
		if (szFileName == nullptr) {
			return nullptr;
		}
		
		//왜 넣었는지 기억이 안 남...
		D3DX11_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory(&loadinfo, sizeof(loadinfo));
		loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		loadinfo.Format = DXGI_FORMAT_FROM_FILE;

		ID3D11ShaderResourceView* pSRV = nullptr;
		hr = D3DX11CreateShaderResourceViewFromFile(g_pD3dDevice, szFileName, &loadinfo, nullptr, &pSRV, nullptr);
		if (FAILED(hr)) { 
			H(hr);
			return nullptr; 
		}

		return pSRV;
	}

	ID3D11DepthStencilView*   CreateDSV(DWORD dwWidth, DWORD dwHeight)
	{
		HRESULT hr = S_OK;

		ID3D11DepthStencilView* pDSV = nullptr;
		ComPtr<ID3D11Texture2D> pDSTexture = nullptr;

		D3D11_TEXTURE2D_DESC DescDepth;
		DescDepth.Width = dwWidth;
		DescDepth.Height = dwHeight;
		DescDepth.MipLevels = 1;
		DescDepth.ArraySize = 1;
		DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DescDepth.SampleDesc.Count = 1;
		DescDepth.SampleDesc.Quality = 0;
		DescDepth.Usage = D3D11_USAGE_DEFAULT;
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DescDepth.CPUAccessFlags = 0;
		DescDepth.MiscFlags = 0;

		hr = g_pD3dDevice->CreateTexture2D(&DescDepth, nullptr, &pDSTexture);
		if (FAILED(hr)) {
			return nullptr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DescDepth.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;

		hr = g_pD3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvd, &pDSV);
		if (FAILED(hr)) {
			return nullptr;
		}

		return pDSV;
	}

	//(쉐이더 코드가 들어있는 파일 이름, 컴파일 시작 함수 이름, 쉐이더 모델, 반환인자)
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

		if (pErrorBlob) {
			pErrorBlob->Release();
		}

		return S_OK;
	}

	// (쉐이더 파일 이름, 진입 함수 이름, 반환인자)
	ID3D11VertexShader*    LoadVertexShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char*  pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;
		
		ID3D11VertexShader* pVertexShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		LPCVOID lpData = nullptr;
		DWORD dwSize = NULL;

		if (bBinary) {
			pBlob = *ppBlobOut;
			if (pBlob == nullptr) { return nullptr; }
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "vs_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
		}

		dwSize = (DWORD)pBlob->GetBufferSize();
		lpData = pBlob->GetBufferPointer();

		hr = g_pD3dDevice->CreateVertexShader(lpData, dwSize, NULL, &pVertexShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pVertexShader;
	}

	ID3D11PixelShader*     LoadPixelShaderFile(const void* pShaderFile, const char*  pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;
	
		ID3D11PixelShader* pPixelShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		DWORD dwSize = NULL;
		LPCVOID lpData = nullptr;

		if (bBinary) {
			dwSize = sizeof(pShaderFile);
			lpData = pShaderFile;
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "ps_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
			dwSize = (DWORD)pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}

		hr = g_pD3dDevice->CreatePixelShader(lpData, dwSize, NULL, &pPixelShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		return pPixelShader;
	}

	ID3D11GeometryShader*  LoadGeoShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char*  pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3D11GeometryShader* pGeoShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		LPCVOID lpData = nullptr;
		DWORD dwSize = NULL;

		if (bBinary) {
			pBlob = *ppBlobOut;
			if (pBlob == nullptr) { return nullptr; }
			dwSize = sizeof(pShaderFile);
			lpData = pShaderFile;
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "gs_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
			dwSize = (DWORD)pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}

		hr = g_pD3dDevice->CreateGeometryShader(lpData, dwSize, NULL, &pGeoShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pGeoShader;
	}

	ID3D11HullShader*      LoadHullShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char *pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3D11HullShader* pHullShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		LPCVOID lpData = nullptr;
		DWORD dwSize = NULL;

		if (bBinary) {
			pBlob = *ppBlobOut;
			if (pBlob == nullptr) { return nullptr; }
			dwSize = sizeof(pShaderFile);
			lpData = pShaderFile;
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "hs_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
			dwSize = (DWORD)pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}	

		hr = g_pD3dDevice->CreateHullShader(lpData, dwSize, NULL, &pHullShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pHullShader;
	}

	ID3D11DomainShader*    LoadDomainShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char *pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3D11DomainShader* pDomainShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		LPCVOID lpData = nullptr;
		DWORD dwSize = NULL;
		
		if(bBinary){
			pBlob = *ppBlobOut;
			if (pBlob == nullptr) { return nullptr; }
			dwSize = sizeof(pShaderFile);
			lpData = pShaderFile;
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "ds_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
			dwSize = (DWORD)pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}

		hr = g_pD3dDevice->CreateDomainShader(lpData, dwSize, NULL, &pDomainShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pDomainShader;
	}

	ID3D11ComputeShader*   LoadComputeShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut, const char *pFuntionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3D11ComputeShader* pCompShader = nullptr;
		ID3DBlob* pBlob = nullptr;
		LPCVOID lpData = nullptr;
		DWORD dwSize = NULL;

		if (bBinary) {
			pBlob = *ppBlobOut;
			if (pBlob == nullptr) { return nullptr; }
			dwSize = sizeof(pShaderFile);
			lpData = pShaderFile;
		}
		else {
			hr = CompileShaderFromFile((TCHAR*)pShaderFile, pFuntionName, "cs_5_0", &pBlob);
			if (FAILED(hr)) { return nullptr; }
			dwSize = (DWORD)pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}

		hr = g_pD3dDevice->CreateComputeShader(lpData, dwSize, NULL, &pCompShader);
		if (FAILED(hr)) {
			if (pBlob) { pBlob->Release(); }
			return nullptr;
		}

		if (ppBlobOut == nullptr) { if (pBlob) { pBlob->Release(); } }
		else { *ppBlobOut = pBlob; }

		return pCompShader;
	}

	DxObj3d::DxObj3d()
	{
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
		m_pConstantBuffer = nullptr;

		m_pVSBlob = nullptr;
		m_pGSBlob = nullptr;
		m_pPSBlob = nullptr;
		m_pHSBlob = nullptr;
		m_pDSBlob = nullptr;
		m_pCSBlob = nullptr;

		m_pInputLayout = nullptr;
		m_pTextureSRV = nullptr;

		m_pVertexShader = nullptr;
		m_pPixelShader = nullptr;
		m_pGeoShader = nullptr;
		m_pHullShader = nullptr;
		m_pDomainShader = nullptr;
		m_pComputeShader = nullptr;

		m_pTextureRV = nullptr;

		m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		m_iCullMode = 1;
		m_iSamplerMode = 0;
		m_iNumVertex = 0;
		m_iNumIndex = 0;
		m_iVertexSize = 0;
		m_iIndexSize = sizeof(DWORD);

		m_iBeginVB = 0;
		m_iBeginIB = 0;
	}

	bool  DxObj3d::PreRender(UINT iVertexSize)
	{
		g_pD3dContext->IASetInputLayout(m_pInputLayout.Get());                           //인풋 레이아웃 세팅

		UINT stride = iVertexSize;
		UINT offset = 0;
		if (iVertexSize == 0) {
			stride = m_iVertexSize;
		}

		g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);      //정점 버퍼 세팅
		g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);   //인덱스 버퍼 세팅
		
		g_pD3dContext->VSSetShader(m_pVertexShader.Get(), NULL, 0);                       // 정점 쉐이더 세팅
		g_pD3dContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);			          // 정점 쉐이더에 상수 버퍼 세팅
		
		g_pD3dContext->GSSetShader(m_pGeoShader.Get(), NULL, 0);						  // 기하 쉐이더 세팅
		g_pD3dContext->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);			          // 기하 쉐이더에 상수 버퍼 세팅

		g_pD3dContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);						  // 픽셀 쉐이더 세팅
		g_pD3dContext->PSSetShaderResources(0, 1, &m_pTextureRV);					      // 픽셀 쉐이더에 텍스쳐 리소스 세팅

		g_pD3dContext->HSSetShader(m_pHullShader.Get(), NULL, 0);                         // 헐 쉐이더 세팅 
		g_pD3dContext->DSSetShader(m_pDomainShader.Get(), NULL, 0);                       // 도메인 쉐이더 세팅

		return true;
	}

	bool  DxObj3d::Render(UINT iVertexSize, UINT iNumVertex, UINT iNumIndex)
	{
		PreRender(iVertexSize);
		PostRender(iNumVertex, iNumIndex);
		return true;
	}

	bool  DxObj3d::PostRender(UINT iNumVertex, UINT iNumIndex)
	{
		// 인덱스 버퍼를 이용해서 그리기
		if (m_pIndexBuffer != nullptr) { 
			g_pD3dContext->DrawIndexed(iNumIndex, 0, 0); 
		}
		// 정점 버퍼를 이용해서 직접 그리기
		else { 
			g_pD3dContext->Draw(iNumVertex, 0); 
		}

		return true;
	}

	DxObj3d::~DxObj3d()
	{
	}
}