#pragma once
#include "header_DX.h"

namespace D3D
{
	ID3D11Buffer* CreateVertexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);                        // ���� ���� ���� (���� ����, ���� ũ��, ���� ���ҽ� ������)
	ID3D11Buffer* CreateIndexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);						    // �ε��� ���� ���� (���� ����, ���� ũ��, ���� ���ҽ� ������)
	ID3D11Buffer* CreateConstantBuffer(UINT iBufferSize, VOID* data = nullptr, bool bDynamic = false);		// ��� ���� ���� (���� ũ��, ���� ���ҽ� ������, ���� ���ҽ� ����)

	//(���̴� �ڵ尡 ����ִ� ���� �̸�, ������ ���� �Լ� �̸�, ���̴� ��, ��ȯ����)
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	ID3D11ShaderResourceView* CreateSRV(const TCHAR* szFileName);
	
	// (���̴� ���� �̸�, ���� �Լ� �̸�, ��ȯ����)
	ID3D11VertexShader*    LoadVertexShaderFile (const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "VS");
	ID3D11PixelShader*     LoadPixelShaderFile  (const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "PS");
	ID3D11GeometryShader*  LoadGeoShaderFile    (const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "GS");
}

class Obj3d_DX
{
public:
	ComPtr<ID3D11Buffer>                m_pVertexBuffer;
	ComPtr<ID3D11Buffer>                m_pIndexBuffer;
	ComPtr<ID3D11Buffer>                m_pConstantBuffer;
								        
	ComPtr<ID3DBlob>                    m_pVSBlob;

	ComPtr<ID3D11InputLayout>           m_pInputLayout;
								        
	ComPtr<ID3D11VertexShader>          m_pVertexShader;
	ComPtr<ID3D11PixelShader>           m_pPixelShader;
	ComPtr<ID3D11GeometryShader>        m_pGeoShader;
									    
	ComPtr<ID3D11ShaderResourceView>    m_pTextureRV;

public:
	bool  PreRender(UINT iVertexSize);
	bool  Render(UINT iVertexSize, UINT iNumVertex, UINT iNumIndex);
	bool  PostRender(UINT iNumVertex, UINT iNumIndex);
	bool  Release();
public:
	Obj3d_DX();
	virtual ~Obj3d_DX();
};