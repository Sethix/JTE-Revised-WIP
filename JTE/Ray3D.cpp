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
		Ray3D	operator*	(const Matrix4 &m, const Ray3D &a)
		{
			Vector4 np = { a.position.x , a.position.y , a.position.z , 1 };
			Vector4 nr = { a.direction.x, a.direction.y, a.direction.z, 0 };
			np = (m * np);
			nr = (m * nr);
			return Ray3D{ np.xyz, Normalized(nr.xyz), a.length * (Length(np.xyz) - Length(a.position)) };
		}

#pragma region ShapeFunctions

		bool iTest(const Ray3D &ac, const AABB3D &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Ray3D &ac, const Sphere &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Ray3D &ac, const Plane3D &bc)
		{
			float r = Dot(bc.normal, (ac.position - bc.position)) / -(Dot(bc.normal, ac.direction));
			return 0 <= r && r <= ac.length && -(Dot(bc.normal, ac.direction)) > 0;
		}

		CollisionData iTest_data(const Ray3D &ac, const AABB3D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Ray3D &ac, const Sphere &bc)
		{
			return iTest_data(ac, bc);
		}

		CollisionData iTest_data(const Ray3D &ac, const Plane3D &bc)
		{
			CollisionData cd = { 0 };
			float r = (Dot(bc.normal, (ac.position - bc.position) / -(Dot(bc.normal, ac.direction))));
			Vector3 np = Cross(ac.direction, bc.normal);
			if (r <= 0 && r <= ac.length) cd = { r,{ np.x, np.y, 0 } };
			return cd;
		}

		CollisionData iTest_data(const Ray3D &ac, const Convex3D &bc)
		{
			return iTest_data(bc, ac);
		}

#pragma endregion
	}
}