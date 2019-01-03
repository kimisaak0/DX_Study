#include "Texture.h"

namespace Lypi
{
	Texture::Texture()
	{
		m_pTexture = nullptr;
	}

	ID3D11Texture2D* Texture::LoadTexture(LPCWSTR filename)
	{
		HRESULT hr;

		ID3D11Texture2D* texture = nullptr;
		ID3D11Resource* pRes = nullptr;

		//����ü�ο� ������ ������ ũ��� ����۸� �����.
		hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//����� ������ �����´�.
		m_pBackBuffer->GetDesc(&m_BackBuffereDesc);

		//CopyResource()�Լ��� ����� ��� �ݵ�� �� ������ ũ�⺸�� ũ�ų� ���ƾ� �Ѵ�.
		//CopyResourceRegion()�Լ��� ����� ��� ���ϴ� ũ��� ������ �� �ִ�.
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.Width = 300;                       // �ؽ����� �ʺ�. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Height = 400;                       // �ؽ����� ����. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Depth = D3DX11_DEFAULT;            // �ؽ����� ����. ���� �ؽ�ó���� ����ȴ�.
		loadInfo.FirstMipLevel = 0;                         // �ؽ��� �ְ� �ػ� �Ӹ� ����.
		loadInfo.MipLevels = 1;                         // �ؽ��� �Ӹ��� �ִ� ��. (�ּ� 1�̾�� �Ѵ�.)
		loadInfo.Usage = D3D11_USAGE_DEFAULT;       // �ؽ��� ���ҽ��� �뵵
		loadInfo.BindFlags = 0;                         // �ؽ��ĸ� ���ε��� ���������� �ܰ�.
		loadInfo.CpuAccessFlags = 0;                         // CPU�� �ؽ��Ŀ� ������ �� �ִ� ���� ����. 0�̸� ���� �Ұ�.
		loadInfo.MiscFlags = 0;                         // ���ҽ��� ���� ��Ÿ �Ӽ���.
		loadInfo.Format = m_BackBuffereDesc.Format;  // �ؽ��İ� �ε�� ���� ����
		loadInfo.Filter = D3DX11_FILTER_LINEAR;      // ������ ���͸� ����Ͽ� �ؽ��� ���͸�.
		loadInfo.MipFilter = D3DX11_FILTER_NONE;        // ������ ���͸� ����Ͽ� ������ �Ӹ��� ���͸�.
		loadInfo.pSrcInfo = 0;                         // ���� �̹����� ���� ����.


		hr = D3DX11CreateTextureFromFile(g_pD3dDevice, filename, &loadInfo, nullptr, &pRes, nullptr);
		if (FAILED(hr)) {
			DEBUGMSG(L"�̹��� �ҷ����� ����");
			return nullptr;
		}

		pRes->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&m_pTexture);
		pRes->Release();

		return texture;
	}

	bool Texture::Init()
	{
		m_pTexture->GetDesc(&m_TextureDesc);

		return true;
	}

	bool Texture::Frame()
	{
		int iCenterX = m_BackBuffereDesc.Width / 2 - m_TextureDesc.Width / 2;
		int iCenterY = m_BackBuffereDesc.Height / 2 - m_TextureDesc.Height / 2;
		m_iPosX = (int)(cosf(timeGetTime() / 1000.0f) * iCenterX + iCenterX);
		m_iPosY = (int)(sinf(timeGetTime() / 1000.0f) * iCenterY + iCenterY);
		return true;
	}

	bool Texture::Render()
	{
		//2���� �ؽ������� ��ġ�� 3�������� ǥ���Ѵ�.
		//���� �ؽ����� ��ü ���� �� �Ϻ� ���� ����.
		D3D11_BOX sourceRegion;
		sourceRegion.left = 0;
		sourceRegion.right = m_TextureDesc.Width;
		sourceRegion.top = 0;
		sourceRegion.bottom = m_TextureDesc.Height;
		sourceRegion.front = 0;
		sourceRegion.back = 1;

		//CopyResourceRegion()�Լ� : �����ؽ����� ��ü �� �Ϻ� ������ �� ������ 0,0 ��ġ�� ������.
		g_pD3dContext->CopySubresourceRegion(m_pBackBuffer.Get(), 0, m_iPosX, m_iPosY, 0, m_pTexture.Get(), 0, &sourceRegion);
		return true;
	}


	bool Texture::Release()
	{
		return true;
	}

	Texture::~Texture(void)
	{
	}
}

