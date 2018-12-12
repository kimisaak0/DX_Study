#pragma once
#include "DxDevice.h"

namespace Lypi
{
	//전역 함수
	void SetDSS(ID3D11DepthStencilState* pDepthStencilState, UINT iRef = 0x01);
	void SetRS(ID3D11RasterizerState* pState);
	void SetBS(ID3D11BlendState* pBlendState, const FLOAT fBlendFactor[] = 0, UINT iMask = 0xffffffff);
	void SetSS(ID3D11SamplerState* pSamplerState, UINT iSlot = 0, UINT iArray = 1);

	struct DxState
	{
		static ID3D11BlendState*	  g_pBSAlphaBlend;
		static ID3D11BlendState*	  g_pBSNoAlphaBlend;
		static ID3D11BlendState*	  g_pBSColorOne;
		static ID3D11BlendState*	  g_pBSOneOne;
		static ID3D11BlendState*	  g_pBSOneZero;
		static ID3D11BlendState*	  g_pBSAlphaOne;
		static ID3D11BlendState*	  g_pBSMaxOneOne;
		static ID3D11BlendState*      g_pBS[7];

		static ID3D11DepthStencilState*	  g_pDSSDepthEnable;
		static ID3D11DepthStencilState*   g_pDSSDepthEnableNoWrite;
		static ID3D11DepthStencilState*	  g_pDSSDepthDisable;
		static ID3D11DepthStencilState*	  g_pDSSDepthDisableNoWrite;
		static ID3D11DepthStencilState*   g_pDSVStateEnableLessEqual;
		static ID3D11DepthStencilState*   g_pDSVStateEnableGreater;
		static ID3D11DepthStencilState*	  g_pDSSDepthStencilAdd;
		static ID3D11DepthStencilState*	  g_pDSSDepthAlways;
		static ID3D11DepthStencilState*	  g_pDSS[8];

		static ID3D11RasterizerState* g_pRSBackWireFrame;
		static ID3D11RasterizerState* g_pRSBackSolid;
		static ID3D11RasterizerState* g_pRSFrontWireFrame;
		static ID3D11RasterizerState* g_pRSFrontSolid;
		static ID3D11RasterizerState* g_pRSNoneWireFrame;
		static ID3D11RasterizerState* g_pRSNoneSolid;
		static ID3D11RasterizerState* g_pRSSlopeScaledDepthBias;
		static ID3D11RasterizerState* g_pRS[7];

		static ID3D11SamplerState*	g_pSSTex;
		static ID3D11SamplerState*	g_pSSWrapLinear;
		static ID3D11SamplerState*	g_pSSWrapPoint;
		static ID3D11SamplerState*  g_pSSMirrorLinear;
		static ID3D11SamplerState*  g_pSSMirrorPoint;
		static ID3D11SamplerState*  g_pSSClampLinear;
		static ID3D11SamplerState*  g_pSSClampPoint;
		static ID3D11SamplerState*  g_pSSShadowMap;
		static ID3D11SamplerState*  g_pSS[8];

	public:
		static HRESULT SetState();
		static bool Release();
		
		DxState();
		~DxState();
	};
}