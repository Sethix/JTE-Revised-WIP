#pragma once

#pragma region Defines

#define E_VEC2 Vector2{FLT_EPSILON, FLT_EPSILON}

#pragma endregion

namespace JTL
{

	__declspec(align(16)) struct Vector2
	{
		union
		{
			float v[2];
			struct { float x, y; };
		};

#pragma region BinaryOperators

		Vector2& operator+= (const Vector2 &rhs);

		Vector2& operator-= (const Vector2 &rhs);

		Vector2& operator*= (const Vector2 &rhs);

		Vector2& operator/= (const Vector2 &rhs);

		Vector2& operator*= (const float   &rhs);

		Vector2& operator/= (const float   &rhs);


		Vector2  operator+  (const Vector2 &rhs) const;

		Vector2  operator-  (const Vector2 &rhs) const;

		Vector2  operator*  (const Vector2 &rhs) const;

		Vector2  operator/  (const Vector2 &rhs) const;

		Vector2  operator*  (const float   &rhs) const;

		Vector2  operator/  (const float   &rhs) const;


		bool operator==     (const Vector2 &rhs) const;

		bool operator!=     (const Vector2 &rhs) const;

		bool operator<      (const Vector2 &rhs) const;

		bool operator>      (const Vector2 &rhs) const;

		bool operator<=     (const Vector2 &rhs) const;

		bool operator>=     (const Vector2 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned idx);

		float  operator[](unsigned idx) const;


		Vector2  operator-() const;

#pragma endregion

#pragma region MemberFunctions

		Vector2 Normalize();

#pragma endregion

	};

#pragma region Functions

	float    Dot(const Vector2 &a, const Vector2 &b);

	float    Length(const Vector2 &a);

	float    ToAngle(const Vector2 &a);

	Vector2  FromAngle(const float &a);

	Vector2  Normalized(const Vector2 &a);

	Vector2  Lerp(const Vector2 &a, const Vector2 &b, const float &alpha);

	Vector2  Clamp(const Vector2 &a, const Vector2 &min, const Vector2 &max);

	Vector2  Min(const Vector2 *pts, const size_t &n);

	Vector2  Max(const Vector2 *pts, const size_t &n);

	Vector2  Perpendicular(const Vector2 &a);

	Vector2  Reflect(const Vector2 &incident, const Vector2 &normal);

	Vector2  Hermite(const Vector2 &ptA, const Vector2 &ptB, const Vector2 &tanA, const Vector2 &tanB, const float &t);

	Vector2  Bezier(const Vector2 &a, const Vector2 &b, const Vector2 &c, const Vector2 &d, const float &t);

#pragma endregion

}
