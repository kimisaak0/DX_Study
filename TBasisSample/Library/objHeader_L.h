#pragma once
#include "DxObj.h"

namespace Lypi
{
#pragma region TextureType
// Sub texture types
#define ST_AM 0   // ambient
#define ST_DI 1   // diffuse
#define ST_SP 2   // specular
#define ST_SH 3   // shininesNs
#define ST_SS 4   // shininess strength
#define ST_SI 5   // self-illumination
#define ST_OP 6   // opacity
#define ST_FI 7   // filter color
#define ST_BU 8   // bump 
#define ST_RL 9   // reflection
#define ST_RR 10  // refraction 
#define ST_DP 11  // displacement
#define ST_GN 12  // Generic
#define ST_EV 13  // EnvMap
#pragma endregion
	
#pragma region Enum
	const enum OBJECTCLASSTYPE {
		CLASS_GEOM = 0,
		CLASS_BONE,
		CLASS_DUMMY,
		CLASS_BIPED,
	};

	const enum FILETYPE {
		NULLFILE = 0,
		ASEFILE,
		TBSFILE,
		SKMFILE,
		MATFILE,
	};
#pragma endregion

#pragma region struct
	struct VersionMark
	{
		int		iVersion;
		TCHAR	description[128];
	};

	struct VS_CONSTANT_BUFFER
	{
		stdMatrix matWorld; // c0						
		stdMatrix matView;	// c4						
		stdMatrix matProj;	// c8						
		Vector4   Color;    // 12
	};
	
	struct Point3
	{
		double x, y, z;
	};
#pragma endregion

#pragma region Vertex
	struct PC_VERTEX
	{
		Vector3 p;
		Vector4 c;

		PC_VERTEX() {}
		PC_VERTEX(Vector3 vp, Vector4 vc)
		{
			p = vp, c = vc;
		}
	};

	struct PCT_VERTEX
	{
		Vector3 p;
		Vector4 c;
		Vector2 t;

		PCT_VERTEX() {}
		PCT_VERTEX(Vector3 vp, Vector4 vc, Vector2 vt)
		{
			p = vp, c = vc, t = vt;
		}
	};

	struct PCT2_VERTEX
	{
		Vector3 p;
		Vector4 c;
		Vector2 t0;
		Vector2 t1;

		PCT2_VERTEX() {}
		PCT2_VERTEX(Vector3	vp,	Vector4 vc, Vector2 vt0, Vector2 vt1)
		{
			p = vp, c = vc, t0 = vt0, t1 = vt1;
		}
	};

	struct PNC_VERTEX
	{
		Vector3 p;
		Vector3 n;
		Vector4 c;

		PNC_VERTEX() {}
		PNC_VERTEX(Vector3 vp, Vector3 vn, Vector4 vc)
		{
			p = vp, n = vn, c = vc;
		}
	};

	struct PNCT_VERTEX
	{
		Vector3		p;
		Vector3		n;
		Vector4		c;
		Vector2     t;

		PNCT_VERTEX() {}
		PNCT_VERTEX(Vector3	vp, Vector3 vn, Vector4 vc,	Vector2 vt)
		{
			p = vp, n = vn, c = vc, t = vt;
		}
	};

	struct PNCT2_VERTEX
	{
		Vector3		p;
		Vector3		n;
		Vector4		c;
		Vector2     t;
		Vector3		vTangent;

		PNCT2_VERTEX() {}
		PNCT2_VERTEX(Vector3 vp, Vector3 vn, Vector4 vc, Vector2 vt, Vector3 tangent)
		{
			p = vp, n = vn, c = vc, t = vt, vTangent = tangent;
		}
	};

	// ─────────────────────────────────
	//  쉐이더 사용시( 가중치 4개 제한 사용 )
	// ─────────────────────────────────
	struct PNCT3_VERTEX
	{
		Vector3		p;
		Vector3		n;
		Vector4		c;
		Vector2		t;
		Vector4		i;	// I0, I1, I2, I3
		Vector4		w;// W0, fW1, fW2, fNumWeight;

		PNCT3_VERTEX() {
			w.x = w.y = w.z = w.w = 0.0f;
			i.x = i.y = i.z = i.w = 0.0f;
		}
		PNCT3_VERTEX(Vector3 vp, Vector3 vn, Vector4 vc, Vector2 vt, Vector4 vw, Vector4 vi)
		{
			p = vp, n = vn, c = vc, t = vt;
			w = vw, i = vi;
		}
	};

	// ─────────────────────────────────
	//  쉐이더 사용시( 가중치 8개 제한 사용 )
	// ─────────────────────────────────
	struct PNCT5_VERTEX
	{
		Vector3		p;
		Vector3		n;
		Vector4		c;
		Vector2		t;
		Vector4		w0;// W0, fW1, fW2, fW3;
		Vector4		i0;	// I0, I1, I2, I3
		Vector4		w1;// W4, fW5, fW6, fNumWeight;	
		Vector4		i1;	// I4, I5, I6, I7

		PNCT5_VERTEX() {
			w0.x = w0.y = w0.z = w0.w = 0.0f;
			i0.x = i0.y = i0.z = i0.w = 0.0f;
			w1.x = w1.y = w1.z = w1.w = 0.0f;
			i1.x = i1.y = i1.z = i1.w = 0.0f;
		}
		PNCT5_VERTEX(Vector3 vp, Vector3 vn, Vector4 vc, Vector2 vt, Vector4 vw0, Vector4 vi0, Vector4 vw1, Vector4 vi1)
		{
			p = vp, n = vn, c = vc, t = vt;
			w0 = vw0, i0 = vi0, w1 = vw1, i1 = vi1;
		}
	};

#pragma endregion

#pragma region shape
	struct T_PLANE
	{
		float4	fV;
		bool	CreatePlane(Vector3 v0, Vector3 v1, Vector3 v2);
		bool	CreatePlane(Vector3 vNormal, Vector3 v0);
		void	Normalize()
		{
			float fMag = sqrt(fV.x*fV.x + fV.y*fV.y + fV.z*fV.z + fV.w*fV.w);
			fV.x = fV.x / fMag;
			fV.y = fV.y / fMag;
			fV.z = fV.z / fMag;
			fV.w = fV.w / fMag;
		}
	};

	struct T_SPHERE
	{
		Vector3		vCenter;
		float		fRadius;
	};

	struct T_BOX
	{
		// Common
		D3DXVECTOR3		vCenter;
		D3DXVECTOR3		vPos[8];
		// AABB
		D3DXVECTOR3		vMax;
		D3DXVECTOR3		vMin;
		// OBB
		D3DXVECTOR3		vAxis[3];
		float			fExtent[3];
	};

#pragma endregion

#pragma region List
	struct TFaceList
	{
		union
		{
			struct { DWORD	_0, _1, _2; };
			DWORD v[3];
		};
		DWORD   dwMtrl;
		TFaceList() : dwMtrl(0), _0(0), _1(0), _2(0)
		{}
	};

	struct TVertexList
	{
		DWORD					dwNumVertex;
		DWORD					dwNumFace;
		vector<D3DXVECTOR3>		pVertexList;
		vector<TFaceList>		pFaceList;
		vector<DWORD>			pSubListMtl;
		TVertexList() : dwNumVertex(0), dwNumFace(0)
		{
		}
		~TVertexList() { stl_wipe_vector(pVertexList); stl_wipe_vector(pVertexList); }
	};

#pragma endregion


	struct TScene
	{
		int iVersion;		// 버전
		int	iFirstFrame;    // 시작 프레임
		int	iLastFrame;     // 마지막 프레임
		int	iFrameSpeed;    // 1초당 프레임 개수(30)
		int	iTickPerFrame;  // 1프레임의 틱 값(160)
		int iNumMesh;		// 메쉬오브젝트 개수
		int iMaxWeight;		// 정점 당 가중치
		int iBindPose;		// 바인딩 포즈 에니메이션 여부
	};

	struct TAnimTrack
	{
		int					iTick;
		D3DXQUATERNION		qRotate;
		D3DXVECTOR3			vVector;
		TAnimTrack*			pNext;
		TAnimTrack*			pPrev;
	};

	struct ObjFrame
	{
		vector<D3DXMATRIX>  m_matWorldList;
		int  				m_iIndex;

		ObjFrame(int iNumMesh, int iIndex)
		{
			m_matWorldList.resize(iNumMesh);
			m_iIndex = iIndex;
		}
	};

	struct LTextureMap
	{
		DWORD		m_dwIndex;         // 오브젝트 텍스쳐 관리자에서 매터리얼의 텍스쳐파일명을 보고 DX텍스쳐 생성 후 참조인덱스를 저장한다.
		DWORD		m_dwType;          // 텍스쳐 맵 타입인덱스
	
		T_STR		m_strName;         // 맵 이름
		T_STR		m_strClassName;    // 맵 클래스 이름
		T_STR		m_strTextureName;  // 맵 텍스쳐 이름.

		LTextureMap() : m_dwType(1), m_dwIndex(0) {}
	};

	struct LMaterial
	{
		T_STR		m_strName;       // 메터리얼 이름
		T_STR		m_strClassName;  // 메터리얼 클래스 이름
		
		vector<LTextureMap>	m_TexMaps;	    // 맵타입들
		vector<LMaterial>		m_SubMaterial;  // 서브 매터리얼 저장벡터

		//TBS
		DWORD m_dwSubCount;
		DWORD m_dwTexMapCount;
		DWORD m_dwIndex;

		LMaterial() {}
		~LMaterial()
		{
			stl_wipe_vector(m_SubMaterial);
			stl_wipe_vector(m_TexMaps);
		}
	};

	struct TBipedMesh
	{
		T_STR		        m_strName;
		int					m_iNumFace;
		D3DXMATRIX			m_matWorld;
		vector<PNC_VERTEX>	m_VertexList;
		PNC_VERTEX*		    m_pDrawVertex;
	};


	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------

	struct PositionKey
	{
		double t;   /* sample time */
		Point3 P; 	/* sample position */
		double tension, continuity, bias; /* sample parameters for affecting tangential behavior at control point */
	};

	/* private structures to hide details of polynomials */
	struct CubicPolynomial
	{
		Point3 C0, C1, C2, C3; /* P(u) = C0 + u*C1 + u^2*C2 + u^3*C3,  0 <= u <= 1 */
		double tmin, tmax, trange; 	/* sample time interval on which polynomial is valid, tmin <= t <= tmax */
	};

	struct SplineInfo
	{
		int numPolys;
		CubicPolynomial* poly;

		/* partial sums of arc length */
		double* length;
		double totalLength;
	};
}
