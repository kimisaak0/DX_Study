#pragma once
#include "13c_ButtonDX.h"

class Sample : public coreC_DX
{
public:
	ButtonDX m_Actor[1];
	PCT_VERTEX m_FrameVertexList[6];
	ID3D11RasterizerState* m_pRSSolid;
	ID3D11RasterizerState* m_pRSWireFrame;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT SetRasterizerState(D3D11_FILL_MODE fill = D3D11_FILL_SOLID);

public:
	bool gameInit() override;
	bool gameRun() override;
	bool gameFrame() override;
	bool gamePreRender() override;
	bool gameRender() override;
	bool gamePostRender() override;
	bool gameRelease() override;

	bool ResetRT() override;

public:
	Sample(LPCTSTR LWndName);
	virtual ~Sample();
};