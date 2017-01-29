#include <cassert>
#include <cfloat>
#include <cmath>
#include "Vector3.h"
#include "Quaternion.h"

namespace JTL
{
#pragma region BinaryOperators

	Vector3& Vector3::operator+= (const Vector3 &rhs)
	{ return *this = Vector3{ x + rhs.x, y + rhs.y, z + rhs.z }; }

	Vector3& Vector3::operator-= (const Vector3 &rhs)
	{ return *this = Vector3{ x - rhs.x, y - rhs.y, z - rhs.z }; }

	Vector3& Vector3::operator*= (const float   &rhs)
	{ return *this = Vector3{ x * rhs, y * rhs, z * rhs }; }

	Vector3& Vector3::operator/= (const float   &rhs)
	{ return *this = Vector3{ x / rhs, y / rhs, z / rhs }; }


	Vector3  Vector3::operator+  (const Vector3 &rhs) const
	{
		Vector3 result = *this;
		result += rhs;
		return result;
	}

	Vector3  Vector3::operator-  (const Vector3 &rhs) const
	{
		Vector3 result = *this;
		result -= rhs;
		return result;
	}

	Vector3  Vector3::operator*  (const float   &rhs) const
	{
		Vector3 result = *this;
		result *= rhs;
		return result;
	}

	Vector3  Vector3::operator/  (const float   &rhs) const
	{
		Vector3 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector3::operator==     (const Vector3 &rhs) const
	{
		return  x == rhs.x && y == rhs.y && z == rhs.z
			|| rhs < *this + E_VEC3 && *this - E_VEC3 < rhs;
	}

	bool Vector3::operator!=	 (const Vector3 &rhs) const
	{ return !(*this == rhs); }

	bool Vector3::operator<		 (const Vector3 &rhs) const
	{
		return x < rhs.x - FLT_EPSILON
			&& y < rhs.y - FLT_EPSILON
			&& z < rhs.z - FLT_EPSILON;
	}

	bool Vector3::operator>		 (const Vector3 &rhs) const
	{
		return x > rhs.x + FLT_EPSILON
			&& y > rhs.y + FLT_EPSILON
			&& z > rhs.z + FLT_EPSILON;
	}

	bool Vector3::operator<=		(const Vector3 &rhs) const
	{ return *this == rhs || *this < rhs; }

	bool Vector3::operator>=		(const Vector3 &rhs) const
	{ return *this == rhs || *this > rhs; }

#pragma endregion

#pragma region UnaryOperators

	float&  Vector3::operator[](unsigned i) { return v[i]; }

	float   Vector3::operator[](unsigned i) const { return v[i]; }


	Vector3  Vector3::operator-() const
	{
		return Vector3{ -x,-y,-z };
	}

#pragma endregion

#pragma region MemberFunctions

	Vector3 Vector3::Normalize()
	{ return *this = Normalized(*this); }

	Vector3 Vector3::Rotate(const Vector3 &axis, const float &angle)
	{
		float sAngle = sin(angle);
		float cAngle = cos(angle);

		return *this = Cross(*this, (axis * sAngle)) + *this * cAngle + axis * Dot(*this, axis * (1 - cAngle));
	}

	Vector3 Vector3::Rotate(const Quaternion &rotation)
	{
		Quaternion con = rotation;
		con.Conjugate();

		Quaternion result = rotation;
		result *= *this;
		result *= con;

		return *this = Vector3{ result.x, result.y, result.z };
	}

#pragma endregion

#pragma region Functions

	float    Dot(const Vector3 &a, const Vector3 &b)
	{ return a.x * b.x + a.y * b.y + a.z * b.z; }

	float    Length(const Vector3 &a)
	{ return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }

	Vector3  Normalized(const Vector3 &a)
	{
		float m = Length(a);
		return Vector3{ a.x / m, a.y / m, a.z / m };
	}

	Vector3  Cross(const Vector3 &a, const Vector3 &b)
	{
		return Vector3{ a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x };
	}

	Vector3  Lerp(const Vector3 &a, const Vector3 &b, const float   &alpha)
	{
		return Vector3{ a.x + (b.x - a.x) * alpha ,
			a.y + (b.y - a.y) * alpha ,
			a.z + (b.z - a.z) * alpha };
	}

	Vector3  Clamp(const Vector3 &a, const Vector3 &min, const Vector3 &max)
	{
		Vector3 r = a;

		if (a.x < min.x) r.x = min.x;
		else if (a.x > max.x) r.x = max.x;

		if (a.y < min.y) r.y = min.y;
		else if (a.y > max.y) r.y = max.y;

		if (a.z < min.z) r.z = min.z;
		else if (a.z > max.z) r.z = max.z;

		return r;
	}

	Vector3  Min(const Vector3 *pts, const size_t &n)
	{
		Vector3 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
			if (pts[i].z < temp.z) temp.z = pts[i].z;
		}

		return temp;
	}

	Vector3  Max(const Vector3 *pts, const size_t &n)
	{
		Vector3 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
			if (pts[i].z > temp.z) temp.z = pts[i].z;
		}

		return temp;
	}

	Vector3  Reflect(const Vector3 &incident, const Vector3 &normal)
	{ return incident - (normal * (2 * Dot(incident, normal))); }

#pragma endregion
}