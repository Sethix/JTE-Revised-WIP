#pragma once
#include "Vector2.h"

namespace JTL
{
	struct Matrix3;

	namespace SIM
	{
		struct AABB2D;
		struct Circle;
		struct Ray2D;
		struct Convex2D;

		struct CollisionData;

		struct Plane2D { Vector2 position, normal; };

		Plane2D operator*(const Matrix4 &m, const Plane2D &p);


		bool iTest(const Plane2D &a, const AABB2D &b);

		bool iTest(const Plane2D &a, const Circle &b);

		bool iTest(const Plane2D &a, const Ray2D &b);

		CollisionData iTest_data(const Plane2D &a, const AABB2D &b);

		CollisionData iTest_data(const Plane2D &a, const Circle &b);

		CollisionData iTest_data(const Plane2D &a, const Ray2D &b);

		CollisionData iTest_data(const Plane2D &a, const Convex2D &b);
	}
}