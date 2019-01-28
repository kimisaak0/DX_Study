#pragma once
#include "ShapeHeader.h"

namespace Lypi
{

	class Object_DX
	{
	protected:
		ID3D11Buffer*               m_pVertexBuffer;   // ���� ����
		ID3D11VertexShader*         m_pVS;             // ���� ���̴�
		ID3D11PixelShader*          m_pPS;             // �ȼ� ���̴�
		ID3D11InputLayout*          m_pInputLayout;    // ��ǲ ���̾ƿ�
		ID3D11ShaderResourceView*   m_pTextureSRV;     // �ؽ��� SRV
		ID3D11BlendState*           m_pAlphaBlend;
		ID3D11SamplerState*         m_pSamplerState;

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

		void ImagePartialChange(iXYWH);

		void ImageFileChange(const TCHAR* pTexFile);

		void MoveX(float fDis);
		void MoveY(float fDis);

		iLTRB getPos();

		void spin(float fAngle);
		void spin(float dx, float dy);
		void scale(float size);

		void ColorChange(float r, float g, float b, float a);

	public:
		virtual bool Init();
		virtual bool Frame();
		virtual bool Render();
		virtual bool Release();

	public:
		Object_DX();
		virtual ~Object_DX();

	};

}