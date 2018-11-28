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
	int iVersion;      // ����
	int iFirstFrame;   // ���� ������
	int iLastFrame;    // ������ ������
	int iFrameSpeed;   // 1�ʴ� ������ ����(30)
	int iTickPerFrame; // 1�������� ƽ ��(160)
	int iNumMesh;      // �޽�������Ʈ ����
	int iMaxWeight;    // ���� �� ����ġ
	int iBindPose;     // ���ε� ���� �ִϸ��̼� ����
};

struct VesionMark 
{
	int iVersion;
	TCHAR description[128];
};

struct TextureMap
{
	DWORD m_dwIndex;        // ������Ʈ �ؽ��� �����ڿ��� ���׸����� �ؽ������ϸ��� ���� DX�ؽ��� ���� �� ���� �ε����� �����Ѵ�. 
	DWORD m_dwType;         // �ؽ��� �� Ÿ�� �ε���
	T_STR m_strName;        // �� �̸�
	T_STR m_strClassName;   // �� Ŭ���� �̸�
	T_STR m_strTextureName; // �� �ؽ��� �̸�

	TextureMap() : m_dwIndex(0), m_dwType(1) {}
};

struct Mtrl
{
	T_STR m_strName;        // ���׸��� �̸�
	T_STR m_strClassName;   // ���͸��� Ŭ���� �̸�

	vector<TextureMap>  m_vtTMTypes;       // �ؽ��ĸ� Ÿ�Ե�
	vector<Mtrl>        m_vtSubMaterial;   // ���� ���׸��� ���庤��

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
