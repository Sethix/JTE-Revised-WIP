#include <cassert>
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Math.h"
#include "JTLMath.h"
#include <cmath>

namespace JTL
{

#pragma region BinaryOperators

	Matrix4& Matrix4::operator += (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			m[0] + rhs.m[0],  m[1] + rhs.m[1] ,  m[2] + rhs.m[2] ,  m[3] + rhs.m[3]  ,
			m[4] + rhs.m[4],  m[5] + rhs.m[5] ,  m[6] + rhs.m[6] ,  m[7] + rhs.m[7]  ,
			m[8] + rhs.m[8],  m[9] + rhs.m[9] ,  m[10] + rhs.m[10],  m[11] + rhs.m[11] ,
			m[12] + rhs.m[12], m[13] + rhs.m[13],  m[14] + rhs.m[14],  m[15] + rhs.m[15] };
	}

	Matrix4& Matrix4::operator -= (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			m[0] - rhs.m[0] ,  m[1] - rhs.m[1] ,  m[2] - rhs.m[2] ,  m[3] - rhs.m[3]  ,
			m[4] - rhs.m[4] ,  m[5] - rhs.m[5] ,  m[6] - rhs.m[6] ,  m[7] - rhs.m[7]  ,
			m[8] - rhs.m[8] ,  m[9] - rhs.m[9] ,  m[10] - rhs.m[10],  m[11] - rhs.m[11] ,
			m[12] - rhs.m[12],  m[13] - rhs.m[13],  m[14] - rhs.m[14],  m[15] - rhs.m[15] };
	}

	Matrix4& Matrix4::operator *= (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0] + mm[0][2] * rhs.mm[2][0] + mm[0][3] * rhs.mm[3][0],
			mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1] + mm[0][2] * rhs.mm[2][1] + mm[0][3] * rhs.mm[3][1],
			mm[0][0] * rhs.mm[0][2] + mm[0][1] * rhs.mm[1][2] + mm[0][2] * rhs.mm[2][2] + mm[0][3] * rhs.mm[3][2],
			mm[0][0] * rhs.mm[0][3] + mm[0][1] * rhs.mm[1][3] + mm[0][2] * rhs.mm[2][3] + mm[0][3] * rhs.mm[3][3],

			mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0] + mm[1][2] * rhs.mm[2][0] + mm[1][3] * rhs.mm[3][0],
			mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] + mm[1][2] * rhs.mm[2][1] + mm[1][3] * rhs.mm[3][1],
			mm[1][0] * rhs.mm[0][2] + mm[1][1] * rhs.mm[1][2] + mm[1][2] * rhs.mm[2][2] + mm[1][3] * rhs.mm[3][2],
			mm[1][0] * rhs.mm[0][3] + mm[1][1] * rhs.mm[1][3] + mm[1][2] * rhs.mm[2][3] + mm[1][3] * rhs.mm[3][3],

			mm[2][0] * rhs.mm[0][0] + mm[2][1] * rhs.mm[1][0] + mm[2][2] * rhs.mm[2][0] + mm[2][3] * rhs.mm[3][0],
			mm[2][0] * rhs.mm[0][1] + mm[2][1] * rhs.mm[1][1] + mm[2][2] * rhs.mm[2][1] + mm[2][3] * rhs.mm[3][1],
			mm[2][0] * rhs.mm[0][2] + mm[2][1] * rhs.mm[1][2] + mm[2][2] * rhs.mm[2][2] + mm[2][3] * rhs.mm[3][2],
			mm[2][0] * rhs.mm[0][3] + mm[2][1] * rhs.mm[1][3] + mm[2][2] * rhs.mm[2][3] + mm[2][3] * rhs.mm[3][3],

			mm[3][0] * rhs.mm[0][0] + mm[3][1] * rhs.mm[1][0] + mm[3][2] * rhs.mm[2][0] + mm[3][3] * rhs.mm[3][0],
			mm[3][0] * rhs.mm[0][1] + mm[3][1] * rhs.mm[1][1] + mm[3][2] * rhs.mm[2][1] + mm[3][3] * rhs.mm[3][1],
			mm[3][0] * rhs.mm[0][2] + mm[3][1] * rhs.mm[1][2] + mm[3][2] * rhs.mm[2][2] + mm[3][3] * rhs.mm[3][2],
			mm[3][0] * rhs.mm[0][3] + mm[3][1] * rhs.mm[1][3] + mm[3][2] * rhs.mm[2][3] + mm[3][3] * rhs.mm[3][3]

		};
	}


	Matrix4  Matrix4::operator +  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result += rhs;
		return result;
	}

	Matrix4  Matrix4::operator -  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result -= rhs;
		return result;
	}

	Matrix4  Matrix4::operator *  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result *= rhs;
		return result;
	}

	Vector4  Matrix4::operator *  (const Vector4 &rhs) const
	{
		return Vector4{ m[0] * m[1] * m[2] * m[3] * rhs.x,
			m[4] * m[5] * m[6] * m[7] * rhs.y,
			m[8] * m[9] * m[10] * m[11] * rhs.z,
			m[12] * m[13] * m[14] * m[15] * rhs.w, };
	}


	bool     Matrix4::operator == (const Matrix4 &rhs) const
	{
		return m[0] == rhs.m[0], m[1] == rhs.m[1], m[2] == rhs.m[2], m[3] == rhs.m[3],
			m[4] == rhs.m[4], m[5] == rhs.m[5], m[6] == rhs.m[6], m[7] == rhs.m[7],
			m[8] == rhs.m[8], m[9] == rhs.m[9], m[10] == rhs.m[10], m[11] == rhs.m[11],
			m[12] == rhs.m[12], m[13] == rhs.m[13], m[14] == rhs.m[14], m[15] == rhs.m[15];
	}

#pragma endregion

#pragma region Functions

	float   Determinant(const Matrix4 &a)
	{
		return{ a.mm[0][3] * a.mm[1][2] * a.mm[2][1] * a.mm[3][0] - a.mm[0][2] * a.mm[1][3] * a.mm[2][1] * a.mm[3][0] -
			a.mm[0][3] * a.mm[1][1] * a.mm[2][2] * a.mm[3][0] + a.mm[0][1] * a.mm[1][3] * a.mm[2][2] * a.mm[3][0] +
			a.mm[0][2] * a.mm[1][1] * a.mm[2][3] * a.mm[3][0] - a.mm[0][1] * a.mm[1][2] * a.mm[2][3] * a.mm[3][0] -
			a.mm[0][3] * a.mm[1][2] * a.mm[2][0] * a.mm[3][1] + a.mm[0][2] * a.mm[1][3] * a.mm[2][0] * a.mm[3][1] +
			a.mm[0][3] * a.mm[1][0] * a.mm[2][2] * a.mm[3][1] - a.mm[0][0] * a.mm[1][3] * a.mm[2][2] * a.mm[3][1] -
			a.mm[0][2] * a.mm[1][0] * a.mm[2][3] * a.mm[3][1] + a.mm[0][0] * a.mm[1][2] * a.mm[2][3] * a.mm[3][1] +
			a.mm[0][3] * a.mm[1][1] * a.mm[2][0] * a.mm[3][2] - a.mm[0][1] * a.mm[1][3] * a.mm[2][0] * a.mm[3][2] -
			a.mm[0][3] * a.mm[1][0] * a.mm[2][1] * a.mm[3][2] + a.mm[0][0] * a.mm[1][3] * a.mm[2][1] * a.mm[3][2] +
			a.mm[0][1] * a.mm[1][0] * a.mm[2][3] * a.mm[3][2] - a.mm[0][0] * a.mm[1][1] * a.mm[2][3] * a.mm[3][2] -
			a.mm[0][2] * a.mm[1][1] * a.mm[2][0] * a.mm[3][3] + a.mm[0][1] * a.mm[1][2] * a.mm[2][0] * a.mm[3][3] +
			a.mm[0][2] * a.mm[1][0] * a.mm[2][1] * a.mm[3][3] - a.mm[0][0] * a.mm[1][2] * a.mm[2][1] * a.mm[3][3] -
			a.mm[0][1] * a.mm[1][0] * a.mm[2][2] * a.mm[3][3] + a.mm[0][0] * a.mm[1][1] * a.mm[2][2] * a.mm[3][3] };
	}

	Matrix4 Inverse(const Matrix4 &a)
	{
		float d = 1 / Determinant(a);

		assert(d != 0);

		return  Matrix4{ (a.m[5] * a.m[10] * a.m[15] - a.m[5] * a.m[11] * a.m[14] - a.m[9] * a.m[6] * a.m[15] +
			a.m[9] * a.m[7] * a.m[14] + a.m[13] * a.m[6] * a.m[11] - a.m[13] * a.m[7] * a.m[10]) * d ,

			(-a.m[1] * a.m[10] * a.m[15] + a.m[1] * a.m[11] * a.m[14] + a.m[9] * a.m[2] * a.m[15] -
				a.m[9] * a.m[3] * a.m[14] - a.m[13] * a.m[2] * a.m[11] + a.m[13] * a.m[3] * a.m[10]) * d ,

				(a.m[1] * a.m[6] * a.m[15] - a.m[1] * a.m[7] * a.m[14] - a.m[5] * a.m[2] * a.m[15] +
					a.m[5] * a.m[3] * a.m[14] + a.m[13] * a.m[2] * a.m[7] - a.m[13] * a.m[3] * a.m[6]) * d ,

					(-a.m[1] * a.m[6] * a.m[11] + a.m[1] * a.m[7] * a.m[10] + a.m[5] * a.m[2] * a.m[11] -
						a.m[5] * a.m[3] * a.m[10] - a.m[9] * a.m[2] * a.m[7] + a.m[9] * a.m[3] * a.m[6]) * d ,


						(-a.m[4] * a.m[10] * a.m[15] + a.m[4] * a.m[11] * a.m[14] + a.m[8] * a.m[6] * a.m[15] -
							a.m[8] * a.m[7] * a.m[14] - a.m[12] * a.m[6] * a.m[11] + a.m[12] * a.m[7] * a.m[10]) * d ,

							(a.m[0] * a.m[10] * a.m[15] - a.m[0] * a.m[11] * a.m[14] - a.m[8] * a.m[2] * a.m[15] +
								a.m[8] * a.m[3] * a.m[14] + a.m[12] * a.m[2] * a.m[11] - a.m[12] * a.m[3] * a.m[10]) * d ,

								(-a.m[0] * a.m[6] * a.m[15] + a.m[0] * a.m[7] * a.m[14] + a.m[4] * a.m[2] * a.m[15] -
									a.m[4] * a.m[3] * a.m[14] - a.m[12] * a.m[2] * a.m[7] + a.m[12] * a.m[3] * a.m[6]) * d ,

									(a.m[0] * a.m[6] * a.m[11] - a.m[0] * a.m[7] * a.m[10] - a.m[4] * a.m[2] * a.m[11] +
										a.m[4] * a.m[3] * a.m[10] + a.m[8] * a.m[2] * a.m[7] - a.m[8] * a.m[3] * a.m[6]) * d ,


										(a.m[4] * a.m[9] * a.m[15] - a.m[4] * a.m[11] * a.m[13] - a.m[8] * a.m[5] * a.m[15] +
											a.m[8] * a.m[7] * a.m[13] + a.m[12] * a.m[5] * a.m[11] - a.m[12] * a.m[7] * a.m[9]) * d ,

											(-a.m[0] * a.m[9] * a.m[15] + a.m[0] * a.m[11] * a.m[13] + a.m[8] * a.m[1] * a.m[15] -
												a.m[8] * a.m[3] * a.m[13] - a.m[12] * a.m[1] * a.m[11] + a.m[12] * a.m[3] * a.m[9]) * d ,

												(a.m[0] * a.m[5] * a.m[15] - a.m[0] * a.m[7] * a.m[13] - a.m[4] * a.m[1] * a.m[15] +
													a.m[4] * a.m[3] * a.m[13] + a.m[12] * a.m[1] * a.m[7] - a.m[12] * a.m[3] * a.m[5]) * d ,

													(-a.m[0] * a.m[5] * a.m[11] + a.m[0] * a.m[7] * a.m[9] + a.m[4] * a.m[1] * a.m[11] -
														a.m[4] * a.m[3] * a.m[9] - a.m[8] * a.m[1] * a.m[7] + a.m[8] * a.m[3] * a.m[5]) * d ,


														(-a.m[4] * a.m[9] * a.m[14] + a.m[4] * a.m[10] * a.m[13] + a.m[8] * a.m[5] * a.m[14] -
															a.m[8] * a.m[6] * a.m[13] - a.m[12] * a.m[5] * a.m[10] + a.m[12] * a.m[6] * a.m[9]) * d ,

															(a.m[0] * a.m[9] * a.m[14] - a.m[0] * a.m[10] * a.m[13] - a.m[8] * a.m[1] * a.m[14] +
																a.m[8] * a.m[2] * a.m[13] + a.m[12] * a.m[1] * a.m[10] - a.m[12] * a.m[2] * a.m[9]) * d ,

																(-a.m[0] * a.m[5] * a.m[14] + a.m[0] * a.m[6] * a.m[13] + a.m[4] * a.m[1] * a.m[14] -
																	a.m[4] * a.m[2] * a.m[13] - a.m[12] * a.m[1] * a.m[6] + a.m[12] * a.m[2] * a.m[5]) * d ,

																	(a.m[0] * a.m[5] * a.m[10] - a.m[0] * a.m[6] * a.m[9] - a.m[4] * a.m[1] * a.m[10] +
																		a.m[4] * a.m[2] * a.m[9] + a.m[8] * a.m[1] * a.m[6] - a.m[8] * a.m[2] * a.m[5]) * d };
	}

	Matrix4 Transpose(const Matrix4 &a)
	{
		return Matrix4{ a.mm[0][0], a.mm[1][0], a.mm[2][0], a.mm[3][0] ,
			a.mm[0][1], a.mm[1][1], a.mm[2][1], a.mm[3][1] ,
			a.mm[0][2], a.mm[1][2], a.mm[2][2], a.mm[3][2] ,
			a.mm[0][3], a.mm[1][3], a.mm[2][3], a.mm[3][3] };
	}

	Matrix4 Matrix3To4(const Matrix3 &a)
	{
		return Matrix4{ a.m[0],a.m[1], 0, a.m[2],
			a.m[3],a.m[4], 0, a.m[5],
			0 ,    0 ,     1 ,0,
			a.m[6],a.m[7], 0, a.m[8] };
	}

#pragma region Transformation

	Matrix4 Rotation(const Vector3 & a)
	{
		Vector3 r = a;

		r.x = DEG2RAD(r.x);
		r.y = DEG2RAD(r.y);
		r.z = DEG2RAD(r.z);

		Matrix4 xRot = { 1,0,0,0,
			0,cos(r.x),-sin(r.x),0,
			0,sin(r.x),cos(r.x),0,
			0,0,0,1 };

		Matrix4 yRot = { cos(r.y),0,-sin(r.y),0,
			0,1,0,0,
			sin(r.y), 0, cos(r.y), 0,
			0, 0, 0, 1 };

		Matrix4 zRot = { cos(r.z),-sin(r.z),0,0,
			sin(r.z),cos(r.z),0,0,
			0,0,1,0,
			0,0,0,1 };

		return zRot * yRot * xRot;
	}

	Matrix4 Rotation(const Vector3 & f, const Vector3 &u)
	{
		Vector3 fwd = Normalized(f);
		Vector3 rgt = Normalized(u);
		rgt = Cross(rgt, fwd);

		Vector3 up = Cross(fwd, rgt);

		return Rotation(fwd, up, rgt);
	}

	Matrix4 Rotation(const Vector3 &f, const Vector3 &u, const Vector3 &r)
	{
		return{ r.x, r.y, r.z, 0,
			u.x, u.y, u.z, 0,
			f.x, f.y, f.z, 0,
			0  , 0  , 0  , 1 };
	}

	Matrix4 Scale(const Vector3 & a)
	{
		return{ a.x,0,0,0,
			0,a.y,0,0,
			0,0,a.z,0,
			0,0,0,1 };
	}

	Matrix4 Translation(const Vector3 & a)
	{
		return{ 1,0,0,a.x,
			0,1,0,a.y,
			0,0,1,a.z,
			0,0,0,1 };
	}

#pragma endregion

#pragma region Projection

	Matrix4 OrthographicProjection(const float &l, const float &r, const float &b, const float &t, const float &n, const float &f)
	{
		return Matrix4{ 2 / (r - l), 0, 0,  0,
			0, 2 / (t - b), 0,  0,
			0, 0, -2 / (f - n), 0,
			-((r + l) / (r - l)), -((t + b) / (t / b)), -((f + n) / (f - n)), 1 };
	}

	Matrix4 PerspectiveProjection(const float &w, const float &h, const float &fov, const float &n, const float &f)
	{
		float aspect = w / h;
		float top = tan(fov * 0.5f) * n;
		float bot = -top;
		float rgt = top * aspect;
		float lft = -rgt;

		return Matrix4{ n * 2 / (rgt - lft), 0, (rgt + lft) / (rgt - lft),0,
			0, n * 2 / (top - bot), (top + bot) / (top - bot),0,
			0, 0, -((f + n) / (f - n)), -(2 * f*n / (f - n)),
			0,0,-1,0 };
	}

#pragma endregion

#pragma endregion

}