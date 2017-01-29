#pragma once
#include "Vector2.h"

#pragma region Defines

#define ID_MAT2 Matrix2{ 1,0,0,1 }

#pragma endregion

namespace JTL
{

	__declspec(align(32)) struct Matrix2
	{
		union
		{
			float m[4], mm[2][2];
			Vector2 r[2];
		};

#pragma region BinaryOperators

		Matrix2& operator += (const Matrix2 &rhs);

		Matrix2& operator -= (const Matrix2 &rhs);

		Matrix2& operator *= (const Matrix2 &rhs);


		Matrix2  operator +  (const Matrix2 &rhs) const;

		Matrix2  operator -  (const Matrix2 &rhs) const;

		Matrix2  operator *  (const Matrix2 &rhs) const;

		Vector2  operator *  (const Vector2 &rhs) const;


		bool     operator == (const Matrix2 &rhs) const;

#pragma endregion

	};

#pragma region Functions

	float   Determinant(const Matrix2 &a);

	Matrix2 Inverse(const Matrix2 &a);

	Matrix2 Transpose(const Matrix2 &a);

#pragma endregion

}