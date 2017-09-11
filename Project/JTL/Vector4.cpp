#include <cassert>
#include <cfloat>
#include <cmath>
#include "Vector4.h"

namespace JTL
{
#pragma region BinaryOperators

	Vector4& Vector4::operator+= (const Vector4 &rhs)
	{ return *this = Vector4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }

	Vector4& Vector4::operator-= (const Vector4 &rhs)
	{ return *this = Vector4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }

	Vector4& Vector4::operator*= (const float   &rhs)
	{ return *this = Vector4{ x * rhs, y * rhs, z * rhs, w * rhs }; }

	Vector4& Vector4::operator/= (const float   &rhs)
	{ return *this = Vector4{ x / rhs, y / rhs, z / rhs, w / rhs }; }


	Vector4  Vector4::operator+  (const Vector4 &rhs) const
	{
		Vector4 result = *this;
		result += rhs;
		return result;
	}

	Vector4  Vector4::operator-  (const Vector4 &rhs) const
	{
		Vector4 result = *this;
		result -= rhs;
		return result;
	}

	Vector4  Vector4::operator*  (const float   &rhs) const
	{
		Vector4 result = *this;
		result *= rhs;
		return result;
	}

	Vector4  Vector4::operator/  (const float   &rhs) const
	{
		Vector4 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector4::operator==	 (const Vector4 &rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
			|| (rhs < *this + E_VEC4 && *this - E_VEC4 < rhs);
	}

	bool Vector4::operator!=	 (const Vector4 &rhs) const
	{ return !(*this == rhs); }

	bool Vector4::operator<		 (const Vector4 &rhs) const
	{
		return x < rhs.x - FLT_EPSILON
			&& y < rhs.y - FLT_EPSILON
			&& z < rhs.z - FLT_EPSILON
			&& w < rhs.w - FLT_EPSILON;
	}

	bool Vector4::operator>		 (const Vector4 &rhs) const
	{
		return x > rhs.x + FLT_EPSILON
			&& y > rhs.y + FLT_EPSILON
			&& z > rhs.z + FLT_EPSILON
			&& w > rhs.w + FLT_EPSILON;
	}

	bool Vector4::operator<=	 (const Vector4 &rhs) const
	{ return *this == rhs || *this < rhs; }

	bool Vector4::operator>=	 (const Vector4 &rhs) const
	{ return *this == rhs || *this > rhs; }

#pragma endregion

#pragma region UnaryOperators

	float& Vector4::operator[](unsigned i) { return v[i]; };

	float  Vector4::operator[](unsigned i) const { return v[i]; };


	Vector4  Vector4::operator-() const
	{ return Vector4{ -x,-y,-z,-w }; }

#pragma endregion

#pragma region MemberFunctions

	Vector4 Vector4::Normalize()
	{ return *this = Normalized(*this); }

#pragma endregion

#pragma region Functions

	float    Dot(const Vector4 &a, const Vector4 &b)
	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	float    Length(const Vector4 &a)
	{ return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

	Vector4  Normalized(const Vector4 &a)
	{
		float m = Length(a);
		return Vector4{ a.x / m, a.y / m, a.z / m, a.w / m };
	}

	Vector4  Lerp(const Vector4 &a, const Vector4 &b, const float   &alpha)
	{
		return Vector4{ a.x + (b.x - a.x) * alpha ,
			a.y + (b.y - a.y) * alpha ,
			a.z + (b.z - a.z) * alpha ,
			a.w + (b.w - a.w) * alpha };
	}

	Vector4  Clamp(const Vector4 &a, const Vector4 &min, const Vector4 &max)
	{
		Vector4 r = a;

		if (a.x < min.x) r.x = min.x;
		else if (a.x > max.x) r.x = max.x;

		if (a.y < min.y) r.y = min.y;
		else if (a.y > max.y) r.y = max.y;

		if (a.z < min.z) r.z = min.z;
		else if (a.z > max.z) r.z = max.z;

		if (a.w < min.w) r.w = min.w;
		else if (a.w > max.w) r.w = max.w;

		return r;
	}

	Vector4  Min(const Vector4 *pts, const size_t &n)
	{
		Vector4 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
			if (pts[i].z < temp.z) temp.z = pts[i].z;
			if (pts[i].w < temp.w) temp.w = pts[i].w;
		}

		return temp;
	}

	Vector4  Max(const Vector4 *pts, const size_t &n)
	{
		Vector4 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
			if (pts[i].z > temp.z) temp.z = pts[i].z;
			if (pts[i].w > temp.w) temp.w = pts[i].w;
		}

		return temp;
	}

#pragma endregion
}