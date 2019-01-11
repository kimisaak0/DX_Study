#pragma once
#include "ShapeHeader.h"

namespace Lypi
{
	//class Object
	//{
	//	ID3D11InputLayout*          m_pInputLayout;     //ÀÎÇ² ·¹ÀÌ¾Æ¿ô
	//	ID3D11Buffer*               m_pVertexBuffer;    //Á¤Á¡ ¹öÆÛ
	//	ID3D11VertexShader*         m_pVS;              //Á¤Á¡ ½¦ÀÌ´õ
	//	ID3D11PixelShader*          m_pPS;              //ÇÈ¼¿ ½¦ÀÌ´õ
	//	ID3D11ShaderResourceView*   m_pTextureSRV;      //ÅØ½ºÃÄ SRV

	//	ID3D11RasterizerState*      m_pRaster;
	//	ID3D11BlendState*           m_pBlend;
	//	ID3D11SamplerState*         m_pSampler;

	//protected:
	//	uint3 m_center;
	//	int m_HarpWidth, m_HarpHeight;

	//	iLTRB m_iSRegion;
	//	fLTRB m_fPRegion;

	//	PCT_VERTEX m_pVertexList[4];
	//	

	//public:
	//	void    VertexSetting(uint3 center, uWH size);
	//	HRESULT Create(const TCHAR* pTexFile, uint3 center, uWH size);

	//public:
	//	virtual bool Init(const TCHAR* pTexFile, uint3 center, uWH size);
	//	virtual bool Frame();
	//	virtual bool Render();
	//	virtual bool Release();

	//public:
	//	Object();
	//	virtual ~Object();

	//};

	class Object_DX
	{
	protected:
		ID3D11Buffer * m_pVertexBuffer;   // Á¤Á¡ ¹öÆÛ
		ID3D11VertexShader*         m_pVS;             // Á¤Á¡ ½¦ÀÌ´õ
		ID3D11PixelShader*          m_pPS;             // ÇÈ¼¿ ½¦ÀÌ´õ
		ID3D11InputLayout*          m_pInputLayout;    // ÀÎÇ² ·¹ÀÌ¾Æ¿ô
		ID3D11ShaderResourceView*   m_pTextureSRV;     // ÅØ½ºÃÄ SRV
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
		void transStoP(); //È­¸é -> Åõ¿µ
		void transPtoS(); //Åõ¿µ -> È­¸é
		void UpdateCP(); //ÁßÁ¡ °»½Å
		void UpdateVertexList(); //Á¤Á¡ ¸®½ºÆ® °»½Å

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