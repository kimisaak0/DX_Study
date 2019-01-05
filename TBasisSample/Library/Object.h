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

		ID3D11RasterizerState*      m_pRaster;
		ID3D11BlendState*           m_pBlend;
		ID3D11SamplerState*         m_pSampler;

	protected:
		uint3 m_center;
		int m_HarpWidth, m_HarpHeight;

		uLTRB m_uSRegion;
		fLTRB m_fPRegion;

		PCT_VERTEX m_pVertexList[4];
		

	public:
		void    VertexSetting(uint3 center, uWH size);
		HRESULT Create(const TCHAR* pTexFile, uint3 center, uWH size);

	public:
		virtual bool Init(const TCHAR* pTexFile, uint3 center, uWH size);
		virtual bool Frame();
		virtual bool Render();
		virtual bool Release();

	public:
		Object();
		virtual ~Object();

	};
}