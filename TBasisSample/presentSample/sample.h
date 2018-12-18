#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{

	class Sample : public zCore
	{
		// ���ؽ� ���� �� ���̾ƿ�
		ID3D11Buffer*         m_pVertexBuffer;    //���� ���� �������̽�
		ID3D11Buffer*         m_pIndexBuffer;    //�ε��� ���� �������̽�
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