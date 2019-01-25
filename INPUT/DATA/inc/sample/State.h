#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	static void ApplyRS(ID3D11RasterizerState* pRState)
	{
		assert(g_pD3dContext);
		g_pD3dContext->RSSetState(pRState);
	}

	static void ApplyDSS(ID3D11DepthStencilState* pDState, UINT iRef = 0x01)
	{
		assert(g_pD3dContext);
		g_pD3dContext->OMSetDepthStencilState(pDState, iRef);
	}

	static void ApplyBS(ID3D11BlendState* pBState, const FLOAT fBlendFactor[] = 0, UINT iMask = 0xffffffff)
	{
		assert(g_pD3dContext);
		g_pD3dContext->OMSetBlendState(pBState, fBlendFactor, iMask);
	}

	static void ApplySS(ID3D11SamplerState* pSamplerState, UINT iSlot = 0, UINT iArray = 1)
	{
		assert(g_pD3dContext);
		g_pD3dContext->PSSetSamplers(iSlot, iArray, &pSamplerState);
	}

	class State
	{
	public:
		static ID3D11RasterizerState* g_pRS[2];
		static ID3D11RasterizerState* g_pRSWireFrame;
		static ID3D11RasterizerState* g_pRSSolid;

		static ID3D11BlendState* g_pBS[2];
		static ID3D11BlendState* g_pAlphaBlend;
		static ID3D11BlendState* g_pNoAlphaBlend;

		static ID3D11SamplerState* g_pSS[2];		
		static ID3D11SamplerState* g_pTexSS;
		static ID3D11SamplerState* g_pSSWrapLinear;

		static ID3D11DepthStencilState* g_pDSS[2];
		static ID3D11DepthStencilState*	g_pDSSDepthEnable;
		static ID3D11DepthStencilState*	g_pDSSDepthDisable;

	public:
		static HRESULT SetState();
		static bool Release();

	public:
		State();
		~State();
	};


}