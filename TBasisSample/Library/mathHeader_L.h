#pragma once
#include "stdHeader_L.h"

#include "DirectXMath.h"
#include "DirectXPackedVector.h"
#include "DirectXCollision.h"
#include "DirectXColors.h"

using namespace DirectX;

//전방 선언
struct Vector2;
struct Vector3;
struct Vector4;
struct stdMatrix;
struct Quaternion;
struct Plane;

namespace Lypi
{
	struct Vector2 : XMFLOAT2
	{
		//생성자
		Vector2() : XMFLOAT2(0.f, 0.f) {}
		explicit Vector2(float x) : XMFLOAT2(x, x) {} //explicit : 자동 형변환 금지.
		Vector2(float x, float y) : XMFLOAT2(x, y) {}
		explicit Vector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {} //_In_reads_(x) : 크기가 x인 인수만 받을 것.
		Vector2(XMFLOAT2 V) { x = V.x; y = V.y; }
		Vector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }

		explicit Vector2(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; } // XMVECTORF32 : 실수 4개를 갖는 벡터. 

		operator XMVECTOR() const { return XMLoadFloat2(this); } //...?

		//복사 생성자
		Vector2(const Vector2&) = default; //디폴트 복사 생성자를 생성할 것.
		Vector2(Vector2&&) = default;      //&& : 우측값 참조, 우측값을 인자로 받는 디폴트 복사 생성자를 생성할 것.

		//연산자재정의
		Vector2& operator=(const Vector2&) = default;  //디폴트 대입 연산자를 재정의할 것.
		Vector2& operator=(Vector2&&) = default;       //우측값을 인자로 받는 대입 연산자를 재정의할 것.
		Vector2& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; return *this; }

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

		Vector2 Scale(const stdMatrix& m) // 자기자신을 바꾸고 이전값을 리턴
		{
			Vector2 bf = *this;

			return bf;
			
		}


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

}