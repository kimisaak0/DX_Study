#pragma once
#include "ShapeHeader.h"

namespace Lypi
{

	class Object_DX
	{
	protected:
		ID3D11Buffer*               m_pVertexBuffer;   // 정점 버퍼
		ID3D11VertexShader*         m_pVS;             // 정점 쉐이더
		ID3D11PixelShader*          m_pPS;             // 픽셀 쉐이더
		ID3D11InputLayout*          m_pInputLayout;    // 인풋 레이아웃
		ID3D11ShaderResourceView*   m_pTextureSRV;     // 텍스쳐 SRV
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
		void transStoP(); //화면 -> 투영
		void transPtoS(); //투영 -> 화면
		void UpdateCP(); //중점 갱신
		void UpdateVertexList(); //정점 리스트 갱신

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