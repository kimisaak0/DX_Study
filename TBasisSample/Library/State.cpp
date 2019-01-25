#include "State.h"

namespace Lypi
{
	ID3D11RasterizerState*     State::g_pRS[2] = { 0, };
	ID3D11RasterizerState*     State::g_pRSWireFrame;
	ID3D11RasterizerState*     State::g_pRSSolid;
						      
	ID3D11BlendState*          State::g_pBS[2] = { 0, };
	ID3D11BlendState*          State::g_pAlphaBlend;
	ID3D11BlendState*          State::g_pNoAlphaBlend;
							  
	ID3D11SamplerState*        State::g_pSS[2] = { 0, };
	ID3D11SamplerState*        State::g_pTexSS;
	ID3D11SamplerState*        State::g_pSSWrapLinear;
							  
	ID3D11DepthStencilState*   State::g_pDSS[2] = { 0, };
	ID3D11DepthStencilState*   State::g_pDSSDepthEnable;
	ID3D11DepthStencilState*   State::g_pDSSDepthDisable;


	State::State()
	{
		
	}

	HRESULT State::SetState() 
	{
		HRESULT hr = S_OK;

		if (g_pD3dDevice == nullptr) { return S_OK;	}
		if (g_pTexSS != nullptr) { return S_OK; }


		//레스터라이즈 설정 저장
		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));

		rsDesc.DepthClipEnable = TRUE;
		rsDesc.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_BACK;
		V_FRETURN(g_pD3dDevice->CreateRasterizerState(&rsDesc, &g_pRSWireFrame));

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		V_FRETURN(g_pD3dDevice->CreateRasterizerState(&rsDesc, &g_pRSSolid));

		g_pRS[0] = g_pRSWireFrame;
		g_pRS[1] = g_pRSSolid;
		

		//블렌드 설정 저장
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		V_FRETURN(g_pD3dDevice->CreateBlendState(&blendDesc, &g_pAlphaBlend));

		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		V_FRETURN(g_pD3dDevice->CreateBlendState(&blendDesc, &g_pNoAlphaBlend));

		g_pBS[0] = g_pAlphaBlend;
		g_pBS[0] = g_pNoAlphaBlend;

		//샘플러 설정 저장
		D3D11_SAMPLER_DESC spDesc;
		ZeroMemory(&spDesc, sizeof(D3D11_SAMPLER_DESC));

		spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;  // 필터링 방식
		spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // 텍스처 주소 지정 방식
		spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		spDesc.MaxLOD = FLT_MAX; //실수의 최대값 매크로
		spDesc.MinLOD = FLT_MIN; //실수의 최소값 매크로
		V_FRETURN(g_pD3dDevice->CreateSamplerState(&spDesc, &g_pSSWrapLinear));

		spDesc.BorderColor[0] = 1.0f;
		spDesc.BorderColor[1] = 0.0f;
		spDesc.BorderColor[2] = 0.0f;
		spDesc.BorderColor[3] = 1.0f;
		spDesc.MaxAnisotropy = 16;
		spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		spDesc.MipLODBias = 0.0f;
		V_FRETURN(g_pD3dDevice->CreateSamplerState(&spDesc, &g_pTexSS));

		g_pSS[0] = g_pTexSS;
		g_pSS[1] = g_pSSWrapLinear;
	
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		// 깊이버퍼 상태값 세팅
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = FALSE;
		dsDesc.StencilReadMask = 1;
		dsDesc.StencilWriteMask = 1;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		// 디폴트 값
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		V_FRETURN(g_pD3dDevice->CreateDepthStencilState(&dsDesc, &g_pDSSDepthEnable));

		dsDesc.DepthEnable = FALSE;
		V_FRETURN(g_pD3dDevice->CreateDepthStencilState(&dsDesc, &g_pDSSDepthDisable));
		
		g_pDSS[0] = g_pDSSDepthEnable;
		g_pDSS[1] = g_pDSSDepthDisable;

		return hr;
	}

	bool State::Release()
	{
		if (g_pRSWireFrame) { g_pRSWireFrame->Release(); } g_pRSWireFrame = nullptr;
		if (g_pRSSolid) { g_pRSSolid->Release(); } g_pRSSolid = nullptr;

		if (g_pAlphaBlend) { g_pAlphaBlend->Release(); } g_pAlphaBlend = nullptr;
		if (g_pNoAlphaBlend) { g_pNoAlphaBlend->Release(); } g_pAlphaBlend = nullptr;
		
		if (g_pTexSS) { g_pTexSS->Release(); } g_pTexSS = nullptr;
		if (g_pSSWrapLinear) {} {g_pSSWrapLinear->Release(); } g_pSSWrapLinear = nullptr;
		
		if (g_pDSSDepthEnable) { g_pDSSDepthEnable->Release(); } g_pDSSDepthEnable = nullptr;
		if (g_pDSSDepthDisable) { g_pDSSDepthDisable->Release(); } g_pDSSDepthDisable = nullptr;

		return true;
	}

	State::~State()
	{
		Release();
	}
}