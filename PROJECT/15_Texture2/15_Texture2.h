#pragma once
#include "00_header.h"

class Texture2
{
public:
	ID3D11ShaderResourceView* m_pTextureSRV;

public:
	HRESULT Load(ID3D11Device* pDevice, TCHAR* strFilePath);
	bool Apply(ID3D11DeviceContext* pImmediateContext);

public:
	Texture2();
	~Texture2();
};