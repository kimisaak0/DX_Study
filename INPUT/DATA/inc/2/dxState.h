#pragma once
//#include <d3d11.h>
#include "header_DX.h"

namespace D3D
{
	static void ApplyDSS(ID3D11DepthStencilState* pState, UINT iRef = 0x01)
	{
		g_pD3dContext->OMSetDepthStencilState(pState, iRef);
	}

	static void ApplyRS(ID3D11RasterizerState* pState)
	{
		g_pD3dContext->RSSetState(pState);
	}

	static void ApplyBS(ID3D11BlendState* pState, const float fBlendFactor[] = 0, UINT iMask = 0xffffffff)
	{
		g_pD3dContext->OMSetBlendState(pState, fBlendFactor, iMask);
	}

	static void ApplySS(ID3D11SamplerState* pSamplerState, UINT iSlot = 0, UINT iArray = 1)
	{
		g_pD3dContext->PSSetSamplers(iSlot, iArray, &pSamplerState);
	}
}

class xDxState
{
public:
	static ID3D11BlendState* g_pBSNoBlend;
	static ID3D11BlendState* g_pBSAlphaBlend;

	static ID3D11DepthStencilState*   g_pDSVStateEnableLessEqual;
	static ID3D11DepthStencilState*   g_pDSVStateEnableGreater;

	static ID3D11RasterizerState* g_pRSBackWireFrame;
	static ID3D11RasterizerState* g_pRSBackSolid;
	static ID3D11RasterizerState* g_pRSFrontWireFrame;
	static ID3D11RasterizerState* g_pRSFrontSolid;
	static ID3D11RasterizerState* g_pRSNoneWireFrame;
	static ID3D11RasterizerState* g_pRSNoneSolid;

	static ID3D11SamplerState*	g_pSSWrapLinear;
	static ID3D11SamplerState*	g_pSSWrapPoint;

	static HRESULT SetState();
	static bool Release();
public:
	xDxState();
	~xDxState();
};