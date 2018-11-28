#pragma once
#include "00_Header.h"

class TextureSample : public coreC_DX
{
protected:
	ID3D11Texture2D*        m_pTextureDesert;
	D3D11_TEXTURE2D_DESC    m_descDesert;
	ID3D11Texture2D*        m_pTextureKoala;
	D3D11_TEXTURE2D_DESC    m_descKoala;
	
	ID3D11Texture2D*        m_pBackBuffer;
	D3D11_TEXTURE2D_DESC    m_descBackBuffer;

	int                     m_iPosX;
	int                     m_iPosY;

public:
	void             ErrorMessageBox(bool bPrint = true);
	ID3D11Texture2D* GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo = nullptr);

public:
	bool Init()    override;
	bool Frame()   override;
	bool Render()  override;
	bool Release() override;

	//core²¨ ÀÓ½Ã·Î ¸· °¡Á®¿È
public:
	bool gameInit()        override;
	bool gameRun()         override;
	bool gameFrame()       override;
	bool gamePreRender()   override;
	bool gameRender()      override;
	bool gamePostRender()  override;
	bool gameRelease()     override;

public:
	TextureSample(LPCTSTR LWndName);
	virtual ~TextureSample();
};