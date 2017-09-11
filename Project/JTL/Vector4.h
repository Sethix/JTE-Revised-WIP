#pragma once
#include "Vector3.h"

#pragma region Defines

#define E_VEC4 Vector4{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}

#pragma endregion

namespace JTL
{

	__declspec(align(32)) struct Vector4
	{
		union
		{
			float v[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { Vector3 xyz; };
			struct { Vector2 xy; Vector2 zw; };
		};

#pragma region BinaryOperators

		Vector4& operator+= (const Vector4 &rhs);

		Vector4& operator-= (const Vector4 &rhs);

		Vector4& operator*= (const float   &rhs);

		Vector4& operator/= (const float   &rhs);


		Vector4  operator+  (const Vector4 &rhs) const;

		Vector4  operator-  (const Vector4 &rhs) const;

		Vector4  operator*  (const float   &rhs) const;

		Vector4  operator/  (const float   &rhs) const;


		bool operator==     (const Vector4 &rhs) const;

		bool operator!=		(const Vector4 &rhs) const;

		bool operator<		(const Vector4 &rhs) const;

		bool operator>		(const Vector4 &rhs) const;

		bool operator<=		(const Vector4 &rhs) const;

		bool operator>=		(const Vector4 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned i);

		float  operator[](unsigned i) const;


		Vector4  operator-() const;

#pragma endregion

#pragma region MemberFunctions

		Vector4 Normalize();

#pragma endregion

	};

#pragma region Functions

	float    Dot(const Vector4 &a, const Vector4 &b);

	float    Length(const Vector4 &a);

	Vector4  Normalized(const Vector4 &a);

	Vector4  Lerp(const Vector4 &a, const Vector4 &b, const float &alpha);

	Vector4  Clamp(const Vector4 &a, const Vector4 &min, const Vector4 &max);

	Vector4  Min(const Vector4 *pts, const size_t &n);

	Vector4  Max(const Vector4 *pts, const size_t &n);

#pragma endregion

}
