#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"
#include "mathHeader_L.h"

namespace Lypi
{
	class Sample : public zCore
	{
		//실제 텍스쳐를 표시할 때 사용할 리소스
		ComPtr<ID3D11Texture2D> m_pTextureSrc;
		ComPtr<ID3D11Texture2D> m_pTextureDest;
		D3D11_TEXTURE2D_DESC m_TextureDesc;

		//백버퍼용 리소스
		ComPtr<ID3D11Texture2D> m_pBackBuffer;
		D3D11_TEXTURE2D_DESC m_BackBuffereDesc;

		D3D11_BOX  m_SourceRegion;

	public:
		ID3D11Texture2D* GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo = nullptr);
		ID3D11Texture2D* CopyTexture(ID3D11Texture2D* pSrcTexture);
		void             WriteDotPixel(ID3D11Texture2D* pTexDest);

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Sample(LPCTSTR LWndName);
		virtual ~Sample();
	};
}
