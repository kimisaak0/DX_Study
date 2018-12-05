#pragma once
#include "header_DX.h"

namespace D3D
{
	ID3D11Buffer* CreateVertexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);                        // 정점 버퍼 생성 (정점 갯수, 정점 크기, 하위 리소스 데이터)
	ID3D11Buffer* CreateIndexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);						    // 인덱스 버퍼 생성 (정점 갯수, 정점 크기, 하위 리소스 데이터)
	ID3D11Buffer* CreateConstantBuffer(UINT iBufferSize, VOID* data = nullptr, bool bDynamic = false);		// 상수 버퍼 생성 (버퍼 크기, 하위 리소스 데이터, 동적 리소스 여부)

	//(쉐이더 코드가 들어있는 파일 이름, 컴파일 시작 함수 이름, 쉐이더 모델, 반환인자)
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	ID3D11ShaderResourceView* CreateSRV(const TCHAR* szFileName);
	
	// (쉐이더 파일 이름, 진입 함수 이름, 반환인자)
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