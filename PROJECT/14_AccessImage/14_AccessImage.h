#pragma once
#include "00_Header.h"

class AccessImage : public coreC_DX
{
public:
	ID3D11Texture2D*      m_pTextureSrc;
	ID3D11Texture2D*      m_pTextureDest;
	D3D11_TEXTURE2D_DESC  m_descDesert;
	ID3D11Texture2D*      m_pBackBuffer;
	D3D11_BOX             m_SrcRegion;
	D3D11_TEXTURE2D_DESC  m_descBackBuffer;

public:
	bool Init();
	bool Render();
	bool Release();

public:
	ID3D11Texture2D* GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo = nullptr);
	ID3D11Texture2D* CopyTexture(ID3D11Texture2D* pSrcTexture);
	void             WriteDotPixel(ID3D11Texture2D* pTexDest);

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
	AccessImage(LPCTSTR LWndName);
	virtual ~AccessImage();
};