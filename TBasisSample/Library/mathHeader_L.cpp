#include "mathHeader_L.h"

namespace Lypi
{
#pragma region float2, Vector2
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

	Vector2::Vector2(float2& F)
	{
		x = F.x; 
		y = F.y; 
	}

	//연산자 재정의
	bool Vector2::operator== (Vector2& V)
	{
		if (abs(x - V.x) < L_Epsilon  && abs(y - V.y) <  L_Epsilon) {
			return true; 
		} 
		return false; 
	}

	bool Vector2::operator!= (Vector2& V)
	{
		if ( abs(x - V.x) < L_Epsilon && abs(y == V.y) < L_Epsilon) {
			return false; 
		} 
		return true; 
	}

	Vector2 Vector2::operator+= (Vector2 V) 
	{
		Vector2 rv = { x += V.x, y += V.y };
		return rv;
	}

	Vector2 Vector2::operator-= (Vector2 V) 
	{
		Vector2 rv = { x -= V.x, y -= V.y};
		return rv; 
	}

	Vector2 Vector2::operator*= (float S)
	{
		Vector2 rv = { x *= S, y *= S };
		return rv; 
	}

	Vector2 Vector2::operator/= (float S) 
	{
		Vector2 rv = { x /= S, y /= S };
		return rv; 
	}

	Vector2 Vector2::operator+ (Vector2 V)
	{
		Vector2 rv = { x + V.x, y + V.y };
		return rv;
	}

	Vector2 Vector2::operator- (Vector2 V)
	{
		Vector2 rv = { x - V.x, y - V.y };
		return rv;
	}

	Vector2 Vector2::operator* (float S)
	{
		Vector2 rv = { x * S, y * S };
		return rv;
	}

	Vector2 Vector2::operator/ (float S)
	{
		Vector2 rv = { x / S, y / S };
		return rv;
	}

	Vector2 Vector2::operator+ () 
	{
		return *this; 
	}

	Vector2 Vector2::operator- ()
	{
		return Vector2(-x, -y); 
	}

	float Vector2::Length() 
	{
		return sqrtf(x*x + y * y); 
	}

	float Vector2::LengthSquared()
	{
		return x * x + y * y; 
	}

	float Vector2::Dot(const Vector2 V)
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

	void Vector2::Normalize(Vector2 result)
	{
		result.x /= Length(); 
		result.y /= Length(); 
	}

	Vector2 Vector2::Clamp(const Vector2 min, const Vector2 max)
	{
		Vector2 bf = *this;
		(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
		(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
		return bf;
	}

	void Vector2::Clamp(Vector2 min, Vector2 max, Vector2 ret)
	{
		(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
		(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
	}

	//static function
	Vector2 operator* (float S, Vector2 V)
	{
		Vector2 rv = { V.x * S, V.y * S };
		return rv;
	}

	Vector2 operator/ (float S, Vector2 V)
	{
		Vector2 rv = { V.x / S, V.y / S };
		return rv;
	}

	float Vector2::Dot(Vector2 v1, Vector2 v2) 
	{
		return v1.x * v2.x + v1.y * v2.y; 
	}

	float Vector2::Distance(Vector2 v1, Vector2 v2)
	{
		return (v2 - v1).Length(); 
	}

	float Vector2::DistanceSquared(Vector2 v1, Vector2 v2) 
	{
		return (v2 - v1).LengthSquared(); 
	}

	Vector2 Vector2::Min(Vector2 v1, Vector2 v2)
	{
		Vector2 ret;
		(v1.x <= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y <= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		return ret;
	}

	Vector2 Vector2::Max(Vector2 v1, Vector2 v2)
	{
		Vector2 ret;
		(v1.x >= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y >= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		return ret;
	}

	Vector2 Vector2::Lerp(Vector2 v1, Vector2 v2, float t)
	{
		Vector2 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		return ret;
	}

	Vector2 Vector2::SmoothStep(Vector2 v1, Vector2 v2, float t)
	{
		Vector2 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t * t * (3.f - 2.f*t); //극솟값이 0, 극댓값이 1, 변곡점이 0.5. (이 조건을 만족한다면 다른 식을 써도 될 듯)
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		return ret;
	}

	Vector2 Vector2::Reflect(Vector2 iV, Vector2 nV)
	{
		return 2.0f * Dot(iV, nV) * (iV - iV);
	}

	Vector2 Vector2::Refract(Vector2 iV, Vector2 nV, float rI)
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

		return rv;

	}

	const Vector2 Vector2::Zero2 = { 0.f, 0.f };
	const Vector2 Vector2::UnitX2 = { 1.f, 0.f };
	const Vector2 Vector2::UnitY2 = { 0.f, 1.f };
#pragma endregion

#pragma region float3, Vector3

	float3::float3()
	{
		x = 0.f; y = 0.f; z = 0.f;
	}

	float3::float3(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}

	//생성자
	Vector3::Vector3()
		: float3() {}

	Vector3::Vector3(float x)
		: float3(x, x, x) {}

	Vector3::Vector3(float x, float y, float z)
		: float3(x, y, z) {}

	Vector3::Vector3(float3& F)
	{ 
		x = F.x; 
		y = F.y; 
		z = F.z; 
	}

	//연산자 재정의
	bool Vector3::operator== (Vector3 V)
	{ 
		if (abs(x - V.x) < L_Epsilon && abs(y - V.y) < L_Epsilon && abs(z - V.z) < L_Epsilon) {
			return true; 
		} 
		return false; 
	}

	bool Vector3::operator!= (Vector3 V)
	{ 
		if (abs(x - V.x) < L_Epsilon && abs(y - V.y) < L_Epsilon && abs(z - V.z) < L_Epsilon) {
			return false; 
		} 
		return true; 
	}

	Vector3 Vector3::operator+= (Vector3 V) 
	{
		Vector3 rv = { x += V.x, y += V.y, z += V.z };
		return rv; 
	}

	Vector3 Vector3::operator-= (const Vector3 V) 
	{
		Vector3 rv = { x -= V.x, y -= V.y, z -= V.z };
		return rv;
	}

	Vector3 Vector3::operator*= (float S)
	{
		Vector3 rv = { x *= S, y *= S, z *= S };
		return rv;
	}

	Vector3 Vector3::operator/= (float S) 
	{
		Vector3 rv = { x /= S, y /= S, z /= S };
		return rv;
	}

	Vector3 Vector3::operator+ (Vector3 V)
	{
		Vector3 rv = { x + V.x, y + V.y, z + V.z };
		return rv;
	}

	Vector3 Vector3::operator- (Vector3 V) 
	{ 
		Vector3 rv = { x + V.x, y + V.y, z - V.z };
		return rv;
	}

	Vector3 Vector3::operator* (float S)
	{
		Vector3 rv = { x * S, y * S, z * S };
		return rv;
	}

	Vector3 Vector3::operator/ (float S)
	{
		Vector3 rv = { x / S, y / S, z / S };
		return rv;
	}

	Vector3 Vector3::operator+ ()
	{
		return *this; 
	}

	Vector3 Vector3::operator- ()
	{
		return Vector3(-x, -y, -z); 
	}

	float Vector3::Length() 
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float Vector3::LengthSquared()
	{
		return x*x + y*y + z*z;
	}

	float Vector3::Dot(Vector3 V)
	{
		return x*V.x + y*V.y + z*V.z; 
	}

	Vector3 Vector3::Cross(Vector3 V)
	{
		return Vector3(y*V.x - z*V.y, z*V.x - x*V.z, x*V.y - y*V.x);
	}

	Vector3 Vector3::Normalize() 
	{
		Vector3 bf = *this; 

		this->x /= Length(); 
		this->y /= Length(); 
		this->z /= Length(); 

		return bf; 
	}	

	void Vector3::Normalize(Vector3 result)
	{
		result.x /= Length(); 
		result.y /= Length();
		result.z /= Length(); 
	}

	Vector3 Vector3::Clamp(Vector3 min, Vector3 max)
	{
		Vector3 bf = *this;
		(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
		(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
		(z <= min.z) ? (z = min.z) : ((z > max.z) ? (z = max.z) : (z));
		return bf;
	}

	void Vector3::Clamp(Vector3 min, Vector3 max, Vector3 ret)
	{
		(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
		(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
		(ret.z <= min.z) ? (ret.z = min.z) : ((ret.z > max.z) ? (ret.z = max.z) : (ret.z));
	}

	//static function
	Vector3 operator* (float S, Vector3 V)
	{
		Vector3 rv = { V.x * S, V.y * S, V.z * S };
		return rv;
	}
	Vector3 operator/ (float S, Vector3 V)
	{
		Vector3 rv = { V.x / S, V.y / S, V.z / S };
		return rv;
	}

	float Vector3::Dot(Vector3 v1, Vector3 v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
	{
		return Vector3(v1.y*v2.x - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	}

	float Vector3::Angle(Vector3 V1, Vector3 V2)
	{
		return RadianToDegree(acos(Dot(V1, V2) / ( (V1.Length())*(V2.Length()) ) ) );
	}
	
	float Vector3::Distance(Vector3 v1, Vector3 v2) 
	{
		return (v2 - v1).Length(); 
	}

	float Vector3::DistanceSquared(Vector3 v1, Vector3 v2)
	{
		return (v2 - v1).LengthSquared(); 
	}

	Vector3 Vector3::Min(Vector3 v1, Vector3 v2)
	{
		Vector3 ret;
		(v1.x <= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y <= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		(v1.z <= v2.z) ? (ret.z = v1.z) : (ret.z = v2.z);
		return ret;
	}

	Vector3 Vector3::Max(Vector3 v1, Vector3 v2)
	{
		Vector3 ret;
		(v1.x >= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
		(v1.y >= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
		(v1.z >= v2.z) ? (ret.z = v1.z) : (ret.z = v2.z);
		return ret;
	}

	Vector3 Vector3::Lerp(Vector3 v1, Vector3 v2, float t)
	{
		Vector3 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		ret.z = v1.z + t * (v2.z - v1.z);
		return ret;
	}

	Vector3 Vector3::SmoothStep(Vector3 v1, Vector3 v2, float t)
	{
		Vector3 ret;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t * t * (3.f - 2.f*t); //극솟값이 0, 극댓값이 1, 변곡점이 0.5. (이 조건을 만족한다면 다른 식을 써도 될 듯)
		ret.x = v1.x + t * (v2.x - v1.x);
		ret.y = v1.y + t * (v2.y - v1.y);
		ret.z = v1.z + t * (v2.z - v1.z);
		return ret;
	}

	Vector3 Vector3::Reflect(Vector3 iV, Vector3 nV)
	{
		return 2.0f * Dot(iV, nV) * iV - iV;
	}

	Vector3 Vector3::Refract(Vector3 iV, Vector3 nV, float rI)
	{
		float t = Dot(iV, nV);
		float r = 1.f - (rI*rI) * (1.f - (t*t));

		Vector3 rv;
		if (r < 0.f) {
			rv = { 0.f, 0.f, 0.f };
		}
		else {
			float s = rI * t + sqrt(r);
			rv = { rI*iV.x - s * nV.x, rI*iV.y - s * nV.y, rI*iV.z - s * nV.z };
		}

		return rv;
	}

	const Vector3 Vector3::Zero3 = { 0.f, 0.f, 0.f };
	const Vector3 Vector3::UnitX3 = { 1.f, 0.f, 0.f };
	const Vector3 Vector3::UnitY3 = { 0.f, 1.f, 0.f };
	const Vector3 Vector3::UnitZ3 = { 0.f, 0.f, 1.f };
#pragma endregion

#pragma region float4, Vector4

	float4::float4()
	{
		x = 0.f; y = 0.f; z = 0.f; w = 1.f;
	}

	float4::float4(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}
	
	//생성자
	Vector4::Vector4()
		: float4() {}

	Vector4::Vector4(float x)
		: float4(x, x, x, 1.f) {}

	Vector4::Vector4(float x, float y, float z, float w)
		: float4(x, y, z, w) {}

	Vector4::Vector4(float4& F)
	{
		x = F.x;
		y = F.y;
		z = F.z;
		w = F.w;
	}

	bool Vector4::operator== (Vector4 V)
	{
		if (abs(x - V.x) < L_Epsilon && abs(y - V.y) < L_Epsilon && abs(z - V.z) < L_Epsilon && abs(w - V.w) < L_Epsilon) {
			return true;
		}
		return false;
	}

	bool Vector4::operator!= (Vector4 V)
	{
		if (abs(x - V.x) < L_Epsilon && abs(y - V.y) < L_Epsilon && abs(z - V.z) < L_Epsilon && abs(w - V.w) < L_Epsilon) {
			return false;
		}
		return true;
	}

	Vector4 Vector4::operator+= (Vector4 V)
	{
		Vector4 rv = { x += V.x, y += V.y, z += V.z , w};
		return rv;
	}

	Vector4 Vector4::operator-= (Vector4 V)
	{
		Vector4 rv = { x -= V.x, y -= V.y, z -= V.z , w };
		return rv;
	}

	Vector4 Vector4::operator*= (float S)
	{
		Vector4 rv = { x *= S, y *= S, z *= S, w };
		return rv;
	}

	Vector4 Vector4::operator/= (float S)
	{
		Vector4 rv = { x /= S, y /= S, z /= S, w };
		return rv;
	}


	Vector4 Vector4::operator+ (Vector4 V)
	{
		Vector4 rv = { x + V.x, y + V.y, z + V.z, w };
		return rv;
	}

	Vector4 Vector4::operator- (Vector4 V)
	{
		Vector4 rv = { x - V.x, y - V.y, z - V.z, w };
		return rv;
	}

	Vector4 Vector4::operator* (float S)
	{
		Vector4 rv = { x * S, y * S, z * S, z };
		return rv;
	}

	Vector4 Vector4::operator/ (float S)
	{
		Vector4 rv = { x / S, y / S, z / S, z };
		return rv;
	}

	Vector4 Vector4::operator+ ()
	{
		return *this;
	}

	Vector4 Vector4::operator- ()
	{
		return Vector4(-x, -y, -z, w);
	}

	Vector4 operator* (float S, Vector4 V)
	{
		Vector4 rv = { V.x * S, V.y * S, V.z * S, V.w };
		return rv;
	}

	Vector4 operator/ (float S, Vector4 V)
	{
		Vector4 rv = { V.x / S, V.y / S, V.z / S, V.w };
		return rv;
	}

	const Vector4 Vector4::Zero4 = { 0.f, 0.f, 0.f, 1.f };
	const Vector4 Vector4::UnitX4 = { 1.f, 0.f, 0.f, 1.f };
	const Vector4 Vector4::UnitY4 = { 0.f, 1.f, 0.f, 1.f };
	const Vector4 Vector4::UnitZ4 = { 0.f, 0.f, 1.f, 1.f };

#pragma endregion

#pragma region matrix

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

#pragma endregion

#pragma region stdMatrix

	stdMatrix::stdMatrix(float4 __1, float4 __2, float4 __3, float4 __4)
		: float4x4(__1, __2, __3, __4)	{ }

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
				ret.m[i][k] = S * m[i][k];
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

	stdMatrix operator* (const float S, stdMatrix M)
	{
		stdMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				ret.m[i][k] = S * M.m[i][k];
			}
		}

		return ret;
	}

	stdMatrix Transpose(stdMatrix& M)
	{
		stdMatrix result;

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][k] = M.m[k][i];
			}
		}

		return result;
	}

	//알고리즘을 쓰지 않고 그냥 생 노가다 식을 때려넣음(..)
	float deteminant(stdMatrix& M)
	{
		return
			M.m[0][0] * M.m[1][1] * M.m[2][2] * M.m[3][3] +
			M.m[0][0] * M.m[1][2] * M.m[2][3] * M.m[3][1] +
			M.m[0][0] * M.m[1][3] * M.m[2][1] * M.m[3][2] +

			M.m[0][1] * M.m[1][0] * M.m[2][3] * M.m[3][2] +
			M.m[0][1] * M.m[1][2] * M.m[2][0] * M.m[3][3] +
			M.m[0][1] * M.m[1][3] * M.m[2][2] * M.m[3][0] +
			
			M.m[0][2] * M.m[1][0] * M.m[2][1] * M.m[3][3] +
			M.m[0][2] * M.m[1][1] * M.m[2][3] * M.m[3][0] +
			M.m[0][2] * M.m[1][3] * M.m[2][0] * M.m[3][1] +
			
			M.m[0][3] * M.m[1][0] * M.m[2][2] * M.m[3][1] +
			M.m[0][3] * M.m[1][1] * M.m[2][0] * M.m[3][2] +
			M.m[0][3] * M.m[1][2] * M.m[2][1] * M.m[3][0] -
			
			M.m[0][0] * M.m[1][1] * M.m[2][3] * M.m[3][2] -
			M.m[0][0] * M.m[1][2] * M.m[2][1] * M.m[3][3] -
			M.m[0][0] * M.m[1][3] * M.m[2][2] * M.m[3][1] -
			
			M.m[0][1] * M.m[1][0] * M.m[2][2] * M.m[3][3] -
			M.m[0][1] * M.m[1][2] * M.m[2][3] * M.m[3][0] -
			M.m[0][1] * M.m[1][3] * M.m[2][0] * M.m[3][2] -
			
			M.m[0][2] * M.m[1][0] * M.m[2][3] * M.m[3][1] -
			M.m[0][2] * M.m[1][1] * M.m[2][0] * M.m[3][3] -
			M.m[0][2] * M.m[1][3] * M.m[2][1] * M.m[3][0] -
			
			M.m[0][3] * M.m[1][0] * M.m[2][1] * M.m[3][2] -
			M.m[0][3] * M.m[1][1] * M.m[2][2] * M.m[3][0] -
			M.m[0][3] * M.m[1][2] * M.m[2][0] * M.m[3][1];
	}

	stdMatrix Inverse(stdMatrix& M)
	{
		stdMatrix result;

		float det = deteminant(M);

		assert(det != 0);

		float b11 = M.m[1][1] * M.m[2][2] * M.m[3][3] + M.m[1][2] * M.m[2][3] * M.m[3][1] + M.m[1][3] * M.m[2][1] * M.m[3][2] - M.m[1][1] * M.m[2][3] * M.m[3][2] - M.m[1][2] * M.m[2][1] * M.m[3][3] - M.m[1][3] * M.m[2][2] * M.m[3][1];
		float b12 = M.m[0][1] * M.m[2][3] * M.m[3][2] + M.m[0][2] * M.m[2][1] * M.m[3][3] + M.m[0][3] * M.m[2][2] * M.m[3][1] - M.m[0][1] * M.m[2][2] * M.m[3][3] - M.m[0][2] * M.m[2][3] * M.m[3][1] - M.m[0][3] * M.m[2][1] * M.m[3][2];
		float b13 = M.m[0][1] * M.m[2][2] * M.m[3][3] + M.m[0][2] * M.m[2][3] * M.m[3][1] + M.m[0][3] * M.m[2][1] * M.m[3][2] - M.m[0][1] * M.m[2][3] * M.m[3][2] - M.m[0][2] * M.m[2][1] * M.m[3][3] - M.m[0][3] * M.m[2][2] * M.m[3][1];
		float b14 = M.m[0][1] * M.m[1][3] * M.m[2][2] + M.m[0][2] * M.m[1][1] * M.m[2][3] + M.m[0][3] * M.m[1][2] * M.m[2][1] - M.m[0][1] * M.m[1][2] * M.m[2][3] - M.m[0][2] * M.m[1][3] * M.m[2][1] - M.m[0][3] * M.m[1][1] * M.m[2][2];
								
		float b21 = M.m[1][0] * M.m[2][3] * M.m[3][2] + M.m[1][2] * M.m[2][0] * M.m[3][3] + M.m[1][3] * M.m[2][2] * M.m[3][0] - M.m[1][0] * M.m[2][2] * M.m[3][3] - M.m[1][2] * M.m[2][3] * M.m[3][0] - M.m[1][3] * M.m[2][0] * M.m[3][2];
		float b22 = M.m[0][0] * M.m[2][2] * M.m[3][3] + M.m[0][2] * M.m[2][3] * M.m[3][0] + M.m[0][3] * M.m[2][0] * M.m[3][2] - M.m[0][0] * M.m[2][3] * M.m[3][2] - M.m[0][2] * M.m[2][0] * M.m[3][3] - M.m[0][3] * M.m[2][2] * M.m[3][0];
		float b23 = M.m[0][0] * M.m[1][3] * M.m[3][2] + M.m[0][2] * M.m[1][0] * M.m[3][3] + M.m[0][3] * M.m[1][2] * M.m[3][0] - M.m[0][0] * M.m[1][2] * M.m[3][3] - M.m[0][2] * M.m[1][3] * M.m[3][0] - M.m[0][3] * M.m[1][0] * M.m[3][2];
		float b24 = M.m[0][0] * M.m[1][2] * M.m[2][3] + M.m[0][2] * M.m[1][3] * M.m[2][0] + M.m[0][3] * M.m[1][0] * M.m[2][2] - M.m[0][0] * M.m[1][3] * M.m[2][2] - M.m[0][2] * M.m[1][0] * M.m[2][3] - M.m[0][3] * M.m[1][2] * M.m[2][0];

		float b31 = M.m[1][0] * M.m[2][1] * M.m[3][3] + M.m[1][1] * M.m[2][3] * M.m[3][0] + M.m[1][3] * M.m[2][0] * M.m[3][1] - M.m[1][0] * M.m[2][3] * M.m[3][1] - M.m[1][1] * M.m[2][0] * M.m[3][3] - M.m[1][3] * M.m[2][1] * M.m[3][0];
		float b32 = M.m[1][0] * M.m[2][3] * M.m[3][1] + M.m[1][1] * M.m[2][0] * M.m[3][3] + M.m[1][3] * M.m[2][1] * M.m[3][0] - M.m[1][0] * M.m[2][1] * M.m[3][3] - M.m[1][1] * M.m[2][3] * M.m[3][0] - M.m[1][3] * M.m[2][0] * M.m[3][1];
		float b33 = M.m[0][0] * M.m[1][1] * M.m[3][3] + M.m[0][1] * M.m[1][3] * M.m[3][0] + M.m[0][3] * M.m[1][0] * M.m[3][1] - M.m[0][0] * M.m[1][3] * M.m[3][1] - M.m[0][1] * M.m[1][0] * M.m[3][3] - M.m[0][3] * M.m[1][1] * M.m[3][0];
		float b34 = M.m[0][0] * M.m[1][3] * M.m[2][1] + M.m[0][1] * M.m[1][0] * M.m[2][3] + M.m[0][3] * M.m[1][1] * M.m[2][0] - M.m[0][0] * M.m[1][1] * M.m[2][3] - M.m[0][1] * M.m[1][3] * M.m[2][0] - M.m[0][3] * M.m[1][0] * M.m[2][1];
					
		float b41 = M.m[1][0] * M.m[2][2] * M.m[3][1] + M.m[1][1] * M.m[2][0] * M.m[3][2] + M.m[1][2] * M.m[2][1] * M.m[3][0] - M.m[1][0] * M.m[2][1] * M.m[3][2] - M.m[1][1] * M.m[2][2] * M.m[3][0] - M.m[1][2] * M.m[2][0] * M.m[3][1];
		float b42 = M.m[0][0] * M.m[2][1] * M.m[3][2] + M.m[0][1] * M.m[2][2] * M.m[3][0] + M.m[0][2] * M.m[2][0] * M.m[3][1] - M.m[0][0] * M.m[2][2] * M.m[3][1] - M.m[0][1] * M.m[2][0] * M.m[3][2] - M.m[0][2] * M.m[2][1] * M.m[3][0];
		float b43 = M.m[0][0] * M.m[1][2] * M.m[3][1] + M.m[0][1] * M.m[1][0] * M.m[3][2] + M.m[0][2] * M.m[1][1] * M.m[3][0] - M.m[0][0] * M.m[1][1] * M.m[3][2] - M.m[0][1] * M.m[1][2] * M.m[3][0] - M.m[0][2] * M.m[1][0] * M.m[3][1];
		float b44 = M.m[0][0] * M.m[1][1] * M.m[2][2] + M.m[0][1] * M.m[1][2] * M.m[2][0] + M.m[0][2] * M.m[1][0] * M.m[2][1] - M.m[0][0] * M.m[1][2] * M.m[2][1] - M.m[0][1] * M.m[1][0] * M.m[2][2] - M.m[0][2] * M.m[1][1] * M.m[2][0];

		stdMatrix subMat = { 
			{ b11, b12, b13, b14 },
			{ b21, b22, b23, b24 },
			{ b31, b32, b33, b34 },
			{ b41, b42, b43, b44 } 
		};

		return result = 1 / det * subMat;
	}

	stdMatrix InverseG(stdMatrix& M)
	{
		stdMatrix result;

		float d12 = (M._31*M._42 - M._41 * M._32);
		float d13 = (M._31*M._43 - M._41 * M._33);
		float d23 = (M._32*M._43 - M._42 * M._33);
		float d24 = (M._32*M._44 - M._42 * M._34);
		float d34 = (M._33*M._44 - M._43 * M._34);
		float d41 = (M._34*M._41 - M._44 * M._31);

		float tmp[16];
		tmp[0] = +(M._22 * d34 - M._23 * d24 + M._24 * d23);
		tmp[1] = -(M._21 * d34 + M._23 * d41 + M._24 * d13);
		tmp[2] = +(M._21 * d24 + M._22 * d41 + M._24 * d12);
		tmp[3] = -(M._21 * d23 - M._22 * d13 + M._23 * d12);
	
		float det = M._11 * tmp[0] + M._12 * tmp[1] + M._13 * tmp[2] + M._14 * tmp[3];
									 
		assert(det != 0);			 
									 
		float invDet = 1.0f / det;	 
		tmp[0] *= invDet;			 
		tmp[1] *= invDet;
		tmp[2] *= invDet;
		tmp[3] *= invDet;

		tmp[4] = -(M._12 * d34 - M._13 * d24 + M._14 * d23) * invDet;
		tmp[5] = +(M._11 * d34 + M._13 * d41 + M._14 * d13) * invDet;
		tmp[6] = -(M._11 * d24 + M._12 * d41 + M._14 * d12) * invDet;
		tmp[7] = +(M._11 * d23 - M._12 * d13 + M._13 * d12) * invDet;

		d12 = M._11 * M._22 - M._21 * M._12;
		d13 = M._11 * M._23 - M._21 * M._13;
		d23 = M._12 * M._23 - M._22 * M._13;
		d24 = M._12 * M._24 - M._22 * M._14;
		d34 = M._13 * M._24 - M._23 * M._14;
		d41 = M._14 * M._21 - M._24 * M._11;

		tmp[+8] = +(M._42 * d34 - M._43 * d24 + M._44 * d23) * invDet;
		tmp[+9] = -(M._41 * d34 + M._43 * d41 + M._44 * d13) * invDet;
		tmp[10] = +(M._41 * d24 + M._42 * d41 + M._44 * d12) * invDet;
		tmp[11] = -(M._41 * d23 - M._42 * d13 + M._43 * d12) * invDet;
		tmp[12] = -(M._32 * d34 - M._33 * d24 + M._34 * d23) * invDet;
		tmp[13] = +(M._31 * d34 + M._33 * d41 + M._34 * d13) * invDet;
		tmp[14] = -(M._31 * d24 + M._32 * d41 + M._34 * d12) * invDet;
		tmp[15] = +(M._31 * d23 - M._32 * d13 + M._33 * d12) * invDet;

		stdMatrix matInverse = {
			{ tmp[+0], tmp[+1], tmp[+2], tmp[+3] },
			{ tmp[+4], tmp[+5], tmp[+6], tmp[+7] },
			{ tmp[+8], tmp[+9], tmp[10], tmp[11] },
			{ tmp[12], tmp[13], tmp[14], tmp[15] },
		};

		return result = Transpose(matInverse);
	}

	stdMatrix Translation(const Vector3& V)
	{
		stdMatrix result;

		result._41 = V.x; result._42 = V.y; result._43 = V.z;

		return result;
	}

	stdMatrix Scale(const Vector3& V)
	{
		stdMatrix result;

		result._11 = V.x;
							result._22 = V.y;
												result._33 = V.z;

		return result;
	}


	stdMatrix XRotate(const float& Radian)
	{
		stdMatrix result;

		float Sin = (float)sin(Radian);	float Cos = (float)cos(Radian);

				result._22 =  Cos; result._23 = Sin;
				result._32 = -Sin; result._33 = Cos;

		return result;
	}

	stdMatrix YRotate(const float& Radian)
	{
		stdMatrix result;

		float Sin = (float)sin(Radian);	float Cos = (float)cos(Radian);

		result._11 =  Cos;		 result._13 = Sin;

		result._31 = -Sin;		 result._33 = Cos;

		return result;
	}

	stdMatrix ZRotate(const float& Radian)
	{
		stdMatrix result;

		float Sin = (float)sin(Radian);	float Cos = (float)cos(Radian);

		result._11 =  Cos; result._12 = Sin;
		result._21 = -Sin; result._22 = Cos;

		return result;
	}

	stdMatrix ObjectLookAt(Vector3& Pos, Vector3& Target, Vector3& Up)
	{
		stdMatrix result;

		Vector3 vDir = Target - Pos; vDir.Normalize();
		float fDot = Vector3::Dot(Up, vDir);
		Vector3 vC = vDir * fDot;
		Vector3 vUV = Up - (vDir * fDot); vUV.Normalize();
		Vector3 vRV = Vector3::Cross(vUV, vDir);

		result._11 =  vRV.x;  result._12 =  vRV.y; result._13 =  vRV.z;
		result._21 =  vUV.x;  result._22 =  vUV.y; result._23 =  vUV.z;
		result._31 = vDir.x;  result._32 = vDir.y; result._33 = vDir.z;
		result._41 =  Pos.x;  result._42 =  Pos.y; result._43 =  Pos.z;

		return result;
	}

	stdMatrix ViewLookAt(Vector3& Pos, Vector3& Target, Vector3& Up)
	{
		stdMatrix result;

		Vector3 vDir = Target - Pos; vDir.Normalize();
		float fDot = Vector3::Dot(Up, vDir);
		Vector3 vC = vDir * fDot;
		Vector3 vUV = Up - (vDir * fDot); vUV.Normalize();
		Vector3 vRV = Vector3::Cross(vUV, vDir);

		result._11 = vRV.x; result._12 = vUV.x; result._13 = vDir.x;
		result._21 = vRV.y; result._22 = vUV.y; result._23 = vDir.y;
		result._31 = vRV.z; result._32 = vUV.z; result._33 = vDir.z;

		result._41 = -(Pos.x* vRV.x + Pos.y* vRV.y + Pos.x* vRV.y);
		result._42 = -(Pos.x* vUV.x + Pos.y* vUV.y + Pos.x* vUV.y);
		result._43 = -(Pos.x*vDir.x + Pos.y*vDir.y + Pos.x*vDir.y);

		return result;
	}

	stdMatrix CompViewMat(Vector3& Pos, Vector3& Target, Vector3& Up)
	{
		stdMatrix result;

		result = ObjectLookAt(Pos, Target, Up);
		result = Inverse(result);

		return result;
	}

	stdMatrix PerspectiveLH(const float& NearPlane, const float& FarPlane, const float& Width, const float& Height)
	{
		stdMatrix result = ZeroMat;

		result._11 = (2.f * NearPlane) / (Width);
		result._22 = (2.f * NearPlane) / (Height);
		result._33 = FarPlane / (FarPlane - NearPlane);
		result._34 = 1.f;
		result._43 = NearPlane * FarPlane / (NearPlane - FarPlane);
	}


	stdMatrix PerspectiveFovLH(const float& fovy, const float& Aspect, const float& NearPlane, const float& FarPlane)
	{
		stdMatrix result = ZeroMat;

		result._11 = 1 / tan(fovy*0.5f) / (Aspect);
		result._22 = 1 / tan(fovy*0.5f);
		result._33 = FarPlane / (FarPlane - NearPlane);
		result._34 = 1.f;
		result._43 = NearPlane * FarPlane / (NearPlane - FarPlane);

		return result;
	}

	stdMatrix AxisAngle(const Vector3& vAxis, const float& Radian)
	{
		stdMatrix result;

		float Sin = (float)sin(Radian);	float Cos = (float)cos(Radian);

		result._11 = vAxis.x * vAxis.x * (1 - Cos) + Cos;
		result._12 = vAxis.y * vAxis.x * (1 - Cos) - (vAxis.z*Sin);
		result._13 = vAxis.z * vAxis.x * (1 - Cos) + (vAxis.y*Sin);
		result._14 = 0.f;

		result._21 = vAxis.x * vAxis.y * (1 - Cos) - (vAxis.z*Sin);
		result._22 = vAxis.y * vAxis.y * (1 - Cos) + Cos;
		result._23 = vAxis.z * vAxis.y * (1 - Cos) + (vAxis.x*Sin);
		result._24 = 0.f;

		result._31 = vAxis.x * vAxis.z * (1 - Cos) + (vAxis.y*Sin);
		result._32 = vAxis.y * vAxis.z * (1 - Cos) - (vAxis.x*Sin);
		result._33 = vAxis.z * vAxis.z * (1 - Cos) + Cos;
		result._34 = 0.f;

		result._41 = result._42 = result._43 = 0.f; result._44 = 1.f;

		return result;
	}

	const stdMatrix Identity = 
	{ 
		{1.f, 0.f, 0.f, 0.f},
	    {0.f, 1.f, 0.f, 0.f},
	    {0.f, 0.f, 1.f, 0.f},
	    {0.f, 0.f, 0.f, 1.f} 
	};

	const stdMatrix ZeroMat =
	{
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f }
	};
#pragma endregion
}