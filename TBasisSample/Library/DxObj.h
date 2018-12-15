#pragma once
#include "DxRTV.h"

namespace Lypi
{
	////////////////////////// �Ʒ��� ��� ���� ��� ����Ѵ�.
	// �̿� ���� ���� �̹� ���̴� ���������ο� ���ҽ� �� ���°����� �Ҵ�Ǿ� ��� ���� ��쿡 �߻��Ѵ�.
	//D3D11 WARNING : ID3D11DeviceContext::SOSetTargets : Resource being set to SO buffer slot 0 is still bound on input![STATE_SETTING WARNING #10: DEVICE_SOSETTARGETS_HAZARD]
	//D3D11 WARNING : ID3D11DeviceContext::SOSetTargets : Forcing Vertex Buffer slot 0 to NULL.[STATE_SETTING WARNING #1: DEVICE_IASETVERTEXBUFFERS_HAZARD]
	void		       ClearD3D11DeviceContext();

	ID3D11InputLayout* CreateInputlayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements, LPCVOID lpData, DWORD dwSize);

	ID3D11Buffer* CreateVertexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);                        // ���� ���� ���� (���� ����, ���� ũ��, ���� ���ҽ� ������)
	ID3D11Buffer* CreateIndexBuffer(UINT iNumVertex, UINT iVertexSize, VOID* data);						    // �ε��� ���� ���� (���� ����, ���� ũ��, ���� ���ҽ� ������)
	ID3D11Buffer* CreateConstantBuffer(UINT iBufferSize, VOID* data = nullptr, bool bDynamic = false);		// ��� ���� ���� (���� ũ��, ���� ���ҽ� ������, ���� ���ҽ� ����)

	ID3D11ShaderResourceView* CreateSRV(const TCHAR* szFileName);
	ID3D11DepthStencilView*   CreateDSV(DWORD dwWidth, DWORD dwHeight);
	
	//(���̴� �ڵ尡 ����ִ� ���� �̸�, ������ ���� �Լ� �̸�, ���̴� ��, ��ȯ����)
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// (���̴� ���� �̸�, ���� �Լ� �̸�, ��ȯ����)
	ID3D11VertexShader*    LoadVertexShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "VS", bool bBinary = false);
	ID3D11PixelShader*     LoadPixelShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "PS", bool bBinary = false);
	ID3D11GeometryShader*  LoadGeoShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char*  pFuntionName = "GS", bool bBinary = false);
	ID3D11HullShader*      LoadHullShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char *pFuntionName = "HS", bool bBinary = false);
	ID3D11DomainShader*    LoadDomainShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char *pFuntionName = "DS", bool bBinary = false);
	ID3D11ComputeShader*   LoadComputeShaderFile(const void* pShaderFile, ID3DBlob** ppBlobOut = nullptr, const char *pFuntionName = "CS", bool bBinary = false);

	class Obj3d_DX
	{
	public:
		ComPtr<ID3D11Buffer>                m_pVertexBuffer;
		ComPtr<ID3D11Buffer>                m_pIndexBuffer;
		ComPtr<ID3D11Buffer>                m_pConstantBuffer;

		ComPtr<ID3DBlob>				    m_pVSBlob;
		ComPtr<ID3DBlob>				    m_pGSBlob;
		ComPtr<ID3DBlob>				    m_pPSBlob;
		ComPtr<ID3DBlob>				    m_pHSBlob;
		ComPtr<ID3DBlob>				    m_pDSBlob;
		ComPtr<ID3DBlob>				    m_pCSBlob;

		ComPtr<ID3D11InputLayout>           m_pInputLayout;
		ComPtr<ID3D11ShaderResourceView>	m_pTextureSRV;

		ComPtr<ID3D11VertexShader>          m_pVertexShader;
		ComPtr<ID3D11PixelShader>           m_pPixelShader;
		ComPtr<ID3D11GeometryShader>        m_pGeoShader;
		ComPtr<ID3D11HullShader>		    m_pHullShader;
		ComPtr<ID3D11DomainShader>		    m_pDomainShader;
		ComPtr<ID3D11ComputeShader>		    m_pComputeShader;

		ComPtr<ID3D11ShaderResourceView>    m_pTextureRV;

		UINT				                m_iPrimitiveType;
		UINT				                m_iCullMode;
		UINT				                m_iSamplerMode;
		UINT				                m_iNumVertex;
		UINT				                m_iNumIndex;
		UINT				                m_iVertexSize;
		UINT				                m_iIndexSize;

		D3D11_BOX			                m_BoxVB;
		D3D11_BOX			                m_BoxIB;
		
		UINT				                m_iBeginVB;
		UINT				                m_iBeginIB;

	public:
		bool  PreRender(UINT iVertexSize);
		bool  Render(UINT iVertexSize, UINT iNumVertex, UINT iNumIndex);
		bool  PostRender(UINT iNumVertex, UINT iNumIndex);
		bool  Release();
	public:
		Obj3d_DX();
		virtual ~Obj3d_DX();
	};
}