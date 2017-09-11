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
		Plane3D	operator*	(const Matrix4 &m, const Plane3D &a)
		{
			Vector4 np = { a.position.x, a.position.y, a.position.z, 1 };
			Vector4 nr = { a.normal.x  , a.normal.y  , a.normal.z   };
			np = (m * np);
			nr = (m * nr);
			return Plane3D{ np.xyz, Normalized(nr.xyz) };
		}

#pragma region ShapeFunctions

		bool iTest(const Plane3D &ac, const AABB3D &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Plane3D &ac, const Sphere &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Plane3D &ac, const Ray3D &bc)
		{
			return iTest(bc, ac);
		}

		CollisionData iTest_data(const Plane3D &ac, const AABB3D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane3D &ac, const Sphere &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane3D &ac, const Ray3D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane3D &ac, const Convex3D &bc)
		{
			return iTest_data(bc, ac);
		}

#pragma endregion
	}
}