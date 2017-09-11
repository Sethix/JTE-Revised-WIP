#include "Quaternion.h"
#include "Matrix4.h"
#include <algorithm>
#include <cmath>

namespace JTL
{

#pragma region Constructors

	Quaternion::Quaternion() { x = 0; y = 0; z = 0; w = 1; };

	Quaternion::Quaternion(const float &_x, const float &_y, const float &_z, const float &_w)
	{ x = _x; y = _y; z = _z; w = _w; }

	Quaternion::Quaternion(const Vector3 &axis, const float &angle)
	{
		float shAngle = sinf(angle * 0.5f);
		float chAngle = cosf(angle * 0.5f);

		x = axis.x * shAngle;
		y = axis.y * shAngle;
		z = axis.z * shAngle;
		w = chAngle;
	}

	Quaternion::Quaternion(const Matrix4 &m)
	{
		float trace = m.mm[0][0] + m.mm[1][1] + m.mm[2][2];

		if (trace > 0)
		{
			float s = 0.5f / sqrtf(trace + 1);
			x = (m.mm[1][2] - m.mm[2][1]) * s;
			y = (m.mm[2][0] - m.mm[0][2]) * s;
			z = (m.mm[0][1] - m.mm[1][0]) * s;
			w = 0.25f / s;
		}
		else
		{
			if(m.mm[0][0] > m.mm[1][1] && m.mm[0][0] > m.mm[2][2])
			{
				float s = 2 * sqrtf(1 + m.mm[0][0] - m.mm[1][1] - m.mm[2][2]);
				w = (m.mm[1][2] - m.mm[2][1]) * s;
				z = (m.mm[2][0] + m.mm[0][2]) * s;
				y = (m.mm[1][0] + m.mm[0][1]) * s;
				x = 0.25f / s;
			}
			else if (m.mm[1][1] > m.mm[2][2])
			{
				float s = 2 * sqrtf(1 + m.mm[1][1] - m.mm[0][0] - m.mm[2][2]);
				z = (m.mm[2][1] + m.mm[1][2]) * s;
				w = (m.mm[2][0] - m.mm[0][2]) * s;
				x = (m.mm[1][0] + m.mm[0][1]) * s;
				y = 0.25f / s;
			}
			else
			{
				float s = 2 * sqrtf(1 + m.mm[2][2] - m.mm[0][0] - m.mm[1][1]);
				w = (m.mm[0][1] - m.mm[1][0]) * s;
				x = (m.mm[2][0] + m.mm[0][2]) * s;
				y = (m.mm[1][2] + m.mm[2][1]) * s;
				z = 0.25f / s;
			}
		}

		float len = sqrtf(x * x + y * y + z * z + w * w);
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}

#pragma endregion

#pragma region BinaryOperators

	Quaternion& Quaternion:: operator+= (const Quaternion &rhs)
	{ return *this = Quaternion{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.z }; }

	Quaternion& Quaternion:: operator-= (const Quaternion &rhs)
	{ return *this = Quaternion{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.z }; }

	Quaternion& Quaternion:: operator*= (const float	  &rhs)
	{ return *this = Quaternion{ x * rhs, y * rhs, z * rhs, w * rhs }; }

	Quaternion& Quaternion:: operator*= (const Vector3	  &rhs)
	{
		return *this = Quaternion
		{
			w * rhs.x + y * rhs.z + z * rhs.y,
			w * rhs.y + z * rhs.x + x * rhs.z,
			w * rhs.z + x * rhs.y + y * rhs.x,
			x * rhs.x - y * rhs.y - z * rhs.z
		};
	}

	Quaternion& Quaternion:: operator*= (const Quaternion &rhs)
	{
		return *this = Quaternion
		{
			x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y,
			y * rhs.w + w * rhs.y + z * rhs.x - x * rhs.z,
			z * rhs.w + w * rhs.z + x * rhs.y - y * rhs.x,
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
		};
	}


	Quaternion& Quaternion:: operator+  (const Quaternion &rhs)
	{
		Quaternion result = *this;
		result += rhs;
		return result;
	}

	Quaternion& Quaternion:: operator-  (const Quaternion &rhs)
	{
		Quaternion result = *this;
		result -= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const float	  &rhs)
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const Vector3    &rhs)
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const Quaternion &rhs)
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}


	Quaternion& Quaternion:: operator+  (const Quaternion &rhs) const
	{
		Quaternion result = *this;
		result += rhs;
		return result;
	}

	Quaternion& Quaternion:: operator-  (const Quaternion &rhs) const 
	{
		Quaternion result = *this;
		result -= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const float	  &rhs) const 
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const Vector3    &rhs) const 
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}

	Quaternion& Quaternion:: operator*  (const Quaternion &rhs) const 
	{
		Quaternion result = *this;
		result *= rhs;
		return result;
	}


	bool		Quaternion:: operator== (const Quaternion &rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
			|| (rhs.x < x + FLT_EPSILON && x - FLT_EPSILON < rhs.x &&
				rhs.y < y + FLT_EPSILON && y - FLT_EPSILON < rhs.y &&
				rhs.z < z + FLT_EPSILON && z - FLT_EPSILON < rhs.z &&
				rhs.w < w + FLT_EPSILON && w - FLT_EPSILON < rhs.w);
	}

#pragma endregion

#pragma region UnaryOperators

	Quaternion Quaternion:: operator- () const
	{ return{ -x, -y, -z, -w }; }

#pragma endregion

#pragma region MemberFunctions

	Matrix4 Quaternion::RotationMatrix() const
	{
		Vector3 f = { 2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y) };
		Vector3 u = { 2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x) };
		Vector3 r = { 1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y) };

		return Rotation(f, u, r);
	}

	float Quaternion::Length()
	{ return sqrtf(x * x + y * y + z * z + w * w); }

	Quaternion Quaternion::Normalized()
	{
		float l = Length();

		return Quaternion{ x / l, y / l, z / l, w / l };
	}

	Quaternion Quaternion::Conjugate()
	{ return Quaternion{ -x, -y, -z, w }; }

	float Quaternion::Dot(const Quaternion &a)
	{ return x * a.x + y * a.y + z * a.z + w * a.w; }

	Quaternion Quaternion::NLerp(const Quaternion &target, const float &delta, const bool &shortest)
	{
		Quaternion result = target;

		if (shortest && Dot(target) < 0)
			result = -result;

		return ((result - *this) * delta + *this).Normalized();
	}

	Quaternion Quaternion::SLerp(const Quaternion &target, const float &delta, const bool &shortest)
	{
		Quaternion result = target;
		float c = this->Dot(target);

		if (shortest && c < 0)
		{
			c = -c;
			result = -result;
		}

		if (fabs(c) >= 1 - FLT_EPSILON)
			return NLerp(result, delta, false);

		float s = sqrtf(1 - c * c);
		float angle = atan2f(s, c);
		float invS = 1 / s;

		float sourceDelta = sinf((1 - delta) * angle) * invS;
		float resultDelta = sinf(delta * angle) * invS;

		return (*this * sourceDelta) + (result * resultDelta);
	}

	Vector3 Quaternion::Forward() const
	{ Vector3 rotVec = FWD_VEC3; return rotVec.Rotate(*this); }

	Vector3 Quaternion::Back() const
	{ Vector3 rotVec = BAK_VEC3; return rotVec.Rotate(*this); }

	Vector3 Quaternion::Up() const
	{ Vector3 rotVec = UP_VEC3; return rotVec.Rotate(*this); }

	Vector3 Quaternion::Down() const
	{ Vector3 rotVec = DN_VEC3; return rotVec.Rotate(*this); }

	Vector3 Quaternion::Right() const
	{ Vector3 rotVec = RGT_VEC3; return rotVec.Rotate(*this); }

	Vector3 Quaternion::Left() const
	{ Vector3 rotVec = LFT_VEC3; return rotVec.Rotate(*this); }

#pragma endregion

#pragma region Functions

	Matrix4 RotationMatrix(const Quaternion &a)
	{
		Vector3 f = { 2 * (a.x * a.z - a.w * a.y), 2 * (a.y * a.z + a.w * a.x), 1 - 2 * (a.x * a.x + a.y * a.y) };
		Vector3 u = { 2 * (a.x * a.y + a.w * a.z), 1 - 2 * (a.x * a.x + a.z * a.z), 2 * (a.y * a.z - a.w * a.x) };
		Vector3 r = { 1 - 2 * (a.y * a.y + a.z * a.z), 2 * (a.x * a.y - a.w * a.z), 2 * (a.x * a.z + a.w * a.y) };

		return Rotation(f, u, r);
	}

	float Length(const Quaternion &q)
	{ return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }

	Quaternion Normalized(const Quaternion &q)
	{
		float l = Length(q);

		return Quaternion{ q.x / l, q.y / l, q.z / l, q.w / l };
	}

	Quaternion Conjugate(const Quaternion &q)
	{ return Quaternion{ -q.x, -q.y, -q.z, q.w }; }

	float Dot(const Quaternion &a, const Quaternion &b)
	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	Quaternion NLerp(const Quaternion &start, const Quaternion &finish, const float &delta, const bool &shortest)
	{
		Quaternion result = finish;

		if (shortest && Dot(start, finish) < 0)
			result = -result;

		return ((result - start) * delta + start).Normalized();
	}

	Quaternion SLerp(const Quaternion &start, const Quaternion &finish, const float &delta, const bool &shortest)
	{
		Quaternion result = finish;
		float c = Dot(start, finish);

		if (shortest && c < 0)
		{
			c = -c;
			result = -result;
		}

		if (fabs(c) >= 1 - FLT_EPSILON)
			return NLerp(start, result, delta, false);

		float s = sqrtf(1 - c * c);
		float angle = atan2f(s, c);
		float invS = 1 / s;

		float sourceDelta = sinf((1 - delta) * angle) * invS;
		float resultDelta = sinf(delta * angle) * invS;

		return (start * sourceDelta) + (result * resultDelta);
	}

#pragma endregion

}