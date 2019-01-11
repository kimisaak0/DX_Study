#include "Object.h"

namespace Lypi
{

	HRESULT                 CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlopOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )	
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, nullptr, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, nullptr, ppBlopOut, &pErrorBlob, nullptr);

	}

	ID3D11VertexShader*     LoadVertexShaderFile(ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);
	ID3D11PixelShader*      LoadPixelShaderFile(ID3D11Device* pd3dDevice, const void* pLoadShaderFile, char *pFuntionName = 0, bool bBinary = false, ID3DBlob** pRetBlob = nullptr);
	ID3D11GeometryShader*   LoadGeometryShaderFile(ID3D11Device*  pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);

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