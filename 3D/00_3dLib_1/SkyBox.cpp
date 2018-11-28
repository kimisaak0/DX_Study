//#include "SkyBox.h"
//
//SkyBox::SkyBox(){ }
//
//bool SkyBox::LoadTexture(T_STR szName)
//{
//	const TCHAR* g_szSkyTextures[] = {
//		L"../../INPUT/DATA/image/skybox_front.jpg",
//		L"../../INPUT/DATA/image/skybox_bottom.jpg",
//		L"../../INPUT/DATA/image/skybox_left.jpg",
//		L"../../INPUT/DATA/image/skybox_back.jpg",
//		L"../../INPUT/DATA/image/skybox_right.jpg",
//		L"../../INPUT/DATA/image/skybox_front.jpg",
//	};
//
//	int iNumTexture = sizeof(g_szSkyTextures) / sizeof(g_szSkyTextures[0]);
//
//	for (int iTex = 0; iTex < iNumTexture; iTex++) {
//		m_pTexSRV[iTex].Attach(D3D::CreateSRV(g_szSkyTextures[iTex]));
//		if (m_pTexSRV[iTex] == nullptr) {
//			return false;
//		}
//	}
//
//	return true;
//}
//
//bool  SkyBox::Create(T_STR szShaderName, T_STR szTextureName, float scale)
//{
//	D3DXMatrixScaling(&m_matWorld, scale, scale, scale);
//
//}
//bool  SkyBox::Render();
//bool  SkyBox::Release();
//
//
//
//SkyBox::~SkyBox(){ }
