#include <algorithm>
#include <cassert>
#include <Math.h>
#include "CollisionData.h"
#include "AABB3D.h"
#include "Sphere.h"
#include "Plane3D.h"
#include "Ray3D.h"
#include "Convex3D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "JTLMath.h"

namespace JTL
{
	namespace SIM
	{
		Sphere	operator*	(const Matrix4 &m, const Sphere &a)
		{
			Sphere r;
			r.radius = fmaxf(fmaxf(Length(m*Vector4{ a.radius,0,0,0 }),
				Length(m*Vector4{ 0,a.radius,0,0 })), Length(m*Vector4{0,0,a.radius,0}));

			r.position = (m * Vector4{ a.position.x, a.position.y, a.position.z, 1 }).xyz;
			return r;
		}

#pragma region CollisionFunctions

		bool	iTest(const Sphere &ac, const Sphere &bc)
		{
			return sqrtf((bc.position.x - ac.position.x) * (bc.position.x - ac.position.x)
				+ (bc.position.y - ac.position.y) * (bc.position.y - ac.position.y)
				+ (bc.position.z - ac.position.z) * (bc.position.z - ac.position.z))
				<= (ac.radius + bc.radius);
		}

		bool	iTest(const Sphere &ac, const AABB3D &bc)
		{
			return iTest(Sphere{ Clamp(ac.position, bc.min, bc.max) , 0 }, ac);
		}

		bool	iTest(const Sphere &ac, const Plane3D &bc)
		{
			return bc.normal.x * (ac.position.x - bc.position.x) <= ac.radius &&
				bc.normal.y * (ac.position.y - bc.position.y) <= ac.radius &&
				bc.normal.z * (ac.position.z - bc.position.z) <= ac.radius;
		}

		bool	iTest(const Sphere &ac, const Ray3D &bc)
		{
			Vector3 pc = bc.position + bc.direction * fltClamp(Dot((ac.position - bc.position), bc.direction), 0, bc.length);
			return Dot(ac.position - pc, ac.position - pc)
				<= (ac.radius * ac.radius);
		}

		CollisionData iTest_data(const Sphere &ac, const Sphere &bc)
		{
			if (iTest(ac, bc))
			{
				Vector3 nNormal = -Normalized(bc.position - ac.position);
				return CollisionData{ (ac.radius + bc.radius) - (Length(ac.position - bc.position)),
				{ nNormal.x, nNormal.y, 0 } };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Sphere &ac, const AABB3D &bc)
		{
			if (iTest(bc, ac))
			{
					Vector3 aVerts[8] = { bc.min, {bc.min.x, bc.min.y, bc.max.z}, {bc.max.x, bc.min.y, bc.max.z}, {bc.max.x, bc.min.y, bc.min.z},
										  bc.max, {bc.min.x, bc.max.y, bc.max.z}, {bc.max.x, bc.max.y, bc.max.z}, {bc.max.x, bc.max.y, bc.min.z}};

				unsigned cubeIdcs[36] = { 0,1,2,1,3,2,
									  	  5,2,1,6,2,5,
										  2,6,7,7,3,2,
										  0,4,3,7,3,4,
										  0,4,2,5,2,4,
										  4,5,6,5,7,6 };

				Convex3D a(aVerts, cubeIdcs, 8, 36);

				return iTest_data(a, ac);
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Sphere &ac, const Plane3D &bc)
		{
			if (iTest(ac, bc))
			{
				return CollisionData{ fmaxf(fmaxf(bc.normal.x * (ac.position.x - bc.position.x) + ac.radius,
												  bc.normal.y * (ac.position.y - bc.position.y) + ac.radius),
												  bc.normal.z * (ac.position.z - bc.position.z) + ac.radius),{ bc.normal.x, bc.normal.y, bc.normal.z } };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Sphere &ac, const Ray3D &bc)
		{
			if (iTest(ac, bc))
			{
				Vector3 pc = bc.position + bc.direction * fltClamp(Dot((ac.position - bc.position), bc.direction), 0, bc.length);
				Vector3 bcperp = Cross(bc.direction, Normalized(ac.position - bc.position));
				return CollisionData{ Dot(pc - bc.position, pc - bc.position) + (ac.radius * ac.radius),{ bcperp.x, bcperp.y, 0 } };
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const Sphere &ac, const Convex3D &bc)
		{
			return iTest_data(bc, ac);
		}
	}
}