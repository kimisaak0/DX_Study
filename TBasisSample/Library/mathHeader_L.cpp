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

	//생성자
	Vector2::Vector2()
		: float2() {}

	Vector2::Vector2(float x)
		: float2(x, x) {}

	Vector2::Vector2(float x, float y)
		: float2(x, y) {}

	Vector2::Vector2(const float2& F)
	{
		x = F.x; 
		y = F.y; 
	}

	Vector2::Vector2(const Vector2& V)
	{
		x = V.x; 
		y = V.y; 
	}

	bool Vector2::operator== (const Vector2& V) const 
	{
		if (x == V.x && y == V.y) {
			return true; 
		} 
		return false; 
	}

	bool Vector2::operator!= (const Vector2& V) const 
	{
		if (x == V.x && y == V.y) {
			return false; 
		} 
		return true; 
	}

	Vector2& Vector2::operator+= (const Vector2& V) 
	{
		Vector2 rv = { x += V.x, y += V.y };
		return rv;
	}

	Vector2& Vector2::operator-= (const Vector2& V) 
	{
		Vector2 rv = { x -= V.x, y -= V.y};
		return rv; 
	}

	Vector2& Vector2::operator*= (float S)
	{
		Vector2 rv = { x *= S, y *= S };
		return rv; 
	}

	Vector2& Vector2::operator/= (float S) 
	{
		Vector2 rv = { x /= S, y /= S };
		return rv; 
	}

	Vector2 Vector2::operator+ () const 
	{
		return *this; 
	}

	Vector2 Vector2::operator- () const 
	{
		return Vector2(-x, -y); 
	}

	float Vector2::Length() const 
	{
		return sqrtf(x*x + y * y); 
	}

	float Vector2::LengthSquared() const 
	{
		return x * x + y * y; 
	}

	float Vector2::Dot(const Vector2& V) const 
	{
		return x * V.x + y * V.y; 
	}

	Vector2 Vector2::Normalize() 
	{
		Vector2 bf = *this; 

		this->x /= Length();
		this->y /= Length();
		
		return bf; 
	}

	void Vector2::Normalize(Vector2& result) const 
	{
		result.x /= Length(); 
		result.y /= Length(); 
	}

	Vector2 Vector2::Clamp(const Vector2& min, const Vector2& max)
	{
		Vector2 bf = *this;
		(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
		(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
		return bf;
	}

	void Vector2::Clamp(const Vector2& min, const Vector2& max, Vector2& ret)
	{
		(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
		(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
	}

	//static
	Vector2 operator+ (const Vector2& V1, const Vector2& V2)
	{
		return Vector2(V1.x + V2.x, V1.y + V2.y);
	}

	Vector2 operator- (const Vector2& V1, const Vector2& V2) 
	{
		return Vector2(V1.x - V2.x, V1.y - V2.y);
	}

	Vector2 operator* (float S, const Vector2& V)
	{
		return Vector2(V.x * S, V.y * S);
	}

	Vector2 operator* (const Vector2& V, float S)
	{
		return Vector2(V.x * S, V.y * S);
	}

	Vector2 operator/ (float S, const Vector2& V)
	{
		return Vector2(V.x / S, V.y / S);
	}

	Vector2 operator/ (const Vector2& V, float S) 
	{
		return Vector2(V.x / S, V.y / S);
	}

	float Vector2::Dot(const Vector2& v1, const Vector2& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y; 
	}

	float Vector2::Distance(const Vector2& v1, const Vector2& v2)
	{
		return (v2 - v1).Length(); 
	}

	float Vector2::DistanceSquared(const Vector2& v1, const Vector2& v2) 
	{
		return (v2 - v1).LengthSquared(); 
	}

	Vector2 Vector2::Min(const Vector2& v1, const Vector2& v2)
	{
		Vector2 ret;
		(v1.x <= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y <= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		return ret;
	}

	Vector2 Vector2::Max(const Vector2& v1, const Vector2& v2)
	{
		Vector2 ret;
		(v1.x >= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y >= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		return ret;
	}

	//선형 보간법
	Vector2 Vector2::Lerp(const Vector2& v1, const Vector2& v2, float t)
	{
		Vector2 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		return ret;
	}

	//스무스스텝. (필요한가..?)
	Vector2 Vector2::SmoothStep(const Vector2& v1, const Vector2& v2, float t)
	{
		Vector2 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t * t * (3.f - 2.f*t); //극솟값이 0, 극댓값이 1, 변곡점이 0.5. (이 조건을 만족한다면 다른 식을 써도 될 듯)
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		return ret;
	}

	//반사벡터 iV:반사시킬 벡터, nV:평면의 노말벡터.
	Vector2 Vector2::Reflect(const Vector2& iV, const Vector2& nV)
	{
		return 2.0f * Dot(iV, nV) * iV - iV;
	}

	//iV:굴절시킬 벡터, nV:평면의 노말벡터. rI:굴절율
	Vector2 Vector2::Refract(const Vector2& iV, const Vector2& nV, float rI)
	{
		float t = Dot(iV, nV);
		float r = 1.f - (rI*rI) * (1.f - (t*t));

		Vector2 rv;
		if (r < 0.f) {
			rv = { 0.f, 0.f };
		}
		else {
			float s = rI * t + sqrt(r);
			rv = { rI*iV.x - s * nV.x, rI*iV.y - s * nV.y };
		}
	}

	const Vector2 Vector2::Zero = { 0.f, 0.f };
	const Vector2 Vector2::UnitX = { 1.f, 0.f };
	const Vector2 Vector2::UnitY = { 0.f, 1.f };

	float3::float3()
	{
		x = 0.f; y = 0.f; z = 0.f;
	}

	float3::float3(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}

	Vector3::Vector3()
		: float3() {}

	Vector3::Vector3(float x)
		: float3(x, x, x) {}

	Vector3::Vector3(float x, float y, float z)
		: float3(x, y, z) {}

	Vector3::Vector3(const float3& F)
	{ 
		x = F.x; 
		y = F.y; 
		z = F.z; 
	}

	Vector3::Vector3(const Vector3& V)
	{ 
		x = V.x; 
		y = V.y; 
		z = V.z; 
	}

	bool Vector3::operator== (const Vector3& V) const 
	{ 
		if (x == V.x && y == V.y && z == V.z) {
			return true; 
		} 
		return false; 
	}

	bool Vector3::operator!= (const Vector3& V) const 
	{ 
		if (x == V.x && y == V.y && z == V.z) { 
			return false; 
		} 
		return true; 
	}

	Vector3& Vector3::operator+= (const Vector3& V) 
	{
		Vector3 rv = { x += V.x, y += V.y, z += V.z };
		return rv; 
	}

	Vector3& Vector3::operator-= (const Vector3& V) 
	{
		Vector3 rv = { x -= V.x, y -= V.y, z -= V.z };
		return rv;
	}

	Vector3& Vector3::operator*= (float S)
	{
		Vector3 rv = { x *= S, y *= S, z *= S };
		return rv;
	}

	Vector3& Vector3::operator/= (float S) 
	{
		Vector3 rv = { x /= S, y /= S, z /= S };
		return rv;
	}

	Vector3 Vector3::operator+ () const 
	{
		return *this; 
	}

	Vector3 Vector3::operator- () const 
	{
		return Vector3(-x, -y, -z); 
	}

	float Vector3::Length() const 
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float Vector3::LengthSquared() const 
	{
		return x*x + y*y + z*z;
	}

	float Vector3::Dot(const Vector3& V) const 
	{
		return x*V.x + y*V.y + z*V.z; 
	}

	Vector3 Vector3::Normalize() 
	{
		Vector3 bf = *this; 

		this->x /= Length(); 
		this->y /= Length(); 
		this->z /= Length(); 

		return bf; 
	}	

	void Vector3::Normalize(Vector3& result) const 
	{
		result.x /= Length(); 
		result.y /= Length();
		result.z /= Length(); 
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

	stdMatrix::stdMatrix(float4 __1, float4 __2, float4 __3, float4 __4) : float4x4(__1, __2, __3, __4)
	{
	}

	bool stdMatrix::operator== (const stdMatrix& M) const
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (abs(m[i][k] - M.m[i][k]) > L_Epsilon) {
					return false;
				}
			}
		}

		return true;
	}

	bool stdMatrix::operator!= (const stdMatrix& M) const
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (abs(m[i][k] - M.m[i][k]) > L_Epsilon) {
					return true;
				}
			}
		}

		return false;
	}

	stdMatrix stdMatrix::operator+ (const stdMatrix& M)
	{
		stdMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				ret.m[i][k] = m[i][k] + M.m[i][k];
			}
		}

		return ret;
	}

	stdMatrix stdMatrix::operator- (const stdMatrix& M)
	{
		stdMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				ret.m[i][k] = m[i][k] - M.m[i][k];
			}
		}

		return ret;
	}

	stdMatrix stdMatrix::operator* (const stdMatrix& M)
	{
		stdMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				ret.m[i][k] =
					m[i][0] * M.m[0][k] +
					m[i][1] * M.m[1][k] +
					m[i][2] * M.m[2][k] +
					m[i][3] * M.m[3][k];
			}
		}

		return ret;
	}

	stdMatrix stdMatrix::operator* (const float S)
	{
		stdMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				ret.m[i][k] = S * M.m[i][k];
			}
		}

		return ret;
	}

	stdMatrix stdMatrix::operator+= (const stdMatrix& M)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] += M.m[i][k];
			}
		}
		stdMatrix rm(*this);
		return rm;
	}

	stdMatrix stdMatrix::operator-= (const stdMatrix& M)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] -= M.m[i][k];
			}
		}
		stdMatrix rm(*this);
		return rm;
	}

	stdMatrix stdMatrix::Transpose()
	{
		stdMatrix ret = *this;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				m[i][k] = m[k][i];
			}
		}

		return ret;
	}

	void stdMatrix::Transpose(stdMatrix& result)
	{
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][k] = m[k][i];
			}
		}
	}

	//알고리즘을 쓰지 않고 그냥 생 노가다 식을 때려넣음(..)
	float stdMatrix::deteminant()
	{
		return
			m[0][0] * m[1][1] * m[2][2] * m[3][3] +
			m[0][0] * m[1][2] * m[2][3] * m[3][1] +
			m[0][0] * m[1][3] * m[2][1] * m[3][2] +

			m[0][1] * m[1][0] * m[2][3] * m[3][2] +
			m[0][1] * m[1][2] * m[2][0] * m[3][3] +
			m[0][1] * m[1][3] * m[2][2] * m[3][0] +

			m[0][2] * m[1][0] * m[2][1] * m[3][3] +
			m[0][2] * m[1][1] * m[2][3] * m[3][0] +
			m[0][2] * m[1][3] * m[2][0] * m[3][1] +

			m[0][3] * m[1][0] * m[2][2] * m[3][1] +
			m[0][3] * m[1][1] * m[2][0] * m[3][2] +
			m[0][3] * m[1][2] * m[2][1] * m[3][0] -

			m[0][0] * m[1][1] * m[2][3] * m[3][2] -
			m[0][0] * m[1][2] * m[2][1] * m[3][3] -
			m[0][0] * m[1][3] * m[2][2] * m[3][1] -
											
			m[0][1] * m[1][0] * m[2][2] * m[3][3] -
			m[0][1] * m[1][2] * m[2][3] * m[3][0] -
			m[0][1] * m[1][3] * m[2][0] * m[3][2] -
											
			m[0][2] * m[1][0] * m[2][3] * m[3][1] -
			m[0][2] * m[1][1] * m[2][0] * m[3][3] -
			m[0][2] * m[1][3] * m[2][1] * m[3][0] -
											
			m[0][3] * m[1][0] * m[2][1] * m[3][2] -
			m[0][3] * m[1][1] * m[2][2] * m[3][0] -
			m[0][3] * m[1][2] * m[2][0] * m[3][1];
	}

	//알고리즘을 쓰지 않고 그냥 생 노가다 식을 때려넣음(..)
	stdMatrix stdMatrix::Inverse()
	{
		stdMatrix ret = *this;

		float det = this->deteminant();

		assert(det != 0);

		float b11 = m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] - m[1][3] * m[2][2] * m[3][1];
		float b12 = m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] + m[0][3] * m[2][2] * m[3][1] - m[0][1] * m[2][2] * m[3][3] -	m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2];
		float b13 =	m[0][1] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][1] + m[0][3] * m[2][1] * m[3][2] - m[0][1] * m[2][3] * m[3][2] - m[0][2] * m[2][1] * m[3][3] - m[0][3] * m[2][2] * m[3][1];
		float b14 =	m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] + m[0][3] * m[1][2] * m[2][1] - m[0][1] * m[1][2] * m[2][3] -	m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2];

		float b21 =	m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] +	m[1][3] * m[2][2] * m[3][0] - m[1][0] * m[2][2] * m[3][3] -	m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2];
		float b22 =	m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] -	m[0][2] * m[2][0] * m[3][3] - m[0][3] * m[2][2] * m[3][0];
		float b23 = m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] +	m[0][3] * m[1][2] * m[3][0] - m[0][0] * m[1][2] * m[3][3] -	m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2];
		float b24 =	m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][0] +	m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] -	m[0][2] * m[1][0] * m[2][3] - m[0][3] * m[1][2] * m[2][0];

		float b31 =	m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] +	m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] -	m[1][1] * m[2][0] * m[3][3] - m[1][3] * m[2][1] * m[3][0];
		float b32 = m[1][0] * m[2][3] * m[3][1] + m[1][1] * m[2][0] * m[3][3] +	m[1][3] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][3] -	m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][1];
		float b33 = m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] +	m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] -	m[0][1] * m[1][0] * m[3][3] - m[0][3] * m[1][1] * m[3][0];
		float b34 =	m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] +	m[0][3] * m[1][1] * m[2][0] - m[0][0] * m[1][1] * m[2][3] -	m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1];

		float b41 = m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] + m[1][2] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1];
		float b42 =	m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0] +	m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] -	m[0][1] * m[2][0] * m[3][2] - m[0][2] * m[2][1] * m[3][0];
		float b43 =	m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] + m[0][2] * m[1][1] * m[3][0] - m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1];
		float b44 = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +	m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] -	m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];

		float4 b1 = { b11, b12, b13, b14 };
		float4 b2 = { b21, b22, b23, b24 };
		float4 b3 = { b31, b32, b33, b34 };
		float4 b4 = { b41, b42, b43, b44 };

		stdMatrix subMat = { b1, b2, b3, b4 };
		*this = 1/det * subMat;

		return ret;
	}

	void stdMatrix::Inverse(stdMatrix& result)
	{
		float det = this->deteminant();

		assert(det != 0);

		float b11 = m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] - m[1][3] * m[2][2] * m[3][1];
		float b12 = m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] + m[0][3] * m[2][2] * m[3][1] - m[0][1] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2];
		float b13 = m[0][1] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][1] + m[0][3] * m[2][1] * m[3][2] - m[0][1] * m[2][3] * m[3][2] - m[0][2] * m[2][1] * m[3][3] - m[0][3] * m[2][2] * m[3][1];
		float b14 = m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] + m[0][3] * m[1][2] * m[2][1] - m[0][1] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2];

		float b21 = m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] + m[1][3] * m[2][2] * m[3][0] - m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2];
		float b22 = m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] - m[0][3] * m[2][2] * m[3][0];
		float b23 = m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] + m[0][3] * m[1][2] * m[3][0] - m[0][0] * m[1][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2];
		float b24 = m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] - m[0][3] * m[1][2] * m[2][0];

		float b31 = m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] - m[1][3] * m[2][1] * m[3][0];
		float b32 = m[1][0] * m[2][3] * m[3][1] + m[1][1] * m[2][0] * m[3][3] + m[1][3] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][3] - m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][1];
		float b33 = m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] - m[0][3] * m[1][1] * m[3][0];
		float b34 = m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] + m[0][3] * m[1][1] * m[2][0] - m[0][0] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1];

		float b41 = m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] + m[1][2] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1];
		float b42 = m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] - m[0][2] * m[2][1] * m[3][0];
		float b43 = m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] + m[0][2] * m[1][1] * m[3][0] - m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1];
		float b44 = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];

		float4 b1 = { b11, b12, b13, b14 };
		float4 b2 = { b21, b22, b23, b24 };
		float4 b3 = { b31, b32, b33, b34 };
		float4 b4 = { b41, b42, b43, b44 };

		stdMatrix subMat = { b1, b2, b3, b4 };
		result = 1 / det * subMat;
	}



}