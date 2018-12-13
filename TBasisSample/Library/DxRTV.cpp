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

	void DxRTV::Apply(ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, bool bDepthClear = true, bool bStencilClear = true)
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

	HRESULT DxRTV::Create(float fWidth = 1024.f, float fHeight = 1024.f)
	{
		HRESULT hr = S_OK;

	}

	HRESULT DxRTV::CreateCubeMap(float fWidth = 1024.f, float fHeight = 1024.f);
	HRESULT DxRTV::UpdateDSV(UINT uWidth, UINT uHeight);
	HRESULT DxRTV::SaveFile(T_STR szName);
	HRESULT DxRTV::SaveBackBuffer(T_STR szName);
	
	bool DxRTV::Begin(Vector4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
	bool DxRTV::Clear(Vector4 vColor, bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
	bool DxRTV::End();


	
	DxRTV::~DxRTV();
}