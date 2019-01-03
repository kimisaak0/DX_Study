#pragma once
#include "mathHeader_L.h"

namespace Lypi
{
	class Texture1
	{
		//실제 텍스쳐를 표시할 때 사용할 리소스
		ComPtr<ID3D11Texture2D> m_pTexture;
		D3D11_TEXTURE2D_DESC m_TextureDesc;

		//백버퍼용 리소스
		ComPtr<ID3D11Texture2D> m_pBackBuffer;
		D3D11_TEXTURE2D_DESC m_BackBuffereDesc;

		//이미지 위치 지정용
		int m_iPosX, m_iPosY;

	public:
		ID3D11Texture2D * LoadTexture(LPCWSTR filename);

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Texture1();
		virtual ~Texture1();
	};
}
