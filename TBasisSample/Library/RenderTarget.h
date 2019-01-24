#pragma once

#include "ShapeHeader.h"

namespace Lypi
{
	class RenderTarget
	{
	public:
		ComPtr<ID3D11RenderTargetView>    m_pRTV;         //����Ÿ�ٺ�
		ComPtr<ID3D11DepthStencilView>    m_pDSV;		  //���̽��ٽǺ�
		ComPtr<ID3D11ShaderResourceView>  m_pSRV;		  //���̴����ҽ���
		ComPtr<ID3D11ShaderResourceView>  m_pDsvSRV;	  //���̹��� ���ҽ���
		ComPtr<ID3D11Texture2D>           m_pTexture;	  //�ؽ����̹���

		D3D11_VIEWPORT                    m_VP;           //����Ʈ

		D3D11_DEPTH_STENCIL_VIEW_DESC     m_DSVDesc;      //���̽��ٽǺ� ����
		D3D11_TEXTURE2D_DESC              m_TexDesc;      //�ؽ��� ����
		DXGI_FORMAT                       m_DSFormat;	  //���� ���ٽ� ����

		D3DXMATRIX                        m_matProj;      //�������

		//���� ���� Ÿ���� �����Ѵ�.
		D3D11_VIEWPORT  m_OldVP[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
		UINT            m_nViewPorts;
		ID3D11RenderTargetView* m_pOldRTV;
		ID3D11DepthStencilView* m_pOldDSV;

	public:
		void Set(FLOAT TLX, FLOAT TLY, FLOAT width, FLOAT height, FLOAT MinDepth = 0, FLOAT MaxDepth = 1);

		HRESULT Create(FLOAT width = 1024, FLOAT height = 1024);
		HRESULT CreateCubeMap(FLOAT width = 1024, FLOAT height = 1024);

		HRESULT UpdateDepthStencilView(UINT dwWidth, UINT dwHeight);
		void Apply(ID3D11RenderTargetView* pRTV = nullptr, ID3D11DepthStencilView* pDSV = nullptr, bool bDepthClear = true, bool bStencilClear = true);
		
		bool Clear(D3DXVECTOR4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
		bool Begin(D3DXVECTOR4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
		bool End();

	public:
		RenderTarget();
		~RenderTarget();
	};
}