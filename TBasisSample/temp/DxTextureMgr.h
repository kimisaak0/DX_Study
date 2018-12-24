#pragma once
#include "DxDevice.h"

namespace Lypi
{
	class DxTexture
	{
		friend class DxTextureMgr;
		friend class TemplateMap<DxTexture>;

	protected:
		T_STR    m_szName;
		T_STR    m_szPath;

		ID3D11ShaderResourceView*    m_pTextureRV;
		ID3D11SamplerState*          m_pSamplerState;
		D3D11_SAMPLER_DESC           m_SamplerDesc;

	public:
		void    SetPath(const TCHAR* pTexPath);
		HRESULT Load(const TCHAR* pTexName);
		bool    Apply();
		bool    Release();

	public:
		DxTexture();
		DxTexture(const TCHAR* pTexPath);
		virtual ~DxTexture();
	};

	class DxTextureMgr : public TemplateMap<DxTexture>
	{
	public:
		int Add(const TCHAR* szPath, const TCHAR* pFileName);

	public:
		static DxTextureMgr& GetInstance();

	protected:
		DxTextureMgr();
		virtual ~DxTextureMgr();
	};

#define I_DxTextureMgr DxTextureMgr::GetInstance()
}