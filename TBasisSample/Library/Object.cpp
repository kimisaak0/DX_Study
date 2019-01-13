#include "Object.h"

namespace Lypi
{

	HRESULT                 CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlopOut)
	{
		HRESULT hr = S_OK; 

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS; //쉐이더 컴파일시 문법 검사를 엄격히 하게한다. 
#if defined( DEBUG ) || defined( _DEBUG )	
		dwShaderFlags |= D3DCOMPILE_DEBUG;                  //디버그 모드로 실행시 쉐이더의 디버그 정보를 포함한다.
#endif

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, nullptr, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, nullptr, ppBlopOut, &pErrorBlob, nullptr);
		//쉐이더 파일을 컴파일한다.

		if (FAILED(hr)) { //쉐이더 컴파일에 실패했을 경우
			if (pErrorBlob != nullptr) { //디버그 정보가 있으면 
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer()); //표시하고,
				pErrorBlob->Release(); // ErrorBlob을 릴리즈하고,
			}
			return hr; // 함수를 종료한다.
		}

		if (pErrorBlob != nullptr) { //실패하지 않았는데 디버그 정보가 있으면
			pErrorBlob->Release();  //ErrorBlob을 릴리즈한다.
		}

		return S_OK;
	}

	ID3D11VertexShader*     LoadVertexShaderFile(ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut, char *pFunctionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3DBlob* pBlob = nullptr;
		if (bBinary == false) { // 이미 컴파일된 정보가 없으면 
			if (pFunctionName == 0) { // 쉐이더 파일내의 함수명을 지정하지 않았으면
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, "VS", "vs_5_0", &pBlob); //기본 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
			else {
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, pFunctionName, "vs_5_0", &pBlob); //지정된 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
		}
		else { // 이미 컴파일된 정보가 있으면
			pBlob = *ppBlobOut; // 받은 정보를 pBlob에 저장한다.
			if (pBlob == nullptr) {
				return nullptr;
			}
		}
		
		ID3D11VertexShader* pVertexShader;
		//  CreateVertexShader  (*pShaderBytecode, BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
		hr = g_pD3dDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
		if (FAILED(hr)) {
			pBlob->Release();
			return nullptr;
		}

		if (ppBlobOut == nullptr) {
			pBlob->Release();
		}
		else {
			*ppBlobOut = pBlob;
		}

		return pVertexShader;
	}

	ID3D11PixelShader*      LoadPixelShaderFile(ID3D11Device* pd3dDevice, const void* pLoadShaderFile, char *pFunctionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3DBlob* pBlob = nullptr;
		if (bBinary == false) { // 이미 컴파일된 정보가 없으면 
			if (pFunctionName == 0) { // 쉐이더 파일내의 함수명을 지정하지 않았으면
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, "PS", "ps_5_0", &pBlob); //기본 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
			else {
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, pFunctionName, "ps_5_0", &pBlob); //지정된 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
		}

		ID3D11PixelShader* pPixelShader;
		//  CreatePixelShader  (*pShaderBytecode, BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
		hr = g_pD3dDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
		if (FAILED(hr)) {
			pBlob->Release();
			return nullptr;
		}

		return pPixelShader;
	}

	ID3D11GeometryShader*   LoadGeometryShaderFile(ID3D11Device*  pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut, char *pFunctionName, bool bBinary)
	{
		HRESULT hr = S_OK;

		ID3DBlob* pBlob = nullptr;
		if (bBinary == false) { // 이미 컴파일된 정보가 없으면 
			if (pFunctionName == 0) { // 쉐이더 파일내의 함수명을 지정하지 않았으면
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, "GS", "gs_5_0", &pBlob); //기본 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
			else {
				hr = CompileShaderFromFile((TCHAR*)pLoadShaderFile, pFunctionName, "gs_5_0", &pBlob); //지정된 함수명으로 컴파일해서 pBlob에 저장한다.
				if (FAILED(hr)) {
					return nullptr;
				}
			}
		}
		else { // 이미 컴파일된 정보가 있으면
			pBlob = *ppBlobOut; // 받은 정보를 pBlob에 저장한다.
			if (pBlob == nullptr) {
				return nullptr;
			}
		}

		ID3D11GeometryShader* pGeometryShader;
		//  CreateVertexShader  (*pShaderBytecode, BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
		hr = g_pD3dDevice->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pGeometryShader);
		if (FAILED(hr)) {
			pBlob->Release();
			return nullptr;
		}

		if (ppBlobOut == nullptr) {
			pBlob->Release();
		}
		else {
			*ppBlobOut = pBlob;
		}

		return pGeometryShader;
	}

	ID3D11InputLayout*      CreateInputlayout(ID3D11Device*  pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements)
	{
		HRESULT hr = S_OK;
		ID3D11InputLayout* pInputLayout = nullptr;

		hr = pd3dDevice->CreateInputLayout(layout, numElements, lpData, dwSize, &pInputLayout);

		if (FAILED(hr)) {
			H(hr);
			return nullptr;
		}

		return pInputLayout;
	}

	ID3D11Buffer*           CreateVertexBuffer(ID3D11Device*  pd3dDevice, void* vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;

		if (bDynamic) {
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else {
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iVertexSize * iNumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;

		if (vertices != nullptr) {
			hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		else {
			hr = pd3dDevice->CreateBuffer(&bd, nullptr, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		return pBuffer;
	}

	ID3D11Buffer*           CreateIndexBuffer(ID3D11Device*  pd3dDevice, void *indices, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		HRESULT hr = S_OK;
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
		bd.ByteWidth = iSize * iNumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices;

		if (indices != nullptr) {
			hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		else {
			hr = pd3dDevice->CreateBuffer(&bd, nullptr, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		return pBuffer;

	}

	ID3D11Buffer*           CreateConstantBuffer(ID3D11Device*  pd3dDevice, void *data, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		HRESULT hr = S_OK;
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
		bd.ByteWidth = iSize * iNumIndex;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = data;

		if (data != nullptr) {
			hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		else {
			hr = pd3dDevice->CreateBuffer(&bd, nullptr, &pBuffer);
			if (FAILED(hr)) {
				H(hr);
				return nullptr;
			}
		}
		return pBuffer;
	}

	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath)
	{
		HRESULT hr = S_OK;
		if (strFilePath == nullptr) {
			return nullptr;
		}

		ID3D11ShaderResourceView* pSRV = nullptr;
		D3DX11CreateShaderResourceViewFromFile(pDevice, strFilePath, nullptr, nullptr, &pSRV, nullptr);
		if (FAILED(hr)) {
			H(hr);
			return nullptr;
		}
		return pSRV;
	}

	ID3D11DepthStencilView*     CreateDepthStencilView(ID3D11Device* pDevice, DWORD dwWidth, DWORD dwHeight)
	{
		HRESULT hr;
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


		hr = pDevice->CreateTexture2D(&DescDepth, nullptr, &pDSTexture);
		if (FAILED(hr)) {
			return nullptr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DescDepth.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;

		hr = pDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvd, &pDSV);
		if (FAILED(hr)) {
			return nullptr;
		}
		return pDSV;
	}


	Object::Object()
	{

	}

	




	Object::~Object()
	{

	}
}