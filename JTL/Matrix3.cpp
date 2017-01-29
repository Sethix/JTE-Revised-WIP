#include <cassert>
#include <cmath>
#include "Matrix3.h"
#include "Vector2.h"
#include "Vector3.h"

namespace JTL
{

#pragma region BinaryOperators

	Matrix3& Matrix3::operator += (const Matrix3 &rhs)
	{
		return *this = Matrix3{
			m[0] + rhs.m[0] , m[1] + rhs.m[1] , m[2] + rhs.m[2] ,
			m[3] + rhs.m[3] , m[4] + rhs.m[4] , m[5] + rhs.m[5] ,
			m[6] + rhs.m[6] , m[7] + rhs.m[7] , m[8] + rhs.m[8] };
	}

	Matrix3& Matrix3::operator -= (const Matrix3 &rhs)
	{
		return *this = Matrix3{
			m[0] - rhs.m[0] , m[1] - rhs.m[1] , m[2] - rhs.m[2] ,
			m[3] - rhs.m[3] , m[4] - rhs.m[4] , m[5] - rhs.m[5] ,
			m[6] - rhs.m[6] , m[7] - rhs.m[7] , m[8] - rhs.m[8] };
	}

	Matrix3& Matrix3::operator *= (const Matrix3 &rhs)
	{
		return *this = Matrix3{
			mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0] + mm[0][2] * rhs.mm[2][0],
			mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1] + mm[0][2] * rhs.mm[2][1],
			mm[0][0] * rhs.mm[0][2] + mm[0][1] * rhs.mm[1][2] + mm[0][2] * rhs.mm[2][2],

			mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0] + mm[1][2] * rhs.mm[2][0],
			mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] + mm[1][2] * rhs.mm[2][1],
			mm[1][0] * rhs.mm[0][2] + mm[1][1] * rhs.mm[1][2] + mm[1][2] * rhs.mm[2][2],

			mm[2][0] * rhs.mm[0][0] + mm[2][1] * rhs.mm[1][0] + mm[2][2] * rhs.mm[2][0],
			mm[2][0] * rhs.mm[0][1] + mm[2][1] * rhs.mm[1][1] + mm[2][2] * rhs.mm[2][1],
			mm[2][0] * rhs.mm[0][2] + mm[2][1] * rhs.mm[1][2] + mm[2][2] * rhs.mm[2][2] };
	}


	Matrix3  Matrix3::operator +  (const Matrix3 &rhs) const
	{
		Matrix3 result = *this;
		result += rhs;
		return result;
	}

	Matrix3  Matrix3::operator -  (const Matrix3 &rhs) const
	{
		Matrix3 result = *this;
		result -= rhs;
		return result;
	}

	Matrix3  Matrix3::operator *  (const Matrix3 &rhs) const
	{
		Matrix3 result = *this;
		result *= rhs;
		return result;
	}

	Vector3  Matrix3::operator *  (const Vector3 &rhs) const
	{
		return Vector3{
			Dot(Vector3{ m[0], m[1], m[2] }, rhs),
			Dot(Vector3{ m[3], m[4], m[5] }, rhs),
			Dot(Vector3{ m[6], m[7], m[8] }, rhs)
		};
	}


	bool     Matrix3::operator == (const Matrix3 &rhs) const
	{
		return  m[0] == rhs.m[0] && m[1] == rhs.m[1] && m[2] == rhs.m[2] &&
			m[3] == rhs.m[3] && m[4] == rhs.m[4] && m[5] == rhs.m[5] &&
			m[6] == rhs.m[6] && m[7] == rhs.m[7] && m[8] == rhs.m[8];
	}

#pragma endregion

#pragma region UnaryOperators

	Vector3  Matrix3::operator[]  (unsigned i) const { return *(Vector3*)mm[i]; }

	Vector3& Matrix3::operator[]  (unsigned i) { return *(Vector3*)mm[i]; }

#pragma endregion

#pragma region Functions

	float   Determinant(const Matrix3 &a)
	{
		return{ a.mm[0][0] * a.mm[1][1] * a.mm[2][2] + a.mm[0][1] * a.mm[1][2] * a.mm[2][0] +
			a.mm[0][2] * a.mm[1][0] * a.mm[2][1] - a.mm[0][0] * a.mm[1][2] * a.mm[2][1] -
			a.mm[0][1] * a.mm[1][0] * a.mm[2][2] - a.mm[0][2] * a.mm[1][1] * a.mm[2][0] };
	}

	Matrix3 Inverse(const Matrix3 &a)
	{
		float d = 1 / Determinant(a);

		assert(d != 0);

		return{ (a.mm[1][1] * a.mm[2][2] - a.mm[2][1] * a.mm[1][2]) * d,
			(a.mm[0][2] * a.mm[2][1] - a.mm[0][1] * a.mm[2][2]) * d,
			(a.mm[0][1] * a.mm[1][2] - a.mm[0][2] * a.mm[1][1]) * d,

			(a.mm[1][2] * a.mm[2][0] - a.mm[1][0] * a.mm[2][2]) * d,
			(a.mm[0][0] * a.mm[2][2] - a.mm[0][2] * a.mm[2][0]) * d,
			(a.mm[1][0] * a.mm[0][2] - a.mm[0][0] * a.mm[1][2]) * d,

			(a.mm[1][0] * a.mm[2][1] - a.mm[2][0] * a.mm[1][1]) * d,
			(a.mm[2][0] * a.mm[0][1] - a.mm[0][0] * a.mm[2][1]) * d,
			(a.mm[0][0] * a.mm[1][1] - a.mm[1][0] * a.mm[0][1]) * d };
	}

	Matrix3 Transpose(const Matrix3 &a)
	{
		return Matrix3{ a.mm[0][0], a.mm[1][0], a.mm[2][0],
			a.mm[0][1], a.mm[1][1], a.mm[2][1],
			a.mm[0][2], a.mm[1][2], a.mm[2][2] };
	}

#pragma endregion

}