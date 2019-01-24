#include "RenderTarget.h"

namespace Lypi
{
	RenderTarget::RenderTarget()
	{
		m_pRTV = nullptr;
		m_pDSV = nullptr;
		m_pSRV = nullptr;
		m_pTexture = nullptr;
		m_DSFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	}

	void RenderTarget::Set(FLOAT TLX, FLOAT TLY, FLOAT width, FLOAT height, FLOAT MinDepth, FLOAT MaxDepth)
	{
		m_VP.TopLeftX = TLX;
		m_VP.TopLeftY = TLY;
		m_VP.Width = width;
		m_VP.Height = height;
		m_VP.MinDepth = MinDepth;
		m_VP.MaxDepth = MaxDepth;

		D3DXMatrixPerspectiveFovLH(&m_matProj, (float)D3DX_PI*0.25f, width / height, 0.1f, 1000.0f);
	}

	HRESULT RenderTarget::UpdateDepthStencilView(UINT width, UINT height)
	{
		HRESULT hr;
		if (g_pDepthStencilView != nullptr) {
			m_pDSV.ReleaseAndGetAddressOf();
		}

		m_VP.Width = width;
		m_VP.Height = height;

		ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
		D3D11_TEXTURE2D_DESC DepthDesc;
		DepthDesc.Width = width;
		DepthDesc.Height = height;
		DepthDesc.MipLevels = 1;
		DepthDesc.ArraySize = 1;
		DepthDesc.SampleDesc.Count = 1;
		DepthDesc.SampleDesc.Quality = 0;
		DepthDesc.MiscFlags = 0;
		DepthDesc.CPUAccessFlags = 0;
		DepthDesc.Format = m_DSFormat;
		DepthDesc.Usage = D3D11_USAGE_DEFAULT;

		if (DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT) {
			DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		}
		else {
			DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		}

		V_FRETURN(g_pD3dDevice->CreateTexture2D(&DepthDesc, nullptr, &pDSTexture));

		//쉐이더 리소스 생성 : 깊이 맵 쉐도우에서 사용한다.
		D3D11_DEPTH_STENCIL_VIEW_DESC DsvDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC SrvDesc;
		ZeroMemory(&DsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		ZeroMemory(&SrvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		switch (DepthDesc.Format) {
			case DXGI_FORMAT_R32_TYPELESS: {
				DsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
				SrvDesc.Format = DXGI_FORMAT_R32_FLOAT;
			} break;
			case DXGI_FORMAT_D24_UNORM_S8_UINT: {
				DsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				SrvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			} break;
		}

		DsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DsvDesc.Texture2D.MipSlice = 0;
		V_FRETURN(g_pD3dDevice->CreateDepthStencilView(pDSTexture.Get(), &DsvDesc, &m_pDSV));

		//깊이맵일 경우에만 깊이 스텐실 리소스 뷰 생성
		if (DepthDesc.Format == DXGI_FORMAT_R32_TYPELESS) {
			SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			SrvDesc.Texture2D.MipLevels = 1;
			SrvDesc.Texture2D.MostDetailedMip = 0;
			g_pD3dDevice->CreateShaderResourceView(pDSTexture.Get(), &SrvDesc, &m_pDsvSRV);
		}

		g_pDepthStencilView->GetDesc(&m_DSVDesc);
		return hr;
	}

	HRESULT RenderTarget::Create(FLOAT width, FLOAT height)
	{
		HRESULT hr = S_OK;
		Set(0, 0, width, height, 0.0f, 1.0f);

		m_TexDesc.Width = (UINT)width;
		m_TexDesc.Height = (UINT)height;
		m_TexDesc.MipLevels = 1;
		m_TexDesc.ArraySize = 1 ;
		m_TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_TexDesc.SampleDesc.Count = 1;
		m_TexDesc.SampleDesc.Quality = 0;
		m_TexDesc.Usage = D3D11_USAGE_DEFAULT;
		m_TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_TexDesc.CPUAccessFlags = 0;
		m_TexDesc.MiscFlags = 0;

		V_FRETURN(g_pD3dDevice->CreateTexture2D(&m_TexDesc, nullptr, m_pTexture.GetAddressOf()));
		V_FRETURN(g_pD3dDevice->CreateShaderResourceView(m_pTexture.Get(), nullptr, m_pSRV.GetAddressOf()));
		V_FRETURN(g_pD3dDevice->CreateRenderTargetView(m_pTexture.Get(), nullptr, m_pRTV.GetAddressOf()));

		//백버퍼의 크기가 변경되면 깊이스텐실 뷰어도 반드시 재작성되어야 한다.
		UpdateDepthStencilView((UINT)width, (UINT)height);
	}

	HRESULT RenderTarget::CreateCubeMap(FLOAT width, FLOAT height)
	{
		HRESULT hr;
		Set(0, 0, width, height, 0.0f, 1.0f);

		//2D텍스쳐의 구성값을 설정한다.
		D3D11_TEXTURE2D_DESC TexDesc;
		TexDesc.Width = width;
		TexDesc.Height = height;
		TexDesc.MipLevels = 1;
		TexDesc.ArraySize = 6;
		TexDesc.CPUAccessFlags = 0;
		TexDesc.SampleDesc.Count = 1;
		TexDesc.SampleDesc.Quality= 0;
		TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		TexDesc.Usage = D3D11_USAGE_DEFAULT;
		TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		TexDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
		//위의 정보로 2D텍스쳐를 만든다.
		V_FRETURN(g_pD3dDevice->CreateTexture2D(&TexDesc, nullptr, m_pTexture.GetAddressOf()));

		//렌더타겟뷰의 구성값을 설정한다.
		D3D11_RENDER_TARGET_VIEW_DESC RtvDesc;
		RtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		RtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		RtvDesc.Texture2DArray.ArraySize = 6;
		RtvDesc.Texture2DArray.FirstArraySlice = 0;
		RtvDesc.Texture2DArray.MipSlice = 0;
		//위의 정보로 렌더타겟뷰를 만든다.
		V_FRETURN(g_pD3dDevice->CreateRenderTargetView(m_pTexture.Get(), &RtvDesc, m_pRTV.GetAddressOf()));

		//쉐이더 리소스 뷰의 구성값을 설정한다.
		D3D11_SHADER_RESOURCE_VIEW_DESC SrvDesc;
		SrvDesc.Format = TexDesc.Format;
		SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		SrvDesc.Texture2DArray.MipLevels = 1;
		SrvDesc.Texture2DArray.ArraySize = 0;
		SrvDesc.Texture2DArray.FirstArraySlice = 0;
		SrvDesc.Texture2DArray.MostDetailedMip = 0;
		//위의 정보로 쉐이더 리소스 뷰를 만든다.
		V_FRETURN(g_pD3dDevice->CreateShaderResourceView(m_pTexture.Get(), &SrvDesc, m_pSRV.GetAddressOf()));

		//깊이 스텐실 뷰 텍스쳐 생성
		ComPtr<ID3D11Texture2D> pDSTexture = nullptr;

		//2D텍스쳐의 구성값을 설정한다.
		D3D11_TEXTURE2D_DESC DSDesc;
		DSDesc = TexDesc;
		DSDesc.Format = DXGI_FORMAT_D32_FLOAT;
		DSDesc.Usage = D3D11_USAGE_DEFAULT;
		DSDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DSDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
		//위의 정보로 2D텍스쳐를 만든다.
		V_FRETURN(g_pD3dDevice->CreateTexture2D(&DSDesc, nullptr, pDSTexture.GetAddressOf()));

		//깊이 스텐실 뷰의 구성값을 설정한다.
		D3D11_DEPTH_STENCIL_VIEW_DESC DsvDesc;
		DsvDesc.Format = DSDesc.Format;
		DsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		DsvDesc.Texture2DArray.ArraySize = 6;
		DsvDesc.Texture2DArray.FirstArraySlice = 0;
		DsvDesc.Texture2DArray.MipSlice = 0;
		//위의 정보로 깊이 스텐실 뷰를 만든다.
		V_FRETURN(g_pD3dDevice->CreateDepthStencilView(pDSTexture.Get(), &DsvDesc, &m_pDSV));

		return S_OK;
	}


	void RenderTarget::Apply(ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, bool bDepthClear, bool bStencilClear)
	{
		assert(g_pD3dContext);
		assert(pRTV);

		ID3D11RenderTargetView* pNullRTV = NULL;
		g_pD3dContext->OMSetRenderTargets(1, &pNullRTV, NULL);

		if (pRTV != nullptr) {
			if (pDSV != nullptr) {
				g_pD3dContext->OMSetRenderTargets(1, &pRTV, pDSV);
			}
			else {
				g_pD3dContext->OMSetRenderTargets(1, &pRTV, m_pDSV.Get());
			}
		}
		else {
			if (pDSV != nullptr) {
				g_pD3dContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), pDSV);
			}
			else {
				g_pD3dContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());
			}
		}

		if (bDepthClear) {
			if (pDSV != nullptr) {
				g_pD3dContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
			}
			else {
				g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);
			}
		}

		if (bStencilClear) {
			if (pDSV != nullptr) {
				g_pD3dContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_STENCIL, 1.0, 0);
			}
			else {
				g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_STENCIL, 1.0, 0);
			}
		}
		g_pD3dContext->RSSetViewports(1, &m_VP);
	}

	bool RenderTarget::Clear(D3DXVECTOR4 vColor, bool bTargetClear, bool bDepthClear, bool bStencilClear)
	{
		if (bTargetClear) { g_pD3dContext->ClearRenderTargetView(m_pRTV.Get(), vColor); }

		if (bDepthClear) { g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0, 0); }

		if (bStencilClear) { g_pD3dContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_STENCIL, 1.0, 0); }

		g_pD3dContext->RSSetViewports(1, &m_VP);

		return true;
	}

	bool RenderTarget::Begin(D3DXVECTOR4 vColor, bool bTargetClear, bool bDepthClear, bool bStencilClear)
	{
		m_nViewPorts = 1;
		g_pD3dContext->RSGetViewports(&m_nViewPorts, m_OldVP);
		g_pD3dContext->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);

		ID3D11RenderTargetView* pNullRTV = nullptr;
		g_pD3dContext->OMSetRenderTargets(1, &pNullRTV, nullptr);
		g_pD3dContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());

		Clear(vColor, bTargetClear, bDepthClear, bStencilClear);
		g_pD3dContext->RSSetViewports(1, &m_VP);

		return true;
	}

	bool RenderTarget::End()
	{
		g_pD3dContext->RSSetViewports(m_nViewPorts, m_OldVP);
		g_pD3dContext->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);
		SAFE_RELEASE(m_pOldRTV);
		SAFE_RELEASE(m_pOldDSV);

		return true;
	}

	RenderTarget::~RenderTarget()
	{
	}
}
