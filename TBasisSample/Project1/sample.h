#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{
	struct PC_VERTEX
	{
		float3 position;
		float4 color;
	};

	class Sample : public zCore
	{
		// ���ؽ� ���� �� ���̾ƿ�
		ID3D11InputLayout*	  m_pVertexLayout;    //���� ���̾ƿ� �������̽�

		ID3D11Buffer*         m_pVertexBuffer;    //���� ���� �������̽�
		ID3D11Buffer*         m_pIndexBuffer;     //�ε��� ���� �������̽�
		ID3D11Buffer*         m_pStreamTo;        //SO���� IA�� �ǵ��� ����
		ID3D11Buffer*         m_pDrawFrom;        //��¿� ����

												  // ���ؽ� �� �ȼ� ���̴�
		ID3D11VertexShader*     m_pVS;   //���� ���̴� �������̽�
		ID3D11PixelShader*      m_pPS;	 //�ȼ� ���̴� �������̽�
		ID3D11GeometryShader*   m_pGS;   //���� ���̴� �������̽�
		ID3D11GeometryShader*   m_pSO;   //Stream Output Stage��

	public:
		HRESULT		CreateVertexBuffer();        // ���� ���� ����
		HRESULT     CreateIndexBuffer();         // �ε��� ���� ����
		HRESULT		LoadShaderAndInputLayout();  // ���� �� �Ƚ� ���̴� �ε� �� ����


	    HRESULT HandleEffects(ID3D11Buffer* pBuffer); // 

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
