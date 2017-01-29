#include <cassert>
#include <cfloat>
#include <cmath>
#include "JTLMath.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Vector4.h"

namespace JTL
{

#pragma region BinaryOperators

	Vector2& Vector2::operator+= (const Vector2 &rhs)
	{ return *this = Vector2{ x + rhs.x, y + rhs.y }; }

	Vector2& Vector2::operator-= (const Vector2 &rhs)
	{ return *this = Vector2{ x - rhs.x, y - rhs.y }; }

	Vector2& Vector2::operator*= (const Vector2 &rhs)
	{ return *this = Vector2{ x * rhs.x, y * rhs.y }; }

	Vector2& Vector2::operator/= (const Vector2 &rhs)
	{ return *this = Vector2{ x / rhs.x, y / rhs.y }; }

	Vector2& Vector2::operator*= (const float   &rhs)
	{ return *this = Vector2{ x * rhs, y * rhs }; }

	Vector2& Vector2::operator/= (const float   &rhs)
	{ return *this = Vector2{ x / rhs, y / rhs }; }


	Vector2  Vector2::operator+  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result += rhs;
		return result;
	}

	Vector2  Vector2::operator-  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result -= rhs;
		return result;
	}

	Vector2  Vector2::operator*  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result *= rhs;
		return result;
	}

	Vector2  Vector2::operator/  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result /= rhs;
		return result;
	}

	Vector2  Vector2::operator*  (const float   &rhs) const
	{
		Vector2 result = *this;
		result *= rhs;
		return result;
	}

	Vector2  Vector2::operator/  (const float   &rhs) const
	{
		Vector2 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector2::operator==     (const Vector2 &rhs) const
	{
		return x == rhs.x && y == rhs.y
			|| rhs < *this + E_VEC2 && *this - E_VEC2 < rhs;
	}

	bool Vector2::operator!=     (const Vector2 &rhs) const
	{ return !(*this == rhs); }

	bool Vector2::operator<      (const Vector2 &rhs) const
	{ return x < rhs.x - FLT_EPSILON && y < rhs.y - FLT_EPSILON; }

	bool Vector2::operator>      (const Vector2 &rhs) const
	{ return x > rhs.x + FLT_EPSILON && y > rhs.y + FLT_EPSILON; }

	bool Vector2::operator<=     (const Vector2 &rhs) const
	{ return *this == rhs || *this < rhs; }

	bool Vector2::operator>=     (const Vector2 &rhs) const
	{ return *this == rhs || *this > rhs; }

#pragma endregion

#pragma region UnaryOperators

	float   &Vector2::operator[](unsigned idx) { return v[idx]; }

	float    Vector2::operator[](unsigned idx) const { return v[idx]; }


	Vector2  Vector2::operator-() const
	{ return Vector2{ -x,-y }; }

#pragma endregion

#pragma region MemberFunctions

	Vector2     Vector2::Normalize()
	{ return *this = Normalized(*this); }

#pragma endregion

#pragma region Functions

	float    Dot(const Vector2 &a, const Vector2 &b)
	{ return a.x * b.x + a.y * b.y; }

	float    Length(const Vector2 &a)
	{ return sqrtf(a.x * a.x + a.y * a.y); }

	float    ToAngle(const Vector2 &a)
	{ return atan2f(a.y, a.x); }

	Vector2  FromAngle(const float   &a)
	{ return Vector2{ cosf(a), sinf(a) }; }

	Vector2  Normalized(const Vector2 &a)
	{
		float m = Length(a);
		return Vector2{ a.x / m, a.y / m };
	}

	Vector2  Lerp(const Vector2 &a, const Vector2 &b, const float   &alpha)
	{ return Vector2{ a.x + (b.x - a.x) * alpha, a.y + (b.y - a.y) * alpha }; }

	Vector2  Clamp(const Vector2 &a, const Vector2 &min, const Vector2 &max)
	{
		Vector2 r = a;

		r.x = fltClamp(a.x, min.x, max.x);
		r.y = fltClamp(a.y, min.y, max.y);

		return r;
	}

	Vector2  Min(const Vector2 *pts, const size_t &n)
	{
		Vector2 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
		}

		return temp;
	}

	Vector2  Max(const Vector2 *pts, const size_t &n)
	{
		Vector2 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
		}

		return temp;
	}

	Vector2  Perpendicular(const Vector2 &a)
	{ return{ -a.y, a.x }; }

	Vector2  Reflect(const Vector2 &incident, const Vector2 &normal)
	{ return incident - (normal * (2 * Dot(incident, normal))); }

	Vector2  Hermite(const Vector2 &ptA, const Vector2 &ptB, const Vector2 &tanA, const Vector2 &tanB, const float &t)
	{
		float h1 = pow(2 * t, 3) - pow(3 * t, 2) + 1;
		float h2 = pow(-2 * t, 3) + pow(3 * t, 2);
		float h3 = pow(t, 3) - 2 * pow(t, 2) + t;
		float h4 = pow(t, 3) - pow(t, 2);

		return{ h1 * ptA.x + h2 * ptB.x + h3 * tanA.x + h4 * tanB.x,
			h1 * ptA.y + h2 * ptB.y + h3 * tanA.y + h4 * tanB.y };
	}

	Vector2  Bezier(const Vector2 &a, const Vector2 &b, const Vector2 &c, const Vector2 &d, const float &t)
	{
		Vector2 ab, bc, cd, abbc, bccd;
		ab = Lerp(a, b, t);
		bc = Lerp(b, c, t);
		cd = Lerp(c, d, t);
		abbc = Lerp(ab, bc, t);
		bccd = Lerp(bc, cd, t);
		return Lerp(abbc, bccd, t);
	}

#pragma endregion

}