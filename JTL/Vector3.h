#pragma once
#include "Vector2.h"

#pragma region Defines

#define E_VEC3 Vector3{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}

#define FWD_VEC3 Vector3{0,0,1}
#define BAK_VEC3 Vector3{0,0,-1}
#define UP_VEC3 Vector3{0,1,0}
#define DN_VEC3 Vector3{0,-1,0}
#define RGT_VEC3 Vector3{1,0,0}
#define LFT_VEC3 Vector3{-1,0,0}

#pragma endregion

namespace JTL
{

#pragma region ForwardDeclarations

	struct Quaternion;

#pragma endregion

	__declspec(align(32)) struct Vector3
	{
		union
		{
			float v[3];
			struct { float x, y, z; };
			Vector2 xy;
		};

#pragma region BinaryOperators

		Vector3& operator+= (const Vector3 &rhs);

		Vector3& operator-= (const Vector3 &rhs);

		Vector3& operator*= (const float   &rhs);

		Vector3& operator/= (const float   &rhs);


		Vector3  operator+  (const Vector3 &rhs) const;

		Vector3  operator-  (const Vector3 &rhs) const;

		Vector3  operator*  (const float   &rhs) const;

		Vector3  operator/  (const float   &rhs) const;


		bool operator==     (const Vector3 &rhs) const;

		bool operator!=		(const Vector3 &rhs) const;

		bool operator<		(const Vector3 &rhs) const;

		bool operator>		(const Vector3 &rhs) const;

		bool operator<=		(const Vector3 &rhs) const;

		bool operator>=		(const Vector3 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned i);

		float  operator[](unsigned i) const;


		Vector3  operator-() const;

#pragma endregion

#pragma region MemberFunctions

		Vector3 Normalize();

		Vector3 Rotate(const Vector3 &axis, const float &angle);

		Vector3 Rotate(const Quaternion &rotation);

#pragma endregion

	};

#pragma region VectorFunctionHeaders

	float    Dot(const Vector3 &a, const Vector3 &b);

	float    Length(const Vector3 &v);

	Vector3  Normalized(const Vector3 &v);

	Vector3  Cross(const Vector3 &a, const Vector3 &b);

	Vector3  Lerp(const Vector3 &a, const Vector3 &b, const float &alpha);

	Vector3  Clamp(const Vector3 &a, const Vector3 &min, const Vector3 &max);

	Vector3  Min(const Vector3 *pts, const size_t &n);

	Vector3  Max(const Vector3 *pts, const size_t &n);

	Vector3  Reflect(const Vector3 &incident, const Vector3 &normal);

#pragma endregion

}