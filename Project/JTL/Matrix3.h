#pragma once
#include "Vector3.h"

#pragma region Defines

#define ID_MAT3 Matrix3{ 1,0,0,0,1,0,0,0,1 }

#pragma endregion

namespace JTL
{

	__declspec(align(32)) struct Matrix3
	{
		union
		{
			float m[9], mm[3][3];
			Vector3 r[3];
		};

#pragma region BinaryOperators

		Matrix3& operator += (const Matrix3 &rhs);

		Matrix3& operator -= (const Matrix3 &rhs);

		Matrix3& operator *= (const Matrix3 &rhs);


		Matrix3  operator +  (const Matrix3 &rhs) const;

		Matrix3  operator -  (const Matrix3 &rhs) const;

		Matrix3  operator *  (const Matrix3 &rhs) const;

		Vector3  operator *  (const Vector3 &rhs) const;


		bool     operator == (const Matrix3 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		Vector3  operator[](unsigned i) const;

		Vector3 &operator[](unsigned i);

#pragma endregion

	};

#pragma region Functions

	float    Determinant(const Matrix3 &a);

	Matrix3  Inverse(const Matrix3 &a);

	Matrix3  Transpose(const Matrix3 &a);

#pragma endregion

}