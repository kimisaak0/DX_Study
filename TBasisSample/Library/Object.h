#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	class Object
	{
		ID3D11InputLayout*          m_pInputLayout;     //��ǲ ���̾ƿ�
		ID3D11Buffer*               m_pVertexBuffer;    //���� ����
		ID3D11VertexShader*         m_pVS;              //���� ���̴�
		ID3D11PixelShader*          m_pPS;              //�ȼ� ���̴�
		ID3D11ShaderResourceView*   m_pTextureSRV;      //�ؽ��� SRV

	protected:
		PT_VERTEX m_pVertexList[4];

	public:
		virtual bool Init(const TCHAR* pTexFile);
		virtual bool Frame();
		virtual bool Render();
		virtual bool Release();

	public:
		Object();
		virtual ~Object();

	};
}