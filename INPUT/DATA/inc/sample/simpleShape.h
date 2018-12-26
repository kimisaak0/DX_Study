#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	class simpleShape   
	{
		// ���ؽ� ���� �� ���̾ƿ�
		ComPtr<ID3D11InputLayout>	  m_pVertexLayout;    //���� ���̾ƿ� �������̽�
									  
		ComPtr<ID3D11Buffer>          m_pVertexBuffer;    //���� ���� �������̽�
		ComPtr<ID3D11Buffer>          m_pIndexBuffer;     //�ε��� ���� �������̽�
		ID3D11Buffer*                 m_pStreamTo;        //SO���� IA�� �ǵ��� ����
		ID3D11Buffer*                 m_pDrawFrom;        //��¿� ����

		UINT m_uCull_S;
		UINT m_uFill_S;

		// ���ؽ� �� �ȼ� ���̴�
		ComPtr<ID3D11VertexShader>     m_pVS;    //���� ���̴� �������̽�
		ComPtr<ID3D11PixelShader>      m_pPS;	 //�ȼ� ���̴� �������̽�
		ComPtr<ID3D11GeometryShader>   m_pGS;    //���� ���̴� �������̽�
		ComPtr<ID3D11GeometryShader>   m_pSO;    //Stream Output Stage��

		ComPtr<ID3D11RasterizerState>  m_pRS;   //�����Ͷ����� ����

	public:
		HRESULT		CreateVertexBuffer(PC_VERTEX* vertexArray, int aSize);        // ���� ���� ����
		HRESULT     CreateIndexBuffer(DWORD* indexArray, int aSize);         // �ε��� ���� ����
		HRESULT		LoadShaderAndInputLayout();  // ���� �� �Ƚ� ���̴� �ε� �� ����

		HRESULT		RSChange(); // �����Ͷ����� ���� ����

		HRESULT     HandleEffects(ID3D11Buffer* pBuffer); // 

	public:
		bool Init(PC_VERTEX* vertexArray, int vaSize, DWORD* indexArray, int iaSize);
		bool Frame();
		bool Render();
		bool Release();

	public:
		simpleShape();
		virtual ~simpleShape();
	};
}