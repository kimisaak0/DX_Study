#pragma once
#include "Shapes_DX.h"

class SkyBox : public Box_Shape
{
	ComPtr<ID3D11ShaderResourceView>  m_pTexSRV[6];

public:
	HRESULT LoadTexture(T_STR szName);

	HRESULT LoadVertexShader(T_STR szName);
	HRESULT LoadPixelShader(T_STR szName);

	bool Create(T_STR szVSName, T_STR szPSName, T_STR szGSName, T_STR szTextureName, float scale);
	bool Render();
	bool Release();

public:
	SkyBox();
	virtual ~SkyBox();
};
