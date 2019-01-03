#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
	class Texture
	{
		//���� �ؽ��ĸ� ǥ���� �� ����� ���ҽ�
		ComPtr<ID3D11Texture2D> m_pTexture;
		D3D11_TEXTURE2D_DESC m_TextureDesc;

		//����ۿ� ���ҽ�
		ComPtr<ID3D11Texture2D> m_pBackBuffer;
		D3D11_TEXTURE2D_DESC m_BackBuffereDesc;

		//�̹��� ��ġ ������
		int m_iPosX, m_iPosY;

	public:
		ID3D11Texture2D * LoadTexture(LPCWSTR filename);

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Texture();
		virtual ~Texture();
	};
}
