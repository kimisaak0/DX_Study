#pragma once
#include "DxDevice.h"

namespace Lypi
{
	//���� �Լ�
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



//���� ����
//D3D11_BLEND_DESC                                  // ���� ���� ��ü�� �����ϴ� ����ü.
//  BOOL AlphaToCoverageEnable;                        // �ȼ��� ������ Ÿ������ ������ �� ���� ������ ��Ƽ ���ø� ������� ����� �� ���θ� ����.
//  BOOL IndependentBlendEnable;                       // ���� ������ ��󿡼� ���� ���带 ������� ���θ� ����. False�� RT[0]�� ����.
//  D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];    // ������ Ÿ���� ȥ�� ���¸� ����ϴ� ����ü�� �迭.

//D3D11_RENDER_TARGET_BLEND_DESC                    // ���� Ÿ���� ���� ���¸� �����ϴ� ����ü.
//  BOOL BlendEnable;								 // ���� Ȱ��ȭ ����.
//  D3D11_BLEND SrcBlend;							   // �ȼ� ���̴��� ����ϴ� RGB���� ���� ������ ������ ����.
//  D3D11_BLEND DestBlend;							   // ������ ����� ���� RGB���� ���� ������ ������ ����.
//  D3D11_BLEND_OP BlendOp;							  // ���� �� ������ �����ϴ� ����� ����.
//  D3D11_BLEND SrcBlendAlpha;						   // �ȼ� ���̴��� ����ϴ� ���İ��� ���� ������ ������ ����.
//  D3D11_BLEND DestBlendAlpha;						   // ������ ����� ���� ���İ��� ���� ������ ������ ����.
//  D3D11_BLEND_OP BlendOpAlpha;					  // ���� �� ������ �����ϴ� ����� ����.
//  UINT8 RenderTargetWriteMask; 					   // ����ũ�� �����ϴ� ��� ����. (?)
													   
													   
//���� ���ٽ� ����									   
//D3D11_DEPTH_STENCIL_DESC							// ���� ���ٽ� ���¸� �����ϴ� ����ü
//  BOOL DepthEnable;								 // ���� �׽�Ʈ ��� ����.
//  D3D11_DEPTH_WRITE_MASK DepthWriteMask;			   // ���� �����͸� ���µ� �ʿ��� ���ٽ� ���� �κ��� �ĺ�(?)
//  D3D11_COMPARISON_FUNC DepthFunc;				   // ���ο� ���� ���� ���� ���� ���� ���ϴ� �Լ� ����.
//  BOOL StencilEnable;								 // ���ٽ� �׽�Ʈ ��� ����.
//  UINT8 StencilReadMask;							   // ���ٽ� ���� �дµ� �ʿ��� ������ �Ϻθ� �ĺ� (?)
//  UINT8 StencilWriteMask;							   // ���ٽ� ���� ���µ� �ʿ��� ������ �Ϻθ� �ĺ� (?)
//  D3D11_DEPTH_STENCILOP_DESC FrontFace;	       // ����� ī�޶� ���ϰ� �ִ� �ȼ��� ���� ���� �׽�Ʈ ����� ����� ��� ����.
//  D3D11_DEPTH_STENCILOP_DESC BackFace;		   // ����� ī�޶� ���ϰ� �ִ� �ȼ��� ���� ���� �׽�Ʈ ����� ����� ��� ����.

//���ٽ� ���� ����
//D3D11_DEPTH_STENCILOP_DESC                        // ���ٽ� �׽�Ʈ ����� ���� ������ �� �ִ� ���ٽ� �۾��� �����ϴ� ����ü
//  D3D11_STENCIL_OP StencilFailOp;                  // ���ٽ� �׽�Ʈ�� ���� ���� �� ������ ���ٽ� �۾�.
//  D3D11_STENCIL_OP StencilDepthFailOp;             // ���ٽ� �׽�Ʈ�� ���, ���� �׽�Ʈ�� �������� �� ������ ���ٽ� �۾�.
//  D3D11_STENCIL_OP StencilPassOp;					 // �� �׽�Ʈ ��� ������� �� ������ ���ٽ� �۾�.
//  D3D11_COMPARISON_FUNC StencilFunc;				   // ���ο� ���ٽ� ���� ���� ���ٽ� ���� ���ϴ� �Լ�.
													 
													 
//������ ������ ����								
//D3D11_RASTERIZER_DESC 							// ������ ������ ���¸� �����ϴ� ����ü. 
//  D3D11_FILL_MODE FillMode;						  // ������ �� ����� �ʸ�带 ����. (��� ä����)
//  D3D11_CULL_MODE CullMode;						  // ������ �� ����� �ø�带 ����. (��� ��������)
//  BOOL FrontCounterClockwise;						  // False : �ð� ������ �ո� True : �ݽð� ������ �ո�
//  INT DepthBias;									// �־��� �ȼ��� �߰��� ���̰� (?)
//  FLOAT DepthBiasClamp;							// �ȼ��� �ִ� ���̰�. (?)
//  FLOAT SlopeScaledDepthBias;						// ������ �ȼ��� ���⿡ ���� ��Į�� ���̰�. (?)
//  BOOL DepthClipEnable;							// �Ÿ��� ���� Ŭ���� ��� ����. (?)
//  BOOL ScissorEnable;								// ���簢�� �ø� ��� ����. (?)
//  BOOL MultisampleEnable;							    // MSAA ���� Ÿ�ٿ��� ALAA�˰��� ������� ����. (?)
//  BOOL AntialiasedLineEnable;                         // ����AA�� Ȱ������ ���� (�� ���� FALSE�϶��� �����) (?)


//���÷� ����
//D3D11_SAMPLER_DESC                                // ���÷� ���¸� �����ϴ� ����ü
//  D3D11_FILTER Filter;							// �ؽ��ĸ� ���ø� �� ��쿡 ����ϴ� ���͸� ��� (?)
//  D3D11_TEXTURE_ADDRESS_MODE AddressU;			  // �ؽ����� U��ǥ���� 0~1 ������ ������ �ؼ��� ��� ����
//  D3D11_TEXTURE_ADDRESS_MODE AddressV;			  // �ؽ����� Vǥ���� 0~1 ������ ������ �ؼ��� ��� ����
//  D3D11_TEXTURE_ADDRESS_MODE AddressW;			  // �ؽ����� Wǥ���� 0~1 ������ ������ �ؼ��� ��� ����
//  FLOAT MipLODBias;								// �Ӹ� ������ ���ؼ� ���ø��� ������ (?)
//  UINT MaxAnisotropy;								// Filter���� ���� ���Ǵ� Ŭ���� ��. (?)
//  D3D11_COMPARISON_FUNC ComparisonFunc              // ���Ӱ� ���ø��� ���� ������ ���ø� �� ���� ���ϴ� �Լ�.
//  FLOAT BorderColor[4];							// ������ �����Ǿ� �ִ� ��쿡 ����ϴ� ���� Į��. (?)
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