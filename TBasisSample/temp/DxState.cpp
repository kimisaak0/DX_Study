#include "DxState.h"

namespace Lypi
{
	//전역함수
	void SetDSS(ID3D11DepthStencilState* pState, UINT iRef)
	{
		g_pD3dContext->OMSetDepthStencilState(pState, iRef);
	}

	void SetRS(ID3D11RasterizerState* pState)
	{
		g_pD3dContext->RSSetState(pState);
	}

	void SetBS(ID3D11BlendState* pState, const FLOAT fBlendFactor[], UINT iMask)
	{
		g_pD3dContext->OMSetBlendState(pState, fBlendFactor, iMask);
	}

	void SetSS(ID3D11SamplerState* pSamplerState, UINT iSlot, UINT iArray)
	{
		g_pD3dContext->PSSetSamplers(iSlot, iArray, &pSamplerState);
	}

	ID3D11BlendState*          g_pBSDefault  = nullptr;
	ID3D11DepthStencilState*   g_pDSSDefault = nullptr;
	ID3D11RasterizerState*     g_pRSDefault  = nullptr;
	ID3D11SamplerState*	       g_pSSDefault  = nullptr;
						     

	DxState::DxState() { }

	HRESULT DxState::SetState()
	{
		HRESULT hr;

		//blend//
		D3D11_BLEND_DESC bd;
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = FALSE;																												  
		bd.RenderTarget[0].BlendEnable = FALSE;                                          
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;								 
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;							 
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;							 
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		 

		hr = g_pD3dDevice->CreateBlendState(&bd, &g_pBSDefault);

		//depth_stencil//
		D3D11_DEPTH_STENCIL_DESC dsd;
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		dsd.StencilEnable = FALSE;
		dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

		hr = g_pD3dDevice->CreateDepthStencilState(&dsd, &g_pDSSDefault);

		//rasterizer//
		D3D11_RASTERIZER_DESC rd;
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		rd.FrontCounterClockwise = FALSE;
		rd.DepthBias = 0;
		rd.DepthBiasClamp = 0.0f;
		rd.SlopeScaledDepthBias = 0.0f;
		rd.DepthClipEnable = TRUE;
		rd.ScissorEnable = FALSE;
		rd.MultisampleEnable = FALSE;
		rd.AntialiasedLineEnable = FALSE;

		hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSDefault);

		//sampler//
		D3D11_SAMPLER_DESC sd;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.MipLODBias = 0.0f;
		sd.MaxAnisotropy = 1;
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sd.BorderColor[0] = 1.0f;
		sd.BorderColor[1] = 1.0f;
		sd.BorderColor[2] = 1.0f;
		sd.BorderColor[3] = 1.0f;
		sd.MinLOD = -FLT_MAX;
		sd.MaxLOD = FLT_MAX;

		hr = g_pD3dDevice->CreateSamplerState(&sd, &g_pSSDefault);

		return hr;
	}

	bool DxState::Release()
	{
		if (g_pBSDefault) g_pBSDefault->Release();
		if (g_pDSSDefault) g_pDSSDefault->Release();
		if (g_pRSDefault) g_pRSDefault->Release();
		if (g_pSSDefault) g_pSSDefault->Release();

		return true;
	}

	DxState::~DxState() { }

}






//ID3D11BlendState*	          DxState::g_pBSAlphaBlend = nullptr;
//ID3D11BlendState*	          DxState::g_pBSNoAlphaBlend = nullptr;
//ID3D11BlendState*	          DxState::g_pBSColorOne = nullptr;
//ID3D11BlendState*	          DxState::g_pBSOneOne = nullptr;
//ID3D11BlendState*	          DxState::g_pBSOneZero = nullptr;
//ID3D11BlendState*	          DxState::g_pBSAlphaOne = nullptr;
//ID3D11BlendState*	          DxState::g_pBSMaxOneOne = nullptr;
//ID3D11BlendState*	          DxState::g_pBS[7] = { 0, };

//ID3D11DepthStencilState*	  DxState::g_pDSSDepthEnable = nullptr;
//ID3D11DepthStencilState*      DxState::g_pDSSDepthEnableNoWrite = nullptr;
//ID3D11DepthStencilState*	  DxState::g_pDSSDepthDisable = nullptr;
//ID3D11DepthStencilState*	  DxState::g_pDSSDepthDisableNoWrite = nullptr;
//ID3D11DepthStencilState*      DxState::g_pDSVStateEnableLessEqual = nullptr;
//ID3D11DepthStencilState*      DxState::g_pDSVStateEnableGreater = nullptr;
//ID3D11DepthStencilState*	  DxState::g_pDSSDepthStencilAdd = nullptr;
//ID3D11DepthStencilState*	  DxState::g_pDSSDepthAlways = nullptr;
//ID3D11DepthStencilState*	  DxState::g_pDSS[8] = { 0, };

//ID3D11RasterizerState*        DxState::g_pRSBackWireFrame = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSBackSolid = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSFrontWireFrame = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSFrontSolid = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSNoneWireFrame = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSNoneSolid = nullptr;
//ID3D11RasterizerState*        DxState::g_pRSSlopeScaledDepthBias = nullptr;
//ID3D11RasterizerState*        DxState::g_pRS[7] = { 0, };

//ID3D11SamplerState*           DxState::g_pSSTex = nullptr;
//ID3D11SamplerState*           DxState::g_pSSWrapLinear = nullptr;
//ID3D11SamplerState*           DxState::g_pSSWrapPoint = nullptr;
//ID3D11SamplerState*           DxState::g_pSSMirrorLinear = nullptr;
//ID3D11SamplerState*           DxState::g_pSSMirrorPoint = nullptr;
//ID3D11SamplerState*           DxState::g_pSSClampLinear = nullptr;
//ID3D11SamplerState*           DxState::g_pSSClampPoint = nullptr;
//ID3D11SamplerState*           DxState::g_pSSShadowMap = nullptr;
//ID3D11SamplerState*           DxState::g_pSS[8] = { 0, };



//if (g_pDSVStateEnableLessEqual)g_pDSVStateEnableLessEqual->Release();
//if (g_pDSVStateEnableGreater) g_pDSVStateEnableGreater->Release();

//if (g_pRSBackWireFrame) g_pRSBackWireFrame->Release();
//if (g_pRSBackSolid) g_pRSBackSolid->Release();
//if (g_pRSFrontWireFrame) g_pRSFrontWireFrame->Release();
//if (g_pRSFrontSolid) g_pRSFrontSolid->Release();
//if (g_pRSNoneWireFrame) g_pRSNoneWireFrame->Release();
//if (g_pRSNoneSolid) g_pRSNoneSolid->Release();

//if (g_pBSNoBlend) g_pBSNoBlend->Release();
//if (g_pBSAlphaBlend) g_pBSAlphaBlend->Release();

//if (g_pSSWrapLinear) g_pSSWrapLinear->Release();
//if (g_pSSWrapPoint) g_pSSWrapPoint->Release();