#include "mathHeader_L.h"

namespace Lypi
{
	float2::float2()
	{
		x = 0.f; y = 0.f;
	}

	float2::float2(float _x, float _y) 
	{
		x = _x; y = _y;
	}


	float3::float3()
	{
		x = 0.f; y = 0.f; z = 0.f;
	}

	float3::float3(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}


	float4::float4()
	{
		x = 0.f; y = 0.f; z = 0.f; w = 0.f;
	}

	float4::float4(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}


	float2x2::float2x2()
	{
		for (int i = 0; i < 2; i++) {
			for (int k = 0; k < 2; k++) {
				m[i][k] = 0;
			}
		}
	}

	float2x2::float2x2(float2 __0, float2 __1)
	{
		for (int i = 0; i < 2; i++) {
			m[0][i] = __0.f[i];
			m[1][i] = __1.f[i];
		}
	}


	float3x3::float3x3()
	{
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				m[i][k] = 0;
			}
		}
	}

	float3x3::float3x3(float3 __0, float3 __1, float3 __2)
	{
		for (int i = 0; i < 3; i++) {
			m[0][i] = __0.f[i];
			m[1][i] = __1.f[i];
			m[2][i] = __2.f[i];
		}
	}

	float4x4::float4x4()
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] = 0;
			}
		}
	}

	float4x4::float4x4(float4 __0, float4 __1, float4 __2, float4 __3)
	{
		for (int i = 0; i < 4; i++) {
			m[0][i] = __0.f[i];
			m[1][i] = __1.f[i];
			m[2][i] = __2.f[i];
			m[3][i] = __3.f[i];
		}
	}


	bool stdMatrix::operator== (const stdMatrix& V) const
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (abs(m[i][k] - m[i][k]) > L_Epsilon) {
					return false;
				}
			}
		}

		return true;
	}

	bool stdMatrix::operator!= (const stdMatrix& V) const
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (abs(m[i][k] - m[i][k]) > L_Epsilon) {
					return true;
				}
			}
		}

		return false;
	}

	stdMatrix stdMatrix::operator+= (const stdMatrix& V)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] += V.m[i][k];
			}
		}
		stdMatrix rm(*this);
		return rm;
	}

	stdMatrix stdMatrix::operator-= (const stdMatrix& V)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] -= V.m[i][k];
			}
		}
		stdMatrix rm(*this);
		return rm;
	}

	stdMatrix stdMatrix::Transpose()
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] = m[k][i];
			}
		}
	}

	void stdMatrix::Transpose(stdMatrix& result)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][k] = m[k][i];
			}
		}
	}

	stdMatrix stdMatrix::Inverse()
	{

	}

	void stdMatrix::Inverse(stdMatrix& result)
	{

	}

}