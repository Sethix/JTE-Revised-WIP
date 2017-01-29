#pragma once
#include "Vector3.h"

#pragma region Defines

#define ID_QUAT {0,0,0,1}
#define E_QUAT { FLT_EPSILON, FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}

#pragma endregion

namespace JTL
{

	struct Matrix4;

	__declspec(align(32)) struct Quaternion
	{
		union
		{
			float q[4];
			struct { float x, y, z, w; };
			struct { Vector3 xyz; };
		};

#pragma region Constructors

		Quaternion();
		
		Quaternion(const float &_x, const float &_y, const float &_z, const float &_w);

		Quaternion(const Vector3 &axis, const float &angle);

		Quaternion(const Matrix4 &m);

#pragma endregion

#pragma region BinaryOperators

		Quaternion& operator+= (const Quaternion &rhs);

		Quaternion& operator-= (const Quaternion &rhs);

		Quaternion& operator*= (const float		 &rhs);

		Quaternion& operator*= (const Vector3	 &rhs);

		Quaternion& operator*= (const Quaternion &rhs);


		Quaternion& operator+  (const Quaternion &rhs);

		Quaternion& operator-  (const Quaternion &rhs);

		Quaternion& operator*  (const float		 &rhs);

		Quaternion& operator*  (const Vector3    &rhs);

		Quaternion& operator*  (const Quaternion &rhs);


		Quaternion& operator+  (const Quaternion &rhs) const;

		Quaternion& operator-  (const Quaternion &rhs) const;

		Quaternion& operator*  (const float		 &rhs) const;

		Quaternion& operator*  (const Vector3    &rhs) const;

		Quaternion& operator*  (const Quaternion &rhs) const;


		bool		operator== (const Quaternion &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		Quaternion operator- () const;

#pragma endregion

#pragma region MemberFunctions

		Matrix4 RotationMatrix() const;

		float Length();

		Quaternion Normalized();

		Quaternion Conjugate();

		float Dot(const Quaternion &a);

		Quaternion NLerp(const Quaternion &target, const float &delta, const bool &shortest);

		Quaternion SLerp(const Quaternion &target, const float &delta, const bool &shortest);

		Vector3 Forward() const;

		Vector3 Back() const;
		
		Vector3 Up() const;

		Vector3 Down() const;

		Vector3 Right() const;

		Vector3 Left() const;

#pragma endregion

	};
	
#pragma region Functions

	Matrix4 RotationMatrix(const Quaternion &a);

	float Length(const Quaternion &a);

	Quaternion Normalized(const Quaternion &a);

	Quaternion Conjugate(const Quaternion &a);

	float Dot(const Quaternion &a, const Quaternion &b);

	Quaternion NLerp(const Quaternion &start, const Quaternion &finish, const float &delta, const bool &shortest);

	Quaternion SLerp(const Quaternion &start, const Quaternion &finish, const float &delta, const bool &shortest);

#pragma endregion

}