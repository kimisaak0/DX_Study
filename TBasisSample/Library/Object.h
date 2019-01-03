#pragma once
#include "simpleShape.h"

namespace Lypi
{
	class Object : simpleShape
	{
	protected:
		ComPtr<ID3D11ShaderResourceView>   m_pTextureSRV;     // �ؽ��� SRV
		ComPtr<ID3D11BlendState>           m_pAlphaBlend;
		ComPtr<ID3D11SamplerState>         m_pSamplerState;

	protected:
		PCT_VERTEX m_pVertexList[4];

		uWH   m_uImageSize;
		iLTRB m_uImagePart;

		fLTRB m_fPRegion;

		POINT m_ptCenter;
		D3DXVECTOR3 m_v3Center;

	public:
		iLTRB m_uSRegion;

		bool m_bExist;

	private:
		void transStoP(); //ȭ�� -> ����
		void transPtoS(); //���� -> ȭ��
		void UpdateCP(); //���� ����
		void UpdateVertexList(); //���� ����Ʈ ����

		void ImagePartialSelect(iXYWH imgXYWH, uWH imgSize);
		HRESULT Create(const TCHAR* pTexFile);

	public:

		void SetPosition(iXYWH _xywh);

		void CreateFullImgObj(iXYWH _xywh, const TCHAR* pTexFile);
		void CreatePartImgObj(iXYWH _xywh, iXYWH imgXYWH, uWH imgSize, const TCHAR* pTexFile);

		void ImagePartialChange(iXYWH _xywh);

		void ImageFileChange(const TCHAR* pTexFile);

		void MoveX(float fDis);
		void MoveY(float fDis);

		iLTRB getPos();

		void spin(float fAngle);
		void scale(float size);

		void ColorChange(float r, float g, float b, float a);

	public:
		virtual bool Init();
		virtual bool Frame();
		virtual bool Render();
		virtual bool Release();

	public:
		Object();
		virtual ~Object();

	};
}