#pragma once
#include "stdHeader_L.h"

#define _USE_MATH_DEFINES

#include "DirectXMath.h" //<math.h> ����
#include "DirectXPackedVector.h"
#include "DirectXCollision.h"
#include "DirectXColors.h"

using namespace DirectX;

//���� ����
struct float2;
struct Vector2;

struct float3;
struct Vector3;

struct float4;
struct Vector4;

struct float2x2;
struct float3x3;
struct float4x4;
struct stdMatrix;

struct Quaternion;
struct Plane;

namespace Lypi
{

#define L_Epsilon             ( 0.0005f )
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

		float2();
		float2(float _x, float _y);
	};

	struct Vector2 : float2
	{
		static const Vector2 Zero2;
		static const Vector2 UnitX2;
		static const Vector2 UnitY2;

		//������
		Vector2();
		explicit Vector2(float x);
		Vector2(float x, float y);
		Vector2(float2& V);
		Vector2(Vector2& F);

		//���� ������
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;

		//������������
		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;

		bool operator== (Vector2& V);
		bool operator!= (Vector2& V);

		Vector2 operator+= (Vector2 V);
		Vector2 operator-= (Vector2 V);
		Vector2 operator*= (float S);
		Vector2 operator/= (float S);

		Vector2 operator+ (Vector2 V);
		Vector2 operator- (Vector2 V);

		Vector2 operator* (float S);
		Vector2 operator/ (float S);
		
		Vector2 operator+ ();
		Vector2 operator- ();
		
		//����Լ�
		float Length();
		float LengthSquared();

		float Dot(const Vector2 V);

		Vector2 Normalize();
		void Normalize(Vector2 result);

		Vector2 Clamp(Vector2 min, Vector2 max);
		void Clamp(Vector2 min, Vector2 max, Vector2 ret);

		//static function
		//static Vector2 operator* (float S, Vector2 V);
		//static Vector2 operator/ (float S, Vector2 V);

		static float Dot(Vector2 v1, Vector2 v2);
		static float Distance(Vector2 v1, Vector2 v2);
		static float DistanceSquared(Vector2 v1, Vector2 v2);

		static Vector2 Min(Vector2 v1, Vector2 v2);
		static Vector2 Max(Vector2 v1, Vector2 v2);

		static Vector2 Lerp(Vector2 v1, Vector2 v2, float t); //���� ������
		static Vector2 SmoothStep(Vector2 v1, Vector2 v2, float t); //����������. (�ʿ��Ѱ�..?)

		static Vector2 Reflect(Vector2 iV, Vector2 nV); //iV:�ݻ��ų ����, nV:����� �븻����.
		static Vector2 Refract(Vector2 iV, Vector2 nV, float rI); //iV:������ų ����, nV:����� �븻����. rI:������
	};

	struct float3
	{
		union {
			struct { float x, y, z; };
			float f[3];
		};

		float3();
		float3(float _x, float _y, float _z);
	};

	struct Vector3 : float3
	{
		static const Vector3 Zero3;
		static const Vector3 UnitX3;
		static const Vector3 UnitY3;
		static const Vector3 UnitZ3;

		//������
		Vector3();
		explicit Vector3(float x);
		Vector3(float x, float y, float z);
		Vector3(float3& F);
		Vector3(Vector3& V);

		//���� ������
		Vector3(const Vector3&) = default;
		Vector3(Vector3&&) = default;     

		//������������
		Vector3& operator=(const Vector3&) = default;
		Vector3& operator=(Vector3&&) = default;

		bool operator== (Vector3 V);
		bool operator!= (Vector3 V);

		Vector3 operator+= (Vector3 V);
		Vector3 operator-= (Vector3 V);
		Vector3 operator*= (float S);
		Vector3 operator/= (float S);

		Vector3 operator+ (Vector3 V);
		Vector3 operator- (Vector3 V);
		Vector3 operator* (float S);
		Vector3 operator/ (float S);
		
		Vector3 operator+ ();
		Vector3 operator- ();

		//����Լ�
		float Length();
		float LengthSquared();

		float Dot(Vector3 V);
		Vector3 Cross(Vector3 V);

		Vector3 Normalize();
		void Normalize(Vector3 result);

		Vector3 Clamp(Vector3 min, Vector3 max);
		void Clamp(Vector3 min, Vector3 max, Vector3 ret);

		//static function
		//static Vector3 operator* (float S, Vector3 V);
		//static Vector3 operator/ (float S, Vector3 V);

		static float Dot (Vector3 v1,Vector3 v2);
		static Vector3 Cross (Vector3 v1, Vector3 v2);

		static Vector3 Angle(Vector3 V1, Vector3 V2);
			
		static float Distance(Vector3 v1, Vector3 v2);
		static float DistanceSquared(Vector3 v1, Vector3 v2);

		static Vector3 Min(Vector3 v1, Vector3 v2);
		static Vector3 Max(Vector3 v1, Vector3 v2);

		static Vector3 Lerp(Vector3 v1, Vector3 v2, float t); //���� ������
		static Vector3 SmoothStep(Vector3 v1, Vector3 v2, float t); //����������. (�ʿ��Ѱ�..?)

		static Vector3 Reflect(Vector3 iV, Vector3 nV); //iV:�ݻ��ų ����, nV:����� �븻����.
		static Vector3 Refract(Vector3 iV, Vector3 nV, float rI); //iV:������ų ����, nV:����� �븻����. rI:������
	};

	struct float4
	{
		union {
			struct { float x, y, z, w; };
			float f[4];
		};

		float4();
		float4(float _x, float _y, float _z, float _w);
	};

	struct float2x2
	{
		union {
			struct {
				float _11, _12;
				float _21, _22;
			};
			float m[2][2];
			float2 _1, _2;
		};

		float2x2();
		float2x2(float2 __1, float2 __2);

		//���翬���� �⺻������ ����
		float2x2(const float2x2&) = default;
		float2x2(float2x2&&) = default;

		//���Կ����� �⺻������ ����
		float2x2& operator= (const float2x2&) = default;
		float2x2& operator= (float2x2&&) = default;
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
			float3 _1, _2, _3;
		};

		float3x3();
		float3x3(float3 __1, float3 __2, float3 __3);

		//���翬���� �⺻������ ����
		float3x3(const float3x3&) = default;
		float3x3(float3x3&&) = default;

		//���Կ����� �⺻������ ����
		float3x3& operator= (const float3x3&) = default;
		float3x3& operator= (float3x3&&) = default;
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
			float4 _1, _2, _3, _4;
		};

		float4x4();
		float4x4(float4 __1, float4 __2, float4 __3, float4 __4);

		//���翬���� �⺻������ ����
		float4x4(const float4x4&) = default;
		float4x4(float4x4&&) = default;

		//���Կ����� �⺻������ ����
		float4x4& operator= (const float4x4&) = default;
		float4x4& operator= (float4x4&&) = default;
	};

	struct stdMatrix : float4x4
	{
		static const stdMatrix Identity;
		static const stdMatrix ZeroMat;


		//������ 
		stdMatrix() { *this = Identity; }
		stdMatrix(float4 __1, float4 __2, float4 __3, float4 __4);

		//method
		bool operator== (const stdMatrix& M) const;
		bool operator!= (const stdMatrix& M) const;

		stdMatrix operator+= (const stdMatrix& M);
		stdMatrix operator-= (const stdMatrix& M);

		stdMatrix operator+ (const stdMatrix& M);
		stdMatrix operator- (const stdMatrix& M);
		stdMatrix operator* (const stdMatrix& M);
		stdMatrix operator* (const float S);

		//static
		//static stdMatrix operator* (const float S, stdMatrix M);

		stdMatrix Transpose();
		void Transpose(stdMatrix& result);

		float deteminant();
		stdMatrix Inverse();
		void Inverse(stdMatrix& result);

		stdMatrix InverseG();
		void InverseG(stdMatrix& result);

		stdMatrix Translation(const Vector3& V);
		void Translation(const Vector3& V, stdMatrix& result);

		stdMatrix Scale(const Vector3& V);
		void Scale(const Vector3& V, stdMatrix& result);

		stdMatrix XRotate(const float& Radian);
		void XRotate(const float& Radian, stdMatrix& result);

		stdMatrix YRotate(const float& Radian);
		void YRotate(const float& Radian, stdMatrix& result);

		stdMatrix ZRotate(const float& Radian);
		void ZRotate(const float& Radian, stdMatrix& result);

		stdMatrix ObjectLookAt(Vector3& Pos, Vector3& Target, Vector3& Up);
		void ObjectLookAt(Vector3& Pos, Vector3& Target, Vector3& Up, stdMatrix& result);

		stdMatrix ViewLookAt(Vector3& Pos, Vector3& Target, Vector3& Up);
		void ViewLookAt(Vector3& Pos, Vector3& Target, Vector3& Up, stdMatrix& result);

		stdMatrix CompViewMat(Vector3& Pos, Vector3& Target, Vector3& Up);
		void CompViewMat(Vector3& Pos, Vector3& Target, Vector3& Up, stdMatrix& result);

		stdMatrix PerspectiveLH(const float& NearPlane, const float& FarPlane, const float& Width, const float& Height);
		void PerspectiveLH(const float& NearPlane, const float& FarPlane, const float& Width, const float& Height, stdMatrix& result);

		stdMatrix PerspectiveFovLH(const float& NearPlane, const float& FarPlane, const float& fovy, const float& Aspect);
		void PerspectiveFovLH(const float& NearPlane, const float& FarPlane, const float& fovy, const float& Aspect, stdMatrix& result);

		stdMatrix AxisAngle(const Vector3& vAxis, const float& Radian);
		void AxisAngle(const Vector3& vAxis, const float& Radian, stdMatrix& result);
	};

}