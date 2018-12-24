#include "DxRTV.h"

namespace Lypi
{
	DxRTV::DxRTV()
	{
		m_pRTV = nullptr;
		m_pDSV = nullptr;
		m_pSRV = nullptr;
		m_pTexture = nullptr;

		m_DSFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	}

	void DxRTV::Set(float fLTx, float fLTy, float fWidth, float fHeight, float fMinDepth, float fMaxDepth)
	{
		m_vp.TopLeftX = fLTx;
		m_vp.TopLeftY = fLTy;
		m_vp.Width = fWidth;
		m_vp.Height = fHeight;
		m_vp.MinDepth = fMinDepth;
		m_vp.MaxDepth = fMaxDepth;

		m_matProj = PerspectiveFovLH((float)L_Pi * 0.25f, fWidth / fHeight, 0.1f, 1000.f);
	}

	void DxRTV::Apply(ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, bool bDepthClear, bool bStencilClear)
	{
		assert(pRTV);

		ID3D11RenderTargetView* pNullRTV = nullptr;

		g_pD3dContext->OMSetRenderTargets(1, &pNullRTV, nullptr);

		if (pDSV != NULL) {
			g_pD3dContext->OMSetRenderTargets(1, &pRTV, pDSV);
		}
		else {
			g_pD3dContext->OMSetRenderTargets(1, &pRTV, m_pDSV.Get());
		}
	}


	HRESULT DxRTV::Create(float fWidth, float fHeight)
	{
		HRESULT hr = S_OK;
		Set(0, 0, fWidth, fHeight);

		m_TexDesc.Width = (UINT)fWidth;
		m_TexDesc.Height = (UINT)fHeight;
		m_TexDesc.MipLevels = 1;
		m_TexDesc.ArraySize = 1;
		m_TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_TexDesc.SampleDesc.Count = 1;
		m_TexDesc.SampleDesc.Quality = 0;
		m_TexDesc.Usage = D3D11_USAGE_DEFAULT;
		m_TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_TexDesc.CPUAccessFlags = 0;
		m_TexDesc.MiscFlags = 0;

		V_FRETURN(g_pD3dDevice->CreateTexture2D(&m_TexDesc, nullptr, &m_pTexture));
		V_FRETURN(g_pD3dDevice->CreateShaderResourceView(m_pTexture.Get(), nullptr, &m_pSRV));
		V_FRETURN(g_pD3dDevice->CreateRenderTargetView(m_pTexture.Get(), nullptr, &m_pRTV));
		V_FRETURN(UpdateDSV((UINT)fWidth, (UINT)fHeight));

		return hr;
	}

	HRESULT DxRTV::UpdateDSV(UINT uWidth, UINT uHeight)
	{
		HRESULT hr;

		if (m_pDSV != nullptr) {
			m_pDSV.Reset();
		}

		m_vp.Width = (FLOAT)uWidth;
		m_vp.Height = (FLOAT)uHeight;

		ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
		D3D11_TEXTURE2D_DESC DescDepth;
		DescDepth.Width = uWidth;
		DescDepth.Height = uHeight;
		DescDepth.MipLevels = 1;
		DescDepth.ArraySize = 1;
		DescDepth.Format = m_DSFormat;
		DescDepth.SampleDesc.Count = 1;
		DescDepth.SampleDesc.Quality = 0;
		DescDepth.Usage = D3D11_USAGE_DEFAULT;

		if (DescDepth.Format == DXGI_FORMAT_D24_UNORM_S8_UINT) { // πÈ πˆ∆€ π◊ ±Ì¿Ã Ω∫≈ŸΩ« πˆ∆€ ª˝º∫
			DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		}
		else { // ±Ì¿Ã∏  ¿¸øÎ ±Ì¿Ã∏  ª˝º∫
			DescDepth.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		}

		DescDepth.CPUAccessFlags = 0;
		DescDepth.MiscFlags = 0;

		V_FRETURN(g_pD3dDevice->CreateTexture2D(&DescDepth, nullptr, &pDSTexture));
		
		// Ω¶¿Ã¥ı ∏Æº“Ω∫ ª˝º∫ : ±Ì¿Ã ∏  Ω¶µµøÏø°º≠ ªÁøÎ«—¥Ÿ. //
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		switch (DescDepth.Format) {
			case DXGI_FORMAT_R32_TYPELESS: {
				dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
				srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
			} break;

			case DXGI_FORMAT_D24_UNORM_S8_UINT: {
				dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			} break;
		}

		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		V_FRETURN(g_pD3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, &m_pDSV));

		//±Ì¿Ã∏ ¿œ ∞ÊøÏø°∏∏ ª˝º∫«—¥Ÿ.
		if (DescDepth.Format == DXGI_FORMAT_R32_TYPELESS) {
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = 1;
			g_pD3dDevice->CreateShaderResourceView(pDSTexture.Get(), &srvDesc, &m_pDSRV);
		}

		m_pDSV->GetDesc(&m_DSVDesc);
		return hr;

	}

	HRESULT DxRTV::CreateCubeMap(float fWidth, float fHeight)
	{
		HRESULT hr = S_OK;
		Set(0, 0, fWidth, fHeight);

		//∑ª¥ı≈∏ƒœøÎ ≈ÿΩ∫√ƒ ª˝º∫
		D3D11_TEXTURE2D_DESC TexDesc;
		TexDesc.Width = (UINT)fWidth;
		TexDesc.Height = (UINT)fHeight;
		TexDesc.MipLevels = 1;
		TexDesc.ArraySize = 6;
		TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		TexDesc.SampleDesc.Count = 1;
		TexDesc.SampleDesc.Quality = 0;
		TexDesc.Usage = D3D11_USAGE_DEFAULT;
		TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		TexDesc.CPUAccessFlags = 0;
		TexDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
		V_FRETURN(g_pD3dDevice->CreateTexture2D(&TexDesc, NULL, &m_pTexture));

		//∑ª¥ı≈∏ƒœøÎ ∫‰ ª˝º∫
		D3D11_RENDER_TARGET_VIEW_DESC RtvDesc;
		ZeroMemory(&RtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		RtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		RtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		RtvDesc.Texture2DArray.ArraySize = 6;
		V_FRETURN(g_pD3dDevice->CreateRenderTargetView(m_pTexture.Get(), &RtvDesc, &m_pRTV));

		// Ω¶¿Ã¥ı ∏Æº“Ω∫ ∫‰ ª˝º∫
		D3D11_SHADER_RESOURCE_VIEW_DESC SrvDesc;
		ZeroMemory(&SrvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		SrvDesc.Format = TexDesc.Format;
		SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		SrvDesc.Texture2DArray.MipLevels = 1;
		V_FRETURN(g_pD3dDevice->CreateShaderResourceView(m_pTexture.Get(), &SrvDesc, &m_pSRV));

		// ±Ì¿Ã Ω∫≈ŸΩ« ∫‰ ≈ÿΩ∫√≥ ª˝º∫
		ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
		D3D11_TEXTURE2D_DESC DSDesc;
		DSDesc.Width = (UINT)fWidth;
		DSDesc.Height = (UINT)fHeight;
		DSDesc.MipLevels = 1;
		DSDesc.ArraySize = 6;
		DSDesc.Format = DXGI_FORMAT_D32_FLOAT;
		DSDesc.SampleDesc.Count = 1;
		DSDesc.SampleDesc.Quality = 0;
		DSDesc.Usage = D3D11_USAGE_DEFAULT;
		DSDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DSDesc.CPUAccessFlags = 0;
		DSDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;


		V_FRETURN(g_pD3dDevice->CreateTexture2D(&DSDesc, NULL, &pDSTexture));

		// ±Ì¿Ã Ω∫≈ŸΩ« ∫‰ ª˝º∫
		D3D11_DEPTH_STENCIL_VIEW_DESC DsvDesc;
		ZeroMemory(&DsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		DsvDesc.Format = DSDesc.Format;
		DsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		DsvDesc.Texture2DArray.ArraySize = 6;
		V_FRETURN(g_pD3dDevice->CreateDepthStencilView(pDSTexture.Get(), &DsvDesc, &m_pDSV));
		return S_OK;

	}

	HRESULT DxRTV::SaveFile(T_STR szName)
	{
		HRESULT hr = S_OK;

		//∑ª¥ı≈∏∞Ÿ∫‰ø°º≠ ≈ÿΩ∫√≥ ∆ƒ¿œ∑Œ ¿˙¿Â
		if (m_pTexture != nullptr) {
			//∑ª¥ı≈∏∞Ÿ ≈ÿΩ∫√ƒ∏¶ ≈ÿΩ∫√ƒ ∆ƒ¿œ∑Œ ¿˙¿Â
			V_FRETURN(D3DX11SaveTextureToFile(g_pD3dContext, m_pTexture.Get(), D3DX11_IFF_DDS, szName.c_str()));
		}
		else  if (m_pSRV != nullptr) {
			ID3D11Resource* resource;
			m_pSRV.Get()->GetResource(&resource);

			ID3D11Texture2D* texture;
			V_FRETURN(resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&texture)));
			V_FRETURN(D3DX11SaveTextureToFile(g_pD3dContext, texture, D3DX11_IFF_DDS, szName.c_str()));
			texture->Release();
		}

		return hr;
	}

	HRESULT DxRTV::SaveBackBuffer(T_STR szName)
	{
		HRESULT hr = S_OK;
		ID3D11Resource* BackBufferResource;
		m_pRTV.Get()->GetResource(&BackBufferResource);
		D3D11_TEXTURE2D_DESC desc;
		m_pTexture.Get()->GetDesc(&desc);

		ID3D11Texture2D* texture;
		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = desc.Width;
		texDesc.Height = desc.Height;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = desc.Format;
		texDesc.SampleDesc = desc.SampleDesc;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = 0;
		texDesc.CPUAccessFlags = desc.CPUAccessFlags;
		texDesc.MiscFlags = 0;

		V_FRETURN(g_pD3dDevice->CreateTexture2D(&texDesc, 0, &texture));
		g_pD3dContext->CopyResource(texture, BackBufferResource);

		V_FRETURN(D3DX11SaveTextureToFile(g_pD3dContext, texture, D3DX11_IFF_BMP, szName.c_str()));
		texture->Release();
		BackBufferResource->Release();
		return hr;
	}
	
	bool DxRTV::Clear(D3DXVECTOR4 vColor, bool bTargetClear, bool bDepthClear, bool bStencilClear)
	{
		if (bTargetClear)
		{
			g_pD3dContext->ClearRenderTargetView(m_pRTV.Get(), vColor);
		}
		if (bDepthClear)
		{
			g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);
		}
		if (bStencilClear)
		{
			g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_STENCIL, 1.0, 0);
		}
		g_pD3dContext->RSSetViewports(1, &m_vp);
		return true;
	}

	bool DxRTV::Begin(D3DXVECTOR4 vColor, bool bTargetClear, bool bDepthClear, bool bStencilClear)
	{
		m_nViewPorts = 1;
		g_pD3dContext->RSGetViewports(&m_nViewPorts, m_vpOld);
		g_pD3dContext->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);

		ID3D11RenderTargetView* pNullRTV = NULL;
		g_pD3dContext->OMSetRenderTargets(1, &pNullRTV, NULL);
		g_pD3dContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());

		Clear(vColor, bTargetClear, bDepthClear, bStencilClear);
		g_pD3dContext->RSSetViewports(1, &m_vp);
		return true;
	}

	bool DxRTV::End()
	{
		g_pD3dContext->RSSetViewports(m_nViewPorts, m_vpOld);
		g_pD3dContext->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);

		m_pOldRTV->Release(); 
		m_pOldRTV = nullptr;

		m_pOldDSV->Release();
		m_pOldDSV = nullptr;

		return true;
	}

	DxRTV::~DxRTV()
	{

	}
}