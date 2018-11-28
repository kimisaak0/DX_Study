#include "dxState.h"

ID3D11BlendState* xDxState::g_pBSAlphaBlend = nullptr;
ID3D11BlendState* xDxState::g_pBSNoBlend = nullptr;

ID3D11DepthStencilState*   xDxState::g_pDSVStateEnableLessEqual = nullptr;
ID3D11DepthStencilState*   xDxState::g_pDSVStateEnableGreater = nullptr;

ID3D11RasterizerState* xDxState::g_pRSBackWireFrame = nullptr;
ID3D11RasterizerState* xDxState::g_pRSBackSolid = nullptr;
ID3D11RasterizerState* xDxState::g_pRSFrontWireFrame = nullptr;
ID3D11RasterizerState* xDxState::g_pRSFrontSolid = nullptr;
ID3D11RasterizerState* xDxState::g_pRSNoneWireFrame = nullptr;
ID3D11RasterizerState* xDxState::g_pRSNoneSolid = nullptr;

ID3D11SamplerState*	xDxState::g_pSSWrapLinear = nullptr;
ID3D11SamplerState*	xDxState::g_pSSWrapPoint = nullptr;

xDxState::xDxState() { }

HRESULT xDxState::SetState()
{
	HRESULT hr;

	//blend//
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	hr = g_pD3dDevice->CreateBlendState(&bd, &g_pBSAlphaBlend);

	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	hr = g_pD3dDevice->CreateBlendState(&bd, &g_pBSNoBlend);

	//depth_stencil//
	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(dsd));
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	hr = g_pD3dDevice->CreateDepthStencilState(&dsd, &g_pDSVStateEnableLessEqual);

	dsd.DepthFunc = D3D11_COMPARISON_GREATER;
	hr = g_pD3dDevice->CreateDepthStencilState(&dsd, &g_pDSVStateEnableGreater);
	
	//rasterrizer//
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.DepthClipEnable = TRUE;
	rd.CullMode = D3D11_CULL_BACK;

	rd.FillMode = D3D11_FILL_WIREFRAME;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSBackWireFrame);
	rd.FillMode = D3D11_FILL_SOLID;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSBackSolid);

	rd.CullMode = D3D11_CULL_FRONT;

	rd.FillMode = D3D11_FILL_WIREFRAME;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSFrontWireFrame);
	rd.FillMode = D3D11_FILL_SOLID;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSFrontSolid);

	rd.CullMode = D3D11_CULL_NONE;

	rd.FillMode = D3D11_FILL_WIREFRAME;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSNoneWireFrame);
	rd.FillMode = D3D11_FILL_SOLID;
	hr = g_pD3dDevice->CreateRasterizerState(&rd, &g_pRSNoneSolid);

	//sampler//
	D3D11_SAMPLER_DESC sd;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	
	sd.MipLODBias = 0;
	sd.MaxAnisotropy = 16;

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;

	sd.BorderColor[0] = 1.0f;
	sd.BorderColor[1] = 0.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 1.0f;

	sd.MinLOD = 0;
	sd.MaxLOD = D3D10_FLOAT32_MAX;
	hr = g_pD3dDevice->CreateSamplerState(&sd, &g_pSSWrapLinear);

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = g_pD3dDevice->CreateSamplerState(&sd, &g_pSSWrapPoint);

	return hr;
}

bool xDxState::Release()
{
	if (g_pDSVStateEnableLessEqual)g_pDSVStateEnableLessEqual->Release();
	if (g_pDSVStateEnableGreater) g_pDSVStateEnableGreater->Release();

	if (g_pRSBackWireFrame) g_pRSBackWireFrame->Release();
	if (g_pRSBackSolid) g_pRSBackSolid->Release();
	if (g_pRSFrontWireFrame) g_pRSFrontWireFrame->Release();
	if (g_pRSFrontSolid) g_pRSFrontSolid->Release();
	if (g_pRSNoneWireFrame) g_pRSNoneWireFrame->Release();
	if (g_pRSNoneSolid) g_pRSNoneSolid->Release();

	if (g_pBSNoBlend) g_pBSNoBlend->Release();
	if (g_pBSAlphaBlend) g_pBSAlphaBlend->Release();

	if (g_pSSWrapLinear) g_pSSWrapLinear->Release();
	if (g_pSSWrapPoint) g_pSSWrapPoint->Release();

	return true;
}

xDxState::~xDxState() { }
