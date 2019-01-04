#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	class Object
	{
		ID3D11InputLayout*          m_pInputLayout;     //ÀÎÇ² ·¹ÀÌ¾Æ¿ô
		ID3D11Buffer*               m_pVertexBuffer;    //Á¤Á¡ ¹öÆÛ
		ID3D11VertexShader*         m_pVS;              //Á¤Á¡ ½¦ÀÌ´õ
		ID3D11PixelShader*          m_pPS;              //ÇÈ¼¿ ½¦ÀÌ´õ
		ID3D11ShaderResourceView*   m_pTextureSRV;      //ÅØ½ºÃÄ SRV

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