#pragma once
#include "00b_Template.h"

// enum
const enum OBJECTCLASSTYPE 
{
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};

const enum FILETYPE 
{
	NULLFILE = 0,
	ASEFILE,
	TBSFILE,
	SKMFILE,
	MATFILE,
};


// struct 1 ----
struct Scene 
{
	int iVersion;      // 버전
	int iFirstFrame;   // 시작 프레임
	int iLastFrame;    // 마지막 프레임
	int iFrameSpeed;   // 1초당 프레임 개수(30)
	int iTickPerFrame; // 1프레임의 틱 값(160)
	int iNumMesh;      // 메쉬오브젝트 개수
	int iMaxWeight;    // 정점 당 가중치
	int iBindPose;     // 바인딩 포즈 애니메이션 여부
};

struct VesionMark 
{
	int iVersion;
	TCHAR description[128];
};

struct TextureMap
{
	DWORD m_dwIndex;        // 오브젝트 텍스쳐 관리자에서 매테리얼의 텍스쳐파일명을 보고 DX텍스쳐 생성 후 참조 인덱스를 저장한다. 
	DWORD m_dwType;         // 텍스쳐 맵 타입 인덱스
	T_STR m_strName;        // 맵 이름
	T_STR m_strClassName;   // 맵 클래스 이름
	T_STR m_strTextureName; // 맵 텍스쳐 이름

	TextureMap() : m_dwIndex(0), m_dwType(1) {}
};

struct Mtrl
{
	T_STR m_strName;        // 매테리얼 이름
	T_STR m_strClassName;   // 매터리얼 클래스 이름

	vector<TextureMap>  m_vtTMTypes;       // 텍스쳐맵 타입들
	vector<Mtrl>        m_vtSubMaterial;   // 서브 매테리얼 저장벡터

	//TBS
	DWORD m_dwSubCount;
	DWORD m_dwTMCount;
	DWORD m_dwIndex;

	Mtrl() {}
	~Mtrl() 
	{
		stl_wipe_vector(m_vtTMTypes);
		stl_wipe_vector(m_vtSubMaterial);
	}
};

struct FaceList
{
	union {
		struct { DWORD _0, _1, _2; };
		DWORD v[3];
	};

	DWORD dwMtrl;
	FaceList() : dwMtrl(0), _0(0), _1(0), _2(0) 
	{}
};

struct VertexList
{
	DWORD                dwNumVertex;
	DWORD                dwNumFace;
	
	vector<D3DXVECTOR3>  vtVertexList;
	vector<FaceList>     vtFaceList;
	vector<DWORD>        vtSubListMtrl;

	VertexList() : dwNumVertex(0), dwNumFace(0) 
	{}

	~VertexList() 
	{ stl_wipe_vector(vtVertexList); stl_wipe_vector(vtVertexList); }
};

struct AnimeTrack
{
	int             iTick;
	D3DXQUATERNION  qRotate;
	D3DXVECTOR3     v3Vector;
	AnimeTrack*     pNext;
	AnimeTrack*     pPrev;
};
// struct 1 ----


//struct 2 ----

//struct 2 ----

//struct 3 ----
struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;

	bool operator==  (const PCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && c == Vertex.c && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}

	PCT_VERTEX() {}
	
	PCT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR4 vc, D3DXVECTOR2 vt)
	{
		p = vp; 
		c = vc; 
		t = vt;
	}

};


//struct 3 ----
