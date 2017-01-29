#include <algorithm>
#include <cassert>
#include <Math.h>
#include "CollisionDetection2D.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Plane2D.h"
#include "Ray2D.h"
#include "Convex2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "JTLMath.h"

namespace JTL
{
	namespace SIM
	{
		Plane2D	operator*	(const Matrix4 &m, const Plane2D &a)
		{
			Vector4 np = { a.position.x, a.position.y, 0, 0 };
			Vector4 nr = { a.normal.x  , a.normal.y  , 0, 0 };
			np = (m * np);
			nr = (m * nr);
			return Plane2D{ np.xyz.xy, Normalized(nr.xyz.xy) };
		}

#pragma region ShapeFunctions

		bool iTest(const Plane2D &ac, const AABB2D &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Plane2D &ac, const Circle &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Plane2D &ac, const Ray2D &bc)
		{
			return iTest(bc, ac);
		}

		CollisionData iTest_data(const Plane2D &ac, const AABB2D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane2D &ac, const Circle &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane2D &ac, const Ray2D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Plane2D &ac, const Convex2D &bc)
		{
			return iTest_data(bc, ac);
		}

#pragma endregion
	}
}