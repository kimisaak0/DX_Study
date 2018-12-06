#pragma once
#include "stdHeader_L.h"

#define _USE_MATH_DEFINES

#include "DirectXMath.h" //<math.h> 포함
#include "DirectXPackedVector.h"
#include "DirectXCollision.h"
#include "DirectXColors.h"

using namespace DirectX;

//전방 선언
struct float2;
struct float3;
struct float4;

struct float4x4;
struct float3x3;
struct float2x2;
struct stdMatrix;


struct Vector2;
struct Vector3;
struct Vector4;

struct Quaternion;
struct Plane;

namespace Lypi
{

#define L_Epsilon             ( 0.001f )
#define L_Pi			      ( XM_PI )
#define L_e                   ( (float)M_E )
#define DegreeToRadian(d)     ( ((float)d) * (L_Pi / 180.0f) )
#define RadianToDegree(r)     ( ((float)r) * (180.0f / L_Pi) )
#define IS_IN_RANGE(v,r0,r1)  ( (((r0) <= (v)) && ((v) <= (r1))) ? true : false )

	struct float2
	{
		union {
			struct { float x, y; };
			float f[2];
		};

		float2()
		{
			x = 0.f; y = 0.f;
		}
		float2(float _x, float _y)
		{
			x = _x; y = _y;
		}
	};

	struct float3
	{
		union {
			struct { float x, y, z; };
			float f[3];
		};

		float3()
		{
			x = 0.f; y = 0.f; z = 0.f;
		}
		float3(float _x, float _y, float _z)
		{
			x = _x; y = _y; z = _z;
		}
	};

	struct float4
	{
		union {
			struct { float x, y, z, w; };
			float f[4];
		};

		float4()
		{
			x = 0.f; y = 0.f; z = 0.f; w = 0.f;
		}
		float4(float _x, float _y, float _z, float _w)
		{
			x = _x; y = _y; z = _z; w = _w;
		}
	};

	struct float4x4
	{
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};

	struct float3x3
	{
		union {
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
		};
	};
	
	struct float2x2
	{
		union {
			struct {
				float _11, _12;
				float _21, _22;
			};
			float m[2][2];
		};
	};

	struct stdMatrix : float4x4
	{
		static const stdMatrix Identity;

		//생성자 
		stdMatrix() { *this = Identity; }

		stdMatrix (	float __11, float __12, float __13, float __14,
			        float __21, float __22, float __23, float __24,
			        float __31, float __32, float __33, float __34,
			        float __41, float __42, float __43, float __44 )
		{
			_11 = __11; _12 = __12; _13 = __13; _14 = __14;
			_21 = __21; _22 = __22; _23 = __23; _24 = __24;
			_31 = __31; _32 = __32; _33 = __33; _34 = __34;
			_41 = __41; _42 = __42; _43 = __43; _44 = __44;
		}

		stdMatrix(const stdMatrix& m)
		{
			_11 = m._11; _12 = m._12; _13 = m._13; _14 = m._14;
			_21 = m._21; _22 = m._22; _23 = m._23; _24 = m._24;
			_31 = m._31; _32 = m._32; _33 = m._33; _34 = m._34;
			_41 = m._41; _42 = m._42; _43 = m._43; _44 = m._44;
		}

		//복사 생성자
		stdMatrix(const stdMatrix&) = default; //디폴트 복사 생성자를 생성할 것.
		stdMatrix(stdMatrix&&) = default;      //&& : 우측값 참조, 우측값을 인자로 받는 디폴트 복사 생성자를 생성할 것.

		//연산자 재정의
		stdMatrix& operator= (const stdMatrix&) = default;  //디폴트 대입 연산자를 재정의할 것.
		stdMatrix& operator= (stdMatrix&&) = default;       //우측값을 인자로 받는 대입 연산자를 재정의할 것.

		bool operator== (const stdMatrix& V) const 
		{ 
			if (_11 == V._11 && _12 == V._12 && _13 == V._13 && _14 == V._14 &&
				_21 == V._21 && _22 == V._22 && _23 == V._23 && _24 == V._24 &&
				_31 == V._31 && _32 == V._32 && _33 == V._33 && _34 == V._34 &&
			    _41 == V._41 && _42 == V._42 && _43 == V._43 && _44 == V._44){
				return true; 
			} 
			return false; 
		}

		bool operator!= (const stdMatrix& V) const
		{
			if (_11 == V._11 && _12 == V._12 && _13 == V._13 && _14 == V._14 &&
				_21 == V._21 && _22 == V._22 && _23 == V._23 && _24 == V._24 &&
				_31 == V._31 && _32 == V._32 && _33 == V._33 && _34 == V._34 &&
				_41 == V._41 && _42 == V._42 && _43 == V._43 && _44 == V._44) {
				return false;
			}
			return false;
		}

		stdMatrix operator+= (const stdMatrix& V)
		{
			_11 += V._11; _12 += V._12; _13 += V._13; _14 += V._14;
			_21 += V._21; _22 += V._22; _23 += V._23; _24 += V._24;
			_31 += V._31; _32 += V._32; _33 += V._33; _34 += V._34;
			_41 += V._41; _42 += V._42; _43 += V._43; _44 += V._44;
			stdMatrix rm(*this);
			return rm;		
		}

		stdMatrix operator-= (const stdMatrix& V)
		{
			_11 -= V._11; _12 -= V._12; _13 -= V._13; _14 -= V._14;
			_21 -= V._21; _22 -= V._22; _23 -= V._23; _24 -= V._24;
			_31 -= V._31; _32 -= V._32; _33 -= V._33; _34 -= V._34;
			_41 -= V._41; _42 -= V._42; _43 -= V._43; _44 -= V._44;
			stdMatrix rm(*this);
			return rm;
		}

		stdMatrix Transpose()
		{
			_11 = _11; _12 = _21; _13 = _31; _14 = _41;
			_21 = _12; _22 = _22; _23 = _32; _24 = _42;
			_31 = _13; _32 = _23; _33 = _33; _34 = _43;
			_41 = _14; _42 = _24; _43 = _34; _44 = _44;
		}

		void Transpose(stdMatrix& result)
		{
			result._11 = _11; result._12 = _21; result._13 = _31; result._14 = _41;
			result._21 = _12; result._22 = _22; result._23 = _32; result._24 = _42;
			result._31 = _13; result._32 = _23; result._33 = _33; result._34 = _43;
			result._41 = _14; result._42 = _24; result._43 = _34; result._44 = _44;
		}

		//static

	};

	struct Vector2 : float2
	{
		static const Vector2 Zero;
		static const Vector2 UnitX;
		static const Vector2 UnitY;

		//생성자
		Vector2() : float2() {}
		explicit Vector2(float x) : float2(x, x) {} //explicit : 자동 형변환 금지.
		Vector2(float x, float y) : float2(x, y) {}
		Vector2(float2 V) { x = V.x; y = V.y; }
		Vector2(const float2& V) { this->x = V.x; this->y = V.y; }

		explicit Vector2(const float2& F) { this->x = F.f[0]; this->y = F.f[1]; } // XMVECTORF32 : 실수 4개를 갖는 벡터. 

		//복사 생성자
		Vector2(const Vector2&) = default; //디폴트 복사 생성자를 생성할 것.
		Vector2(Vector2&&) = default;      //&& : 우측값 참조, 우측값을 인자로 받는 디폴트 복사 생성자를 생성할 것.

		//연산자재정의
		Vector2& operator=(const Vector2&) = default;  //디폴트 대입 연산자를 재정의할 것.
		Vector2& operator=(Vector2&&) = default;       //우측값을 인자로 받는 대입 연산자를 재정의할 것.

		bool operator== (const Vector2& V) const { if (x == V.x && y == V.y) { return true; } return false; }
		bool operator!= (const Vector2& V) const { if (x == V.x && y == V.y) { return false; } return true; }

		Vector2& operator+= (const Vector2& V) { this->x += V.x; this->y += V.y; Vector2 rv(this->x, this->y); return rv; }
		Vector2& operator-= (const Vector2& V) { this->x -= V.x; this->y -= V.y; Vector2 rv(this->x, this->y); return rv; }

		Vector2& operator*= (float S) { this->x *= S; this->y *= S; Vector2 rv(this->x, this->y); return rv; }
		Vector2& operator/= (float S) { this->x /= S; this->y /= S; Vector2 rv(this->x, this->y); return rv; }

		Vector2 operator+ () const { return *this; }
		Vector2 operator- () const { return Vector2(-x, -y); }

		float Length() const { return sqrtf(x*x + y * y); }
		float LengthSquared() const { return x * x + y * y; }

		float Dot(const Vector2& V) const { return this->x * V.x + this->y * V.y; }

		Vector2 Normalize() { Vector2 bf = *this; this->x /= Length(); this->y /= Length(); return bf; }    //자기자신을 바꾸고 이전값을 리턴.
		void Normalize(Vector2& result) const { result.x /= Length(); result.y /= Length(); }              //바꾼 값을 인자에 넣고 자기자신은 보존.

		Vector2 Clamp(const Vector2& min, const Vector2& max) //자기자신을 바꾸고 이전값을 리턴.
		{
			Vector2 bf = *this;
			(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
			(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
			return bf;
		}
		void Clamp(const Vector2& min, const Vector2& max, Vector2& ret)  //바꾼 값을 인자에 넣고 자기자신은 보존.
		{
			(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
			(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
		}

		//Vector2 Scale(const stdMatrix& m) // 자기자신을 바꾸고 이전값을 리턴
		//{
		//	Vector2 bf = *this;

		//	return bf;
		//	
		//}

		//연산자 재정의
		static friend Vector2 operator+ (const Vector2& V1, const Vector2& V2) { Vector2 rv; rv.x = V1.x + V2.x; rv.y = V1.y + V2.y; return rv; }
		static friend Vector2 operator- (const Vector2& V1, const Vector2& V2) { Vector2 rv; rv.x = V1.x - V2.x; rv.y = V1.y - V2.y; return rv; }
		static friend Vector2 operator* (float S, const Vector2& V) { Vector2 rv; rv.x *= S; rv.y *= S; return rv; }
		static friend Vector2 operator* (const Vector2& V, float S) { Vector2 rv; rv.x *= S; rv.y *= S; return rv; }
		static friend Vector2 operator/ (float S, const Vector2& V) { Vector2 rv; rv.x /= S; rv.y /= S; return rv; }
		static friend Vector2 operator/ (const Vector2& V, float S) { Vector2 rv; rv.x /= S; rv.y /= S; return rv; }

		//static function
		static float Dot(const Vector2& v1, const Vector2& v2) { return v1.x * v2.x + v1.y * v2.y; }

		static float Distance(const Vector2& v1, const Vector2& v2) { return (v2 - v1).Length(); }
		static float DistanceSquared(const Vector2& v1, const Vector2& v2) { return (v2 - v1).LengthSquared(); }

		static Vector2 Min(const Vector2& v1, const Vector2& v2)
		{
			Vector2 ret;
			(v1.x <= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
			(v1.y <= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
			return ret;
		}

		static Vector2 Max(const Vector2& v1, const Vector2& v2)
		{
			Vector2 ret;
			(v1.x >= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
			(v1.y >= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
			return ret;
		}

		//선형 보간법
		static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t)
		{
			Vector2 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			return ret;
		}

		//스무스스텝. (필요한가..?)
		static Vector2 SmoothStep(const Vector2& v1, const Vector2& v2, float t)
		{
			Vector2 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			t = t * t * (3.f - 2.f*t); //극솟값이 0, 극댓값이 1, 변곡점이 0.5. (이 조건을 만족한다면 다른 식을 써도 될 듯)
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			return ret;
		}

		//반사벡터 iV:반사시킬 벡터, nV:평면의 노말벡터.
		static Vector2 Reflect(const Vector2& iV, const Vector2& nV)
		{ return 2.0f * Dot(iV, nV) * iV - iV; }

		static Vector2 Refract(const Vector2& iV, const Vector2& nV, float rI)
		{
			float t = Dot(iV, nV);
			float r = 1.f - (rI*rI) * (1.f - (t*t));

			Vector2 rv;
			if (r < 0.f) {
				rv = { 0.f, 0.f }; 
			}
			else { 
				float s = rI * t + sqrt(r);
				rv = { rI*iV.x - s*nV.x, rI*iV.y - s*nV.y };
			}
		}
	};

	const Vector2 Vector2::Zero = { 0.f, 0.f };
	const Vector2 Vector2::UnitX = { 1.f, 0.f };
	const Vector2 Vector2::UnitY = { 0.f, 1.f };

	struct Vector3 : float3
	{
		static const Vector3 Zero;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;

		//생성자
		Vector3() : float3() {}
		explicit Vector3(float x) : float3(x, x, x) {} //explicit : 자동 형변환 금지.
		Vector3(float x, float y, float z) : float3(x, y, z) {}
		Vector3(float3 V) { x = V.x; y = V.y; z = V.z; }
		Vector3(const float3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }

		explicit Vector3(const float3& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; } 

		//복사 생성자
		Vector3(const Vector3&) = default; //디폴트 복사 생성자를 생성할 것.
		Vector3(Vector3&&) = default;      //&& : 우측값 참조, 우측값을 인자로 받는 디폴트 복사 생성자를 생성할 것.

		//연산자재정의
		Vector3& operator=(const Vector3&) = default;  //디폴트 대입 연산자를 재정의할 것.
		Vector3& operator=(Vector3&&) = default;       //우측값을 인자로 받는 대입 연산자를 재정의할 것.

		bool operator== (const Vector3& V) const { if (x == V.x && y == V.y && z == V.z) { return true; } return false; }
		bool operator!= (const Vector3& V) const { if (x == V.x && y == V.y && z == V.z) { return false; } return true; }

		Vector3& operator+= (const Vector3& V) { this->x += V.x; this->y += V.y; this->z += V.z; Vector3 rv(this->x, this->y, this->z); return rv; }
		Vector3& operator-= (const Vector3& V) { this->x -= V.x; this->y -= V.y; this->z -= V.z; Vector3 rv(this->x, this->y, this->z); return rv; }

		Vector3& operator*= (float S) { this->x *= S; this->y *= S; this->z *= S; Vector3 rv(this->x, this->y, this->z); return rv; }
		Vector3& operator/= (float S) { this->x /= S; this->y /= S; this->z /= S; Vector3 rv(this->x, this->y, this->z); return rv; }

		Vector3 operator+ () const { return *this; }
		Vector3 operator- () const { return Vector3(-x, -y, -z); }

		float Length() const { return sqrtf(x*x + y*y + z*z); }
		float LengthSquared() const { return x*x + y*y + z*z; }

		float Dot(const Vector3& V) const { return this->x*V.x + this->y*V.y + this->z*V.z; }

		Vector3 Normalize() { Vector3 bf = *this; this->x /= Length(); this->y /= Length(); this->z /= Length(); return bf; }    //자기자신을 바꾸고 이전값을 리턴.
		void Normalize(Vector3& result) const { result.x /= Length(); result.y /= Length(); result.z /= Length(); }              //바꾼 값을 인자에 넣고 자기자신은 보존.

		Vector3 Clamp(const Vector3& min, const Vector3& max) //자기자신을 바꾸고 이전값을 리턴.
		{
			Vector3 bf = *this;
			(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
			(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
			(z <= min.z) ? (z = min.z) : ((z > max.z) ? (z = max.z) : (z));
			return bf;
		}
		void Clamp(const Vector3& min, const Vector3& max, Vector3& ret)  //바꾼 값을 인자에 넣고 자기자신은 보존.
		{
			(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
			(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
			(ret.z <= min.z) ? (ret.z = min.z) : ((ret.z > max.z) ? (ret.z = max.z) : (ret.z));
		}

		//Vector3 Scale(const stdMatrix& m) // 자기자신을 바꾸고 이전값을 리턴
		//{
		//	Vector3 bf = *this;

		//	return bf;

		//}

		//연산자 재정의
		static friend Vector3 operator+ (const Vector3& V1, const Vector3& V2) { Vector3 rv; rv.x = V1.x + V2.x; rv.y = V1.y + V2.y; rv.z = V1.z + V2.z;  return rv; }
		static friend Vector3 operator- (const Vector3& V1, const Vector3& V2) { Vector3 rv; rv.x = V1.x - V2.x; rv.y = V1.y - V2.y; rv.z = V1.z - V2.z;  return rv; }
		static friend Vector3 operator* (float S, const Vector3& V) { Vector3 rv; rv.x *= S; rv.y *= S; rv.z *= S; return rv; }
		static friend Vector3 operator* (const Vector3& V, float S) { Vector3 rv; rv.x *= S; rv.y *= S; rv.z *= S; return rv; }
		static friend Vector3 operator/ (float S, const Vector3& V) { Vector3 rv; rv.x /= S; rv.y /= S; rv.z /= S; return rv; }
		static friend Vector3 operator/ (const Vector3& V, float S) { Vector3 rv; rv.x /= S; rv.y /= S; rv.z /= S; return rv; }

		//static function
		static float Dot(const Vector3& v1, const Vector3& v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }

		static float Distance(const Vector3& v1, const Vector3& v2) { return (v2 - v1).Length(); }
		static float DistanceSquared(const Vector3& v1, const Vector3& v2) { return (v2 - v1).LengthSquared(); }

		static Vector3 Min(const Vector3& v1, const Vector3& v2)
		{
			Vector3 ret;
			(v1.x <= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
			(v1.y <= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
			(v1.z <= v2.z) ? (ret.z = v1.z) : (ret.z = v2.z);
			return ret;
		}

		static Vector3 Max(const Vector3& v1, const Vector3& v2)
		{
			Vector3 ret;
			(v1.x >= v2.x) ? (ret.x = v1.x) : (ret.x = v2.x);
			(v1.y >= v2.y) ? (ret.y = v1.y) : (ret.y = v2.y);
			(v1.z >= v2.z) ? (ret.z = v1.z) : (ret.z = v2.z);
			return ret;
		}

		//선형 보간법
		static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
		{
			Vector3 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			ret.z = v1.z + t * (v2.z - v1.z);
			return ret;
		}

		//스무스스텝. (필요한가..?)
		static Vector3 SmoothStep(const Vector3& v1, const Vector3& v2, float t)
		{
			Vector3 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			t = t * t * (3.f - 2.f*t); //극솟값이 0, 극댓값이 1, 변곡점이 0.5. (이 조건을 만족한다면 다른 식을 써도 될 듯)
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			ret.z = v1.z + t * (v2.z - v1.z);
			return ret;
		}

		//반사벡터 iV:반사시킬 벡터, nV:평면의 노말벡터.
		static Vector3 Reflect(const Vector3& iV, const Vector3& nV)
		{
			return 2.0f * Dot(iV, nV) * iV - iV;
		}

		static Vector3 Refract(const Vector3& iV, const Vector3& nV, float rI)
		{
			float t = Dot(iV, nV);
			float r = 1.f - (rI*rI) * (1.f - (t*t));

			Vector3 rv;
			if (r < 0.f) {
				rv = { 0.f, 0.f, 0.f };
			}
			else {
				float s = rI * t + sqrt(r);
				rv = { rI*iV.x - s*nV.x, rI*iV.y - s*nV.y, rI*iV.z - s*nV.z };
			}
		}

		static Vector3 Angle(const Vector3& V1, const Vector3& V2)
		{
			return RadianToDegree(acos(Dot(V1, V2) / (V1.Length*V2.Length)));
		}
	};

}

const Vector3 Vector3::Zero = { 0.f, 0.f, 0.f };
const Vector3 Vector3::UnitX = { 1.f, 0.f, 0.f };
const Vector3 Vector3::UnitY = { 0.f, 1.f, 0.f };
const Vector3 Vector3::UnitZ = { 0.f, 0.f, 1.f };