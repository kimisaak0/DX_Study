#pragma once
#include "stdHeader_L.h"
#include "mathHeader_L.h"

namespace Lypi
{
	struct uint3
	{
		UINT x, y, z;
	};

	struct fLTRB
	{
		float left;
		float top;
		float right;
		float bottom;
	};
	struct iXYWH
	{
		LONG ltx;
		LONG lty;
		UINT width;
		UINT height;
	};

	struct iLTRB
	{
		LONG left;
		LONG top;
		LONG right;
		LONG bottom;

		iLTRB& operator= (const iXYWH& _xywh) {
			left = _xywh.ltx;
			top = _xywh.lty;
			right = _xywh.ltx + _xywh.width;
			bottom = _xywh.lty + _xywh.height;

			return *this;
		}
	};


	struct P_VERTEX
	{
		D3DXVECTOR3 position;
	};

	struct PC_VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	struct PT_VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texel;
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

	struct uWH
	{
		UINT width;
		UINT height;
	};

	struct uPOINT
	{
		UINT x;
		UINT y;

		uPOINT& operator= (const POINT& pt) {
			x = pt.x;
			y = pt.y;

			return *this;
		}
	};


}