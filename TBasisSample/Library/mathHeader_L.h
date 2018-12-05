#pragma once
#include "stdHeader_L.h"

#include "DirectXMath.h"
#include "DirectXPackedVector.h"
#include "DirectXCollision.h"
#include "DirectXColors.h"

using namespace DirectX;

//���� ����
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
		//������
		Vector2() : XMFLOAT2(0.f, 0.f) {}
		explicit Vector2(float x) : XMFLOAT2(x, x) {} //explicit : �ڵ� ����ȯ ����.
		Vector2(float x, float y) : XMFLOAT2(x, y) {}
		explicit Vector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {} //_In_reads_(x) : ũ�Ⱑ x�� �μ��� ���� ��.
		Vector2(XMFLOAT2 V) { x = V.x; y = V.y; }
		Vector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }

		explicit Vector2(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; } // XMVECTORF32 : �Ǽ� 4���� ���� ����. 

		operator XMVECTOR() const { return XMLoadFloat2(this); } //...?

		//���� ������
		Vector2(const Vector2&) = default; //����Ʈ ���� �����ڸ� ������ ��.
		Vector2(Vector2&&) = default;      //&& : ������ ����, �������� ���ڷ� �޴� ����Ʈ ���� �����ڸ� ������ ��.

		//������������
		Vector2& operator=(const Vector2&) = default;  //����Ʈ ���� �����ڸ� �������� ��.
		Vector2& operator=(Vector2&&) = default;       //�������� ���ڷ� �޴� ���� �����ڸ� �������� ��.
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

		Vector2 Normalize() { Vector2 bf = *this; this->x /= Length(); this->y /= Length(); return bf; }    //�ڱ��ڽ��� �ٲٰ� �������� ����.
		void Normalize(Vector2& result) const { result.x /= Length(); result.y /= Length(); }              //�ٲ� ���� ���ڿ� �ְ� �ڱ��ڽ��� ����.

		Vector2 Clamp(const Vector2& min, const Vector2& max) //�ڱ��ڽ��� �ٲٰ� �������� ����.
		{
			Vector2 bf = *this;
			(x <= min.x) ? (x = min.x) : ((x > max.x) ? (x = max.x) : (x));
			(y <= min.y) ? (y = min.y) : ((y > max.y) ? (y = max.y) : (y));
			return bf;
		}
		void Clamp(const Vector2& min, const Vector2& max, Vector2& ret)  //�ٲ� ���� ���ڿ� �ְ� �ڱ��ڽ��� ����.
		{
			(ret.x <= min.x) ? (ret.x = min.x) : ((ret.x > max.x) ? (ret.x = max.x) : (ret.x));
			(ret.y <= min.y) ? (ret.y = min.y) : ((ret.y > max.y) ? (ret.y = max.y) : (ret.y));
		}

		Vector2 Scale(const stdMatrix& m) // �ڱ��ڽ��� �ٲٰ� �������� ����
		{
			Vector2 bf = *this;

			return bf;
			
		}


		//������ ������
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

		//���� ������
		static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t)
		{
			Vector2 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			return ret;
		}

		//����������. (�ʿ��Ѱ�..?)
		static Vector2 SmoothStep(const Vector2& v1, const Vector2& v2, float t)
		{
			Vector2 ret;
			t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
			t = t * t * (3.f - 2.f*t); //�ؼڰ��� 0, �ش��� 1, �������� 0.5. (�� ������ �����Ѵٸ� �ٸ� ���� �ᵵ �� ��)
			ret.x = v1.x + t * (v2.x - v1.x);
			ret.y = v1.y + t * (v2.y - v1.y);
			return ret;
		}

		//�ݻ纤�� iV:�ݻ��ų ����, nV:����� �븻����.
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