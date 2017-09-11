#include <algorithm>
#include <cassert>
#include <Math.h>
#include "CollisionData.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Plane2D.h"
#include "Ray2D.h"
#include "Convex2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "JTLMath.h"

namespace JTL
{
	namespace SIM
	{
		Circle	operator*	(const Matrix4 &m, const Circle &a)
		{
			Circle r;
			r.radius = fmaxf(Length(m*Vector4{ a.radius,0,0 }),
				Length(m*Vector4{ 0,a.radius,0 }));

			r.position = (m * Vector4{ a.position.x, a.position.y, 0, 1 }).xyz.xy;
			return r;
		}

#pragma region CollisionFunctions

		bool	iTest(const Circle &ac, const Circle &bc)
		{
			return sqrtf((bc.position.x - ac.position.x) * (bc.position.x - ac.position.x)
				+ (bc.position.y - ac.position.y) * (bc.position.y - ac.position.y))
				<= (ac.radius + bc.radius);
		}

		bool	iTest(const Circle &ac, const AABB2D &bc)
		{
			return iTest(Circle{ Clamp(ac.position, bc.min, bc.max) , 0 }, ac);
		}

		bool	iTest(const Circle &ac, const Plane2D &bc)
		{
			return bc.normal.x * (ac.position.x - bc.position.x) <= ac.radius &&
				bc.normal.y * (ac.position.y - bc.position.y) <= ac.radius;
		}

		bool	iTest(const Circle &ac, const Ray2D &bc)
		{
			Vector2 pc = bc.position + bc.direction * fltClamp(Dot((ac.position - bc.position), bc.direction), 0, bc.length);
			return Dot(ac.position - pc, ac.position - pc)
				<= (ac.radius * ac.radius);
		}

		CollisionData iTest_data(const Circle &ac, const Circle &bc)
		{
			if (iTest(ac, bc))
			{
				Vector2 nNormal = -Normalized(bc.position - ac.position);
				return CollisionData{ (ac.radius + bc.radius) - (Length(ac.position - bc.position)),
				{nNormal.x, nNormal.y, 0} };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Circle &ac, const AABB2D &bc)
		{
			if (iTest(bc, ac))
			{
				Convex2D a;

				a.size = 4;

				a.verts[0] = bc.min;
				a.verts[1] = Vector2{ bc.min.x, bc.max.y } +E_VEC2;
				a.verts[2] = bc.max;
				a.verts[3] = Vector2{ bc.max.x, bc.min.y };

				return iTest_data(a, ac);
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Circle &ac, const Plane2D &bc)
		{
			if (iTest(ac, bc))
			{
				return CollisionData{ fmaxf(bc.normal.x * (ac.position.x - bc.position.x) + ac.radius,
					bc.normal.y * (ac.position.y - bc.position.y) + ac.radius), {bc.normal.x, bc.normal.y, 0} };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Circle &ac, const Ray2D &bc)
		{
			if (iTest(ac, bc))
			{
				Vector2 pc = bc.position + bc.direction * fltClamp(Dot((ac.position - bc.position), bc.direction), 0, bc.length);
				Vector2 bcperp = Perpendicular(bc.direction);
				return CollisionData{ Dot(pc - bc.position, pc - bc.position) + (ac.radius * ac.radius), {bcperp.x, bcperp.y, 0} };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Circle &ac, const Convex2D &bc)
		{
			return iTest_data(bc, ac);
		}
	}
}