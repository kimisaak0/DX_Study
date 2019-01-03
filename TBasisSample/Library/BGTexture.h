#pragma once

#include "mathHeader_L.h"

namespace Lypi
{
	class BGTexture
	{
		//���� �ؽ��ĸ� ǥ���� �� ����� ���ҽ�
		ComPtr<ID3D11Texture2D> m_pTexture;
		D3D11_TEXTURE2D_DESC m_TextureDesc;

		//����ۿ� ���ҽ�
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

