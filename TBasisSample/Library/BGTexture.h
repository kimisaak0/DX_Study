#pragma once

#include "mathHeader_L.h"

namespace Lypi
{
	class BGTexture
	{
		//실제 텍스쳐를 표시할 때 사용할 리소스
		ComPtr<ID3D11Texture2D> m_pTexture;
		D3D11_TEXTURE2D_DESC m_TextureDesc;

		//백버퍼용 리소스
		ComPtr<ID3D11Texture2D> m_pBackBuffer;
		D3D11_TEXTURE2D_DESC m_BackBuffereDesc;

	public:
		ID3D11Texture2D* LoadTexture(LPCWSTR filename);

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		BGTexture();
		virtual ~BGTexture();
	};
}

