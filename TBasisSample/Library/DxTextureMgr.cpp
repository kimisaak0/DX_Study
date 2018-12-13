#include "DxTextureMgr.h"

namespace Lypi
{
#pragma region //DxTexture

	DxTexture::DxTexture()
	{
		m_pTextureRV = nullptr;
		m_pSamplerState = nullptr;
		m_szPath = _T("");
	}

	DxTexture::DxTexture(const TCHAR* pTexPath)
	{
		m_pTextureRV = nullptr;
		m_pSamplerState = nullptr;
		m_szPath = pTexPath;
	}

	void    DxTexture::SetPath(const TCHAR* pTexPath)
	{
		m_szPath = pTexPath;
	}

	HRESULT DxTexture::Load(const TCHAR* pTexName)
	{
		HRESULT hr = S_OK;

		if (pTexName == nullptr) {
			return hr;
		}

		TCHAR TexFullPath[MAX_PATH] = { 0, };
		_stprintf_s(TexFullPath, _T("%s%s"), m_szPath.c_str(), pTexName);
		m_szName = pTexName;

		D3DX11_IMAGE_LOAD_INFO loadInfo;
		ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		loadInfo.Format = DXGI_FORMAT_FROM_FILE;

		hr = D3DX11CreateShaderResourceViewFromFile(g_pD3dDevice, TexFullPath, &loadInfo, nullptr, &m_pTextureRV, nullptr);
		V_FRETURN(hr);

		return hr;
	}

	bool    DxTexture::Apply()
	{
		assert(g_pD3dContext);

		if (!m_pTextureRV) {
			return false;
		}

		g_pD3dContext->PSSetShaderResources(0, 1, &m_pTextureRV);
		//g_pD3dContext->PSSetSamplers(0, 1, &m_pSamplerState);
		return true;
	}

	bool    DxTexture::Release()
	{
		m_pTextureRV = nullptr;
		m_pSamplerState = nullptr;
	}

	DxTexture::~DxTexture()
	{
	}

#pragma endregion

#pragma region //DxTextureMgr

	
	DxTextureMgr& DxTextureMgr::GetInstance()
	{
		static DxTextureMgr inst;
		return inst;
	}

	DxTextureMgr::DxTextureMgr()
	{
	}

	int DxTextureMgr::Add(const TCHAR* szPath, const TCHAR* pFileName)
	{
		TCHAR szFileName[MAX_PATH] = { 0, };

		TCHAR Drive[MAX_PATH];
		TCHAR Dir[MAX_PATH];
		TCHAR FileName[MAX_PATH];
		TCHAR Ext[MAX_PATH];

		if (pFileName) {
			_tsplitpath(pFileName, Drive, Dir, FileName, Ext);
			Ext[4] = 0;
			
			_stprintf_s(szFileName, _T("%s%s"), FileName, Ext);

			for (TMapIter iter = TM.begin(); iter != TM.end(); iter++) {
				DxTexture* pPoint = (*iter).second;
				if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName)) {
					return (*iter).first;
				}
			}
		}

		DxTexture* pPoint = nullptr;
		pPoint = new DxTexture;
		pPoint->SetPath(szPath);

		if (FAILED(pPoint->Load(szFileName))) {
			return 0;
		}

		TM.insert(make_pair(++m_iCurIndex, pPoint));

		return m_iCurIndex;
	}

	DxTextureMgr::~DxTextureMgr()
	{
	}
#pragma endregion
}