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
		Ray2D	operator*	(const Matrix4 &m, const Ray2D &a)
		{
			Vector4 np = { a.position.x, a.position.y, 0, 1 };
			Vector4 nr = { a.direction.x  , a.direction.y  ,0 , 0 };
			np = (m * np);
			nr = (m * nr);
			return Ray2D{ np.xyz.xy, Normalized(nr.xyz.xy), a.length * (Length(np.xyz.xy) - Length(a.position)) };
		}

#pragma region ShapeFunctions

		bool iTest(const Ray2D &ac, const AABB2D &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Ray2D &ac, const Circle &bc)
		{
			return iTest(bc, ac);
		}

		bool iTest(const Ray2D &ac, const Plane2D &bc)
		{
			float r = Dot(bc.normal, (ac.position - bc.position)) / -(Dot(bc.normal, ac.direction));
			return 0 <= r && r <= ac.length && -(Dot(bc.normal, ac.direction)) > 0;
		}

		CollisionData iTest_data(const Ray2D &ac, const AABB2D &bc)
		{
			return iTest_data(bc, ac);
		}

		CollisionData iTest_data(const Ray2D &ac, const Circle &bc)
		{
			return iTest_data(ac, bc);
		}

		CollisionData iTest_data(const Ray2D &ac, const Plane2D &bc)
		{
			CollisionData cd = { 0 };
			float r = Length(bc.normal * (ac.position - bc.position) / -(bc.normal * ac.direction));
			Vector2 np = Perpendicular(bc.normal);
			if (r <= 0 && r <= ac.length) cd = { r, {np.x, np.y, 0} };
			return cd;
		}

		CollisionData iTest_data(const Ray2D &ac, const Convex2D &bc)
		{
			return iTest_data(bc, ac);
		}

#pragma endregion
	}
}