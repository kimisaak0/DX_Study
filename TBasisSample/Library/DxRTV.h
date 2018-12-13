#pragma once

#include "mathHeader_L.h"
#include "DxState.h"
#include "DxTextureMgr.h"

namespace Lypi
{
	class DxRTV
	{
		ComPtr<ID3D11RenderTargetView>     m_pRTV;
		ComPtr<ID3D11DepthStencilView>     m_pDSV;
		ComPtr<ID3D11ShaderResourceView>   m_pSRV;
		ComPtr<ID3D11ShaderResourceView>   m_pDSRV;
		ComPtr<ID3D11Texture2D>            m_pTexture;
										   
		D3D11_DEPTH_STENCIL_VIEW_DESC    m_DSVDesc;
		D3D11_TEXTURE2D_DESC             m_TexDesc;
		DXGI_FORMAT                      m_DSFormat;
		
		D3D11_VIEWPORT      m_vp;
		stdMatrix           m_matProj;

		//Store the old render targets
		D3D11_VIEWPORT                     m_vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
		UINT                               m_nViewPorts;
		ComPtr<ID3D11RenderTargetView>     m_pOldRTV;
		ComPtr<ID3D11DepthStencilView>     m_pOldDSV;

	public:
		void Set(float fLTx, float fLTy, float fWidth, float fHeight, float fMinDepth = 0.f, float fMaxDepth = 1.f);
		void Apply(ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV = nullptr, bool bDepthClear = true, bool bStencilClear = true);

		HRESULT Create(float fWidth = 1024.f, float fHeight = 1024.f);
		HRESULT CreateCubeMap(float fWidth = 1024.f, float fHeight = 1024.f);
		HRESULT UpdateDSV(UINT uWidth, UINT uHeight);
		HRESULT SaveFile(T_STR szName);
		HRESULT SaveBackBuffer(T_STR szName);

		bool Begin(Vector4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
		bool Clear(Vector4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
		bool End();

	public:
		DxRTV();
		virtual ~DxRTV();
	};
}