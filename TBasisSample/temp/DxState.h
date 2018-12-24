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
		static ID3D11BlendState*	       g_pBSDefault;

		static ID3D11DepthStencilState*	   g_pDSSDefault;

		static ID3D11RasterizerState*      g_pRSDefault;

		static ID3D11SamplerState*	       g_pSSDefault;

	public:
		static HRESULT SetState();
		static bool Release();
		
		DxState();
		~DxState();
	};
}



//블렌드 설정
//D3D11_BLEND_DESC                                  // 블렌드 상태 개체를 지정하는 구조체.
//  BOOL AlphaToCoverageEnable;                        // 픽셀을 렌더링 타겟으로 설정할 때 알파 샘플을 멀티 샘플링 기법으로 사용할 지 여부를 지정.
//  BOOL IndependentBlendEnable;                       // 동시 렌더링 대상에서 독립 블렌드를 사용할지 여부를 지정. False시 RT[0]만 사용됨.
//  D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];    // 렌더링 타겟의 혼합 상태를 기술하는 구조체의 배열.

//D3D11_RENDER_TARGET_BLEND_DESC                    // 렌더 타겟의 블렌드 상태를 지정하는 구조체.
//  BOOL BlendEnable;								 // 블렌딩 활성화 유무.
//  D3D11_BLEND SrcBlend;							   // 픽셀 쉐이더가 출력하는 RGB값에 대해 수행할 연산을 지정.
//  D3D11_BLEND DestBlend;							   // 렌더링 대상의 현재 RGB값에 대해 수행할 연산을 지정.
//  D3D11_BLEND_OP BlendOp;							  // 위의 두 연산을 결합하는 방법을 정의.
//  D3D11_BLEND SrcBlendAlpha;						   // 픽셀 쉐이더가 출력하는 알파값에 대해 수행할 연산을 지정.
//  D3D11_BLEND DestBlendAlpha;						   // 렌더링 대상의 현재 알파값에 대해 수행할 연산을 지정.
//  D3D11_BLEND_OP BlendOpAlpha;					  // 위의 두 연산을 결합하는 방법을 정의.
//  UINT8 RenderTargetWriteMask; 					   // 마스크에 기입하는 방법 지정. (?)
													   
													   
//깊이 스텐실 설정									   
//D3D11_DEPTH_STENCIL_DESC							// 깊이 스텐실 상태를 지정하는 구조체
//  BOOL DepthEnable;								 // 깊이 테스트 사용 여부.
//  D3D11_DEPTH_WRITE_MASK DepthWriteMask;			   // 깊이 데이터를 쓰는데 필요한 스텐실 버퍼 부분을 식별(?)
//  D3D11_COMPARISON_FUNC DepthFunc;				   // 새로운 깊이 값과 기존 깊이 값을 비교하는 함수 지정.
//  BOOL StencilEnable;								 // 스텐실 테스트 사용 여부.
//  UINT8 StencilReadMask;							   // 스텐실 값을 읽는데 필요한 버퍼의 일부를 식별 (?)
//  UINT8 StencilWriteMask;							   // 스텐실 값을 쓰는데 필요한 버퍼의 일부를 식별 (?)
//  D3D11_DEPTH_STENCILOP_DESC FrontFace;	       // 노멀이 카메라를 향하고 있는 픽셀에 대해 깊이 테스트 결과를 사용할 방법 지정.
//  D3D11_DEPTH_STENCILOP_DESC BackFace;		   // 노멀이 카메라를 반하고 있는 픽셀에 대해 깊이 테스트 결과를 사용할 방법 지정.

//스텐실 연산 설정
//D3D11_DEPTH_STENCILOP_DESC                        // 스텐실 테스트 결과에 따라 수행할 수 있는 스텐실 작업을 지정하는 구조체
//  D3D11_STENCIL_OP StencilFailOp;                  // 스텐실 테스트가 실패 했을 때 수행할 스텐실 작업.
//  D3D11_STENCIL_OP StencilDepthFailOp;             // 스텐실 테스트는 통과, 깊이 테스트는 실패했을 때 수행할 스텐실 작업.
//  D3D11_STENCIL_OP StencilPassOp;					 // 두 테스트 모두 통과했을 때 수행할 스텐실 작업.
//  D3D11_COMPARISON_FUNC StencilFunc;				   // 새로운 스텐실 값을 기존 스텐실 값과 비교하는 함수.
													 
													 
//레스터 라이저 설정								
//D3D11_RASTERIZER_DESC 							// 레스터 라이저 상태를 지정하는 구조체. 
//  D3D11_FILL_MODE FillMode;						  // 렌더링 시 사용할 필모드를 설정. (어떻게 채울지)
//  D3D11_CULL_MODE CullMode;						  // 렌더링 시 사용할 컬모드를 설정. (어디를 생략할지)
//  BOOL FrontCounterClockwise;						  // False : 시계 방향이 앞면 True : 반시계 방향이 앞면
//  INT DepthBias;									// 주어진 픽셀에 추가된 깊이값 (?)
//  FLOAT DepthBiasClamp;							// 픽셀의 최대 깊이값. (?)
//  FLOAT SlopeScaledDepthBias;						// 지정된 픽셀의 기울기에 대한 스칼라 깊이값. (?)
//  BOOL DepthClipEnable;							// 거리에 따른 클리핑 사용 여부. (?)
//  BOOL ScissorEnable;								// 직사각형 컬링 사용 여부. (?)
//  BOOL MultisampleEnable;							    // MSAA 렌더 타겟에서 ALAA알고리즘 사용할지 여부. (?)
//  BOOL AntialiasedLineEnable;                         // 선형AA를 활성할지 여부 (위 값이 FALSE일때만 적용됨) (?)


//샘플러 설정
//D3D11_SAMPLER_DESC                                // 샘플러 상태를 지정하는 구조체
//  D3D11_FILTER Filter;							// 텍스쳐를 샘플링 할 경우에 사용하는 필터링 방법 (?)
//  D3D11_TEXTURE_ADDRESS_MODE AddressU;			  // 텍스쳐의 U좌표값이 0~1 범위를 넘을때 해석할 방법 지정
//  D3D11_TEXTURE_ADDRESS_MODE AddressV;			  // 텍스쳐의 V표값이 0~1 범위를 넘을때 해석할 방법 지정
//  D3D11_TEXTURE_ADDRESS_MODE AddressW;			  // 텍스쳐의 W표값이 0~1 범위를 넘을때 해석할 방법 지정
//  FLOAT MipLODBias;								// 밉맵 레벨에 더해서 샘플링할 레벨값 (?)
//  UINT MaxAnisotropy;								// Filter값에 따라 사용되는 클램핑 값. (?)
//  D3D11_COMPARISON_FUNC ComparisonFunc              // 새롭게 샘플링된 값을 기존에 샘플링 된 값과 비교하는 함수.
//  FLOAT BorderColor[4];							// 보더가 지정되어 있는 경우에 사용하는 보더 칼라. (?)
//  FLOAT MinLOD;									// ...?
//  FLOAT MaxLOD;									// ...?








//static ID3D11BlendState*	       g_pBSAlphaBlend;
//static ID3D11BlendState*	       g_pBSNoAlphaBlend;
//static ID3D11BlendState*	       g_pBSColorOne;
//static ID3D11BlendState*	       g_pBSOneOne;
//static ID3D11BlendState*	       g_pBSOneZero;
//static ID3D11BlendState*	       g_pBSAlphaOne;
//static ID3D11BlendState*	       g_pBSMaxOneOne;
//static ID3D11BlendState*           g_pBS[7];

//static ID3D11DepthStencilState*	   g_pDSSDepthEnable;
//static ID3D11DepthStencilState*    g_pDSSDepthEnableNoWrite;
//static ID3D11DepthStencilState*	   g_pDSSDepthDisable;
//static ID3D11DepthStencilState*	   g_pDSSDepthDisableNoWrite;
//static ID3D11DepthStencilState*    g_pDSVStateEnableLessEqual;
//static ID3D11DepthStencilState*    g_pDSVStateEnableGreater;
//static ID3D11DepthStencilState*	   g_pDSSDepthStencilAdd;
//static ID3D11DepthStencilState*	   g_pDSSDepthAlways;
//static ID3D11DepthStencilState*	   g_pDSS[8];

//static ID3D11RasterizerState*      g_pRSBackWireFrame;
//static ID3D11RasterizerState*      g_pRSBackSolid;
//static ID3D11RasterizerState*      g_pRSFrontWireFrame;
//static ID3D11RasterizerState*      g_pRSFrontSolid;
//static ID3D11RasterizerState*      g_pRSNoneWireFrame;
//static ID3D11RasterizerState*      g_pRSNoneSolid;
//static ID3D11RasterizerState*      g_pRSSlopeScaledDepthBias;
//static ID3D11RasterizerState*      g_pRS[7];

//static ID3D11SamplerState*	       g_pSSTex;
//static ID3D11SamplerState*	       g_pSSWrapLinear;
//static ID3D11SamplerState*	       g_pSSWrapPoint;
//static ID3D11SamplerState*         g_pSSMirrorLinear;
//static ID3D11SamplerState*         g_pSSMirrorPoint;
//static ID3D11SamplerState*         g_pSSClampLinear;
//static ID3D11SamplerState*         g_pSSClampPoint;
//static ID3D11SamplerState*         g_pSSShadowMap;
//static ID3D11SamplerState*         g_pSS[8];