#pragma once
#include "ShapeHeader.h"
#include "RenderTarget.h"


namespace Lypi
{
	HRESULT                 CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlopOut);
	
	ID3D11VertexShader*     LoadVertexShaderFile( ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFunctionName = 0, bool bBinary = false);
	ID3D11PixelShader*      LoadPixelShaderFile(  ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFunctionName = 0, bool bBinary = false);
	ID3D11GeometryShader*   LoadGeometryShaderFile(ID3D11Device*  pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);

	ID3D11InputLayout*      CreateInputlayout(ID3D11Device*  pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);
	
	ID3D11Buffer*           CreateVertexBuffer(ID3D11Device*  pd3dDevice, void *vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic = false);
	ID3D11Buffer*           CreateIndexBuffer(ID3D11Device*  pd3dDevice, void *indices, UINT iNumIndex, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*           CreateConstantBuffer(ID3D11Device*  pd3dDevice, void *data, UINT iNumIndex, UINT iSize, bool bDynamic = false);

	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath);
	ID3D11DepthStencilView*     CreateDepthStencilView(ID3D11Device* pDevice, DWORD dwWidth, DWORD dwHeight);

	class Object
	{
	public:
		ComPtr<ID3D11Buffer>			g_pVertexBuffer;
		ComPtr<ID3D11Buffer>			g_pIndexBuffer;
		ComPtr<ID3D11Buffer>			g_pConstantBuffer;

		ComPtr<ID3D11VertexShader>		g_pVertexShader;
		ComPtr<ID3D11PixelShader>		g_pPixelShader;
		ComPtr<ID3D11GeometryShader>	g_pGeometryShader;

		ComPtr<ID3DBlob>				g_pVSBlob;
		ComPtr<ID3DBlob>				g_pGSBlob;
		ComPtr<ID3DBlob>				g_pPSBlob;

		ComPtr<ID3D11InputLayout>			g_pInputlayout;
		ComPtr<ID3D11ShaderResourceView>	g_pTextureSRV;

		UINT					m_iPrimitiveType;
		UINT					m_iCullMode;
		UINT					m_iSamplerMode;
		UINT					m_iNumVertex;
		UINT					m_iNumIndex;
		UINT					m_iVertexSize;
		UINT					m_iIndexSize;

		UINT					m_iBeginVB;
		UINT					m_iBeginIB;

	public:
		void PreRender(UINT iVertexSize = 0);
		void PostRender(UINT iCount = 0);
		bool Render(UINT iVertexSize = 0, UINT iCount = 0);

	public:
		Object();
		virtual ~Object();

	};
}