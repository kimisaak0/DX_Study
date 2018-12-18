#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{
	struct V3
	{
		float x, y, z;
	};

	class Sample : public zCore
	{
		// ���ؽ� ���� �� ���̾ƿ�
		ID3D11Buffer*         m_pVertexBuffer;    //���� ���� �������̽�
		ID3D11Buffer*         m_pIndexBuffer;     //�ε��� ���� �������̽�
		ID3D11InputLayout*	  m_pVertexLayout;    //���� ���̾ƿ� �������̽�

		// ���ؽ� �� �ȼ� ���̴�
		ID3D11VertexShader*     m_pVS;   //���� ���̴� �������̽�
		ID3D11PixelShader*      m_pPS;	 //�ȼ� ���̴� �������̽�
		ID3D11GeometryShader*   m_pGS;   //���� ���̴� �������̽�
	
		// �̹��� ����׿�
		UINT    m_uPrimType;    //�������� Ÿ��
		UINT    m_uCullMode;    //�ø����
		UINT    m_uFillMode;    //���̾� �����Ӹ� ������

		ID3D11RasterizerState*      m_pRS;   //�����Ͷ����� ����

	public:
		HRESULT		CreateVertexBuffer();        // ���� ���� ����
		HRESULT     CreateIndexBuffer();         // �ε��� ���� ����
		HRESULT		LoadShaderAndInputLayout();  // ���� �� �Ƚ� ���̴� �ε� �� ����
		HRESULT		RSChange();                  // �����Ͷ����� ���� ����

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Sample(LPCTSTR LWndName);
		virtual ~Sample();
	};

}

//namespace Lypi
//{
//
//
//	class Sample :public zCore
//	{
//	public:
//		//--------------------------------------------------------------------------------------
//		// ���ؽ� ���� �� ���̾ƿ�
//		//--------------------------------------------------------------------------------------
//		ID3D11InputLayout*		m_pVertexLayout;
//		ID3D11Buffer*           m_pVertexBuffer;
//		ID3D11Buffer*			m_pIndexBuffer;
//
//		//--------------------------------------------------------------------------------------
//		// ���ؽ� �� �ȼ� ���̴�
//		//--------------------------------------------------------------------------------------
//		ID3D11VertexShader*     m_pVS;
//		ID3D11PixelShader*      m_pPS;
//		ID3D11GeometryShader*   m_pGS;
//
//		//--------------------------------------------------------------------------------------
//		// ����׿����� ����ϴ� ���� ����
//		//--------------------------------------------------------------------------------------
//		bool					m_bWireFrameRender;
//		int						m_iPrimitiveType;
//
//		//--------------------------------------------------------------------------------------
//		// ���ؽ� �� �ȼ� ���̴�
//		//--------------------------------------------------------------------------------------
//		ID3D11RasterizerState*      m_pRasterizerStateNoCull;
//
//	public:
//		bool		Init();
//		bool		Render();
//		bool		Release();
//		//--------------------------------------------------------------------------------------
//		// ���� �� �Ƚ� ���̵� �ε� �� ����
//		//--------------------------------------------------------------------------------------
//		HRESULT		LoadShaderAndInputLayout();
//		//--------------------------------------------------------------------------------------
//		// ���� ���� ����
//		//--------------------------------------------------------------------------------------
//		HRESULT		CreateVertexBuffer();
//		//--------------------------------------------------------------------------------------
//		// �����Ͷ����� ���°� ����
//		//--------------------------------------------------------------------------------------
//		HRESULT		SetRasterizerState(D3D11_FILL_MODE d3dFillMode = D3D11_FILL_SOLID);
//		//--------------------------------------------------------------------------------------
//		// WndProc : Sample Ŭ���� ����Լ�
//		//--------------------------------------------------------------------------------------
//		LRESULT             MsgProcA(HWND, UINT, WPARAM, LPARAM);
//	public:
//		Sample(LPCTSTR LWndName);
//		virtual ~Sample();
//	};
//
//}