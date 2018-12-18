#pragma once
#include "stdHeader_L.h"

#define _USE_MATH_DEFINES

#include "D3DX10math.h"

#include "DirectXMath.h" //<math.h> 포함
#include "DirectXPackedVector.h"
#include "DirectXCollision.h"
#include "DirectXColors.h"

using namespace DirectX;

namespace Lypi
{
	//전방 선언
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

		//생성자
		Vector2();
		explicit Vector2(float x);
		Vector2(float x, float y);
		Vector2(float2& F);

		//복사 생성자
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;

		//연산자재정의
		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;

		bool operator== (const Vector2& V);
		bool operator!= (const Vector2& V);

		Vector2 operator+= (const Vector2 V);
		Vector2 operator-= (const Vector2 V);
		Vector2 operator*= (const float S);
		Vector2 operator/= (const float S);

		Vector2 operator+ (const Vector2 V);
		Vector2 operator- (const Vector2 V);
		Vector2 operator* (const float S);
		Vector2 operator/ (const float S);
		
		Vector2 operator+ ();
		Vector2 operator- ();
		
		//멤버함수
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

		static Vector2 Lerp(Vector2 v1, Vector2 v2, float t); //선형 보간법
		static Vector2 SmoothStep(Vector2 v1, Vector2 v2, float t); //스무스스텝. (필요한가..?)

		static Vector2 Reflect(Vector2 iV, Vector2 nV); //iV:반사시킬 벡터, nV:평면의 노말벡터.
		static Vector2 Refract(Vector2 iV, Vector2 nV, float rI); //iV:굴절시킬 벡터, nV:평면의 노말벡터. rI:굴절율
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

		//생성자
		Vector3();
		explicit Vector3(float x);
		Vector3(float x, float y, float z);
		Vector3(float3& F);

		//복사 생성자
		Vector3(const Vector3&) = default;
		//Vector3(Vector3&&) = default;     

		//연산자재정의
		Vector3& operator=(const Vector3&) = default;
		//Vector3& operator=(Vector3&&) = default;

		bool operator== (const Vector3 V);
		bool operator!= (const Vector3 V);

		Vector3 operator+= (const Vector3 V);
		Vector3 operator-= (const Vector3 V);
		Vector3 operator*= (const float S);
		Vector3 operator/= (const float S);

		Vector3 operator+ (const Vector3 V);
		Vector3 operator- (const Vector3 V);
		Vector3 operator* (const float S);
		Vector3 operator/ (const float S);
		
		Vector3 operator+ ();
		Vector3 operator- ();

		//멤버함수
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

		static float Angle(Vector3 V1, Vector3 V2);
			
		static float Distance(Vector3 v1, Vector3 v2);
		static float DistanceSquared(Vector3 v1, Vector3 v2);

		static Vector3 Min(Vector3 v1, Vector3 v2);
		static Vector3 Max(Vector3 v1, Vector3 v2);

		static Vector3 Lerp(Vector3 v1, Vector3 v2, float t); //선형 보간법
		static Vector3 SmoothStep(Vector3 v1, Vector3 v2, float t); //스무스스텝. (필요한가..?)

		static Vector3 Reflect(Vector3 iV, Vector3 nV); //iV:반사시킬 벡터, nV:평면의 노말벡터.
		static Vector3 Refract(Vector3 iV, Vector3 nV, float rI); //iV:굴절시킬 벡터, nV:평면의 노말벡터. rI:굴절율
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

	struct Vector4 : float4
	{
		static const Vector4 Zero4;
		static const Vector4 UnitX4;
		static const Vector4 UnitY4;
		static const Vector4 UnitZ4;

		//생성자
		Vector4();
		explicit Vector4(float x);
		Vector4(float x, float y, float z, float w);
		Vector4(float4& F);

		//복사 생성자
		Vector4(const Vector4&) = default;
		//Vector3(Vector3&&) = default;     

		//연산자재정의
		Vector4& operator=(const Vector4&) = default;
		//Vector3& operator=(Vector3&&) = default;

		bool operator== (const Vector4 V);
		bool operator!= (const Vector4 V);

		Vector4 operator+= (const Vector4 V);
		Vector4 operator-= (const Vector4 V);
		Vector4 operator*= (const float S);
		Vector4 operator/= (const float S);

		Vector4 operator+ (const Vector4 V);
		Vector4 operator- (const Vector4 V);
		Vector4 operator* (const float S);
		Vector4 operator/ (const float S);

		Vector4 operator+ ();
		Vector4 operator- ();

		//static function
		//static Vector3 operator* (float S, Vector3 V);
		//static Vector3 operator/ (float S, Vector3 V);
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

		//복사연산자 기본값으로 정의
		float2x2(const float2x2&) = default;
		float2x2(float2x2&&) = default;

		//대입연산자 기본값으로 정의
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

		//복사연산자 기본값으로 정의
		float3x3(const float3x3&) = default;
		float3x3(float3x3&&) = default;

		//대입연산자 기본값으로 정의
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

		//복사연산자 기본값으로 정의
		float4x4(const float4x4&) = default;
		float4x4(float4x4&&) = default;

		//대입연산자 기본값으로 정의
		float4x4& operator= (const float4x4&) = default;
		float4x4& operator= (float4x4&&) = default;
	};


	struct stdMatrix : float4x4
	{
		//생성자 
		stdMatrix();
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
	};

	//static
	//static stdMatrix operator* (const float S, stdMatrix M);
	const stdMatrix Identity =
	{
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f, 0.f },
		{ 0.f, 0.f, 1.f, 0.f },
		{ 0.f, 0.f, 0.f, 1.f }
	};

	const stdMatrix ZeroMat =
	{
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f },
		{ 0.f, 0.f, 0.f, 0.f }
	};

	stdMatrix Transpose(stdMatrix& M);

	float deteminant(stdMatrix& M);
	stdMatrix Inverse(stdMatrix& M);

	stdMatrix InverseG(stdMatrix& M);

	stdMatrix Translation(const Vector3& V);

	stdMatrix Scale(const Vector3& V);

	stdMatrix XRotate(const float& Radian);

	stdMatrix YRotate(const float& Radian);

	stdMatrix ZRotate(const float& Radian);

	stdMatrix ObjectLookAt(Vector3& Pos, Vector3& Target, Vector3& Up);

	stdMatrix ViewLookAt(Vector3& Pos, Vector3& Target, Vector3& Up);

	stdMatrix CompViewMat(Vector3& Pos, Vector3& Target, Vector3& Up);

	stdMatrix PerspectiveLH(const float& NearPlane, const float& FarPlane, const float& Width, const float& Height);

	stdMatrix PerspectiveFovLH(const float& fovy, const float& Aspect, const float& NearPlane, const float& FarPlane);

	stdMatrix AxisAngle(const Vector3& vAxis, const float& Radian);

}