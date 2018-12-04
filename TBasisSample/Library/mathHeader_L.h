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
struct DxMatrix;
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

		//operator XMVECTOR() const { return XMLoadFloat2(this); } //�̰� ����...

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

		Vector2 operator+ (const Vector2& V) const { Vector2 rv; rv.x = this->x + V.x; rv.y = this->y + V.y; return rv; }
		Vector2 operator- (const Vector2& V) const { Vector2 rv; rv.x = this->x - V.x; rv.y = this->y - V.y; return rv; }

		Vector2 operator+ () const { return *this; }
		Vector2 operator- () const { return Vector2(-x, -y); }

		float Length() const { return sqrtf(x*x + y*y); }
		float LengthSquared() const { return x*x + y*y; }

		float Dot(const Vector2& V) const { return x*V.x + y*V.y; }
		



	};

}