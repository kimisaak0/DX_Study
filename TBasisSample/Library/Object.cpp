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

	ID3D11InputLayout*      CreateInputlayout(ID3D11Device*  pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);

	ID3D11Buffer*           CreateVertexBuffer(ID3D11Device*  pd3dDevice, void *vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic = false);
	ID3D11Buffer*           CreateIndexBuffer(ID3D11Device*  pd3dDevice, void *indices, UINT iNumIndex, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*           CreateConstantBuffer(ID3D11Device*  pd3dDevice, void *data, UINT iNumIndex, UINT iSize, bool bDynamic = false);

	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath);
	ID3D11DepthStencilView*     CreateDepthStencilView(ID3D11Device* pDevice, DWORD dwWidth, DWORD dwHeight);


	Object::Object()
	{

	}

	




	Object::~Object()
	{

	}
}