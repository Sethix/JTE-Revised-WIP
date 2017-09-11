#pragma once

#pragma region Defines

#define ID_MAT4 Matrix4{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 }

#pragma endregion

namespace JTL
{

#pragma region ForwardDeclarations

	struct Vector3;
	struct Vector4;
	struct Matrix3;

	struct Quaternion;

#pragma endregion

	__declspec(align(32)) struct Matrix4
	{
		union
		{ float m[16], mm[4][4]; };

#pragma region BinaryOperators	

		Matrix4& operator += (const Matrix4 &rhs);

		Matrix4& operator -= (const Matrix4 &rhs);

		Matrix4& operator *= (const Matrix4 &rhs);


		Matrix4  operator +  (const Matrix4 &rhs) const;

		Matrix4  operator -  (const Matrix4 &rhs) const;

		Matrix4  operator *  (const Matrix4 &rhs) const;

		Vector4  operator *  (const Vector4 &rhs) const;


		bool     operator == (const Matrix4 &rhs) const;

#pragma endregion

	};

#pragma region Functions

	float   Determinant(const Matrix4 &a);

	Matrix4 Inverse(const Matrix4 &a);

	Matrix4 Transpose(const Matrix4 &a);

	Matrix4 Matrix3To4(const Matrix3 &a);

#pragma region Transformation

	Matrix4 Rotation(const Vector3 &a);

	Matrix4 Rotation(const Vector3 &f, const Vector3 &u);

	Matrix4 Rotation(const Vector3 &f, const Vector3 &u, const Vector3 &r);

	//Matrix4 Rotate(const Quaternion &a);

	Matrix4 Scale(const Vector3 &a);

	Matrix4 Translation(const Vector3 &a);

#pragma endregion

#pragma region Projection

	Matrix4 OrthographicProjection(const float &l, const float &r, const float &b, const float &t, const float &n, const float &f);

	Matrix4 PerspectiveProjection(const float &w, const float &h, const float &fov, const float &n, const float &f);

#pragma endregion

#pragma endregion

}