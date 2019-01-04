#pragma once
#include "stdHeader_L.h"
#include "mathHeader_L.h"

namespace Lypi
{
	struct P_VERTEX
	{
		float3 position;
	};

	struct PC_VERTEX
	{
		float3 position;
		float4 color;
	};

	struct PT_VERTEX
	{
		float3 position;
		float2 texel;
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
		UINT Height;
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
}