#pragma once
#include "Obj3d_DX.h"

struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;

	PC_VERTEX() {}

	PC_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR4 vc)
	{
		p = vp;
		c = vc;
	}

	bool operator==  (const PC_VERTEX& Vertex)
	{
		if (p == Vertex.p && c == Vertex.c) {
			return true;
		}
		else {
			return false;
		}
	}
};

struct PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	PT_VERTEX() {}

	PT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR2 vt)
	{
		p = vp;
		t = vt;
	}

	bool operator==  (const PT_VERTEX& Vertex)
	{
		if (p == Vertex.p && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}
};


struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;

	PCT_VERTEX() {}

	PCT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR4 vc, D3DXVECTOR2 vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}

	bool operator==  (const PCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && c == Vertex.c && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}
};

struct PNCT_VERTEX
{
	D3DXVECTOR3 p;  // Position (위치)
	D3DXVECTOR3 n;  // Normal (표준...?)
	D3DXVECTOR4 c;  // Corlor (색상)
	D3DXVECTOR2 t;  // Texcoord (텍스쳐 좌표)

	PNCT_VERTEX() {}

	PNCT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR3 vn, D3DXVECTOR4 vc, D3DXVECTOR2 vt)
	{
		p = vp;
		n = vn;
		c = vc;
		t = vt;
	}

	bool operator==  (const PNCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && n == Vertex.n && c == Vertex.c && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}
};

//좌표 변환용 상수버퍼 데이터
struct T_CB_DATA
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;

	float fTime;
	float fActiveVP;
	float z, w;

	D3DXVECTOR4 vColor;
};