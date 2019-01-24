#pragma once

#include "ShapeHeader.h"

namespace Lypi
{
	class RenderTarget
	{
	public:
		ComPtr<ID3D11RenderTargetView>    m_pRTV;         //∑ª¥ı≈∏∞Ÿ∫‰
		ComPtr<ID3D11DepthStencilView>    m_pDSV;		  //±Ì¿ÃΩ∫≈ŸΩ«∫‰
		ComPtr<ID3D11ShaderResourceView>  m_pSRV;		  //Ω¶¿Ã¥ı∏Æº“Ω∫∫‰
		ComPtr<ID3D11ShaderResourceView>  m_pDsvSRV;	  //±Ì¿Ãπˆ∆€ ∏Æº“Ω∫∫‰
		ComPtr<ID3D11Texture2D>           m_pTexture;	  //≈ÿΩ∫√ƒ¿ÃπÃ¡ˆ

		D3D11_VIEWPORT                    m_VP;           //∫‰∆˜∆Æ

		D3D11_DEPTH_STENCIL_VIEW_DESC     m_DSVDesc;      //±Ì¿ÃΩ∫≈ŸΩ«∫‰ ¡§∫∏
		D3D11_TEXTURE2D_DESC              m_TexDesc;      //≈ÿΩ∫√ƒ ¡§∫∏
		DXGI_FORMAT                       m_DSFormat;	  //±Ì¿Ã Ω∫≈ŸΩ« ∆˜∏À

		D3DXMATRIX                        m_matProj;      //≈ıøµ«‡∑ƒ

		//¿Ã¿¸ ∑ª¥ı ≈∏∞Ÿ¿ª ¿˙¿Â«—¥Ÿ.
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