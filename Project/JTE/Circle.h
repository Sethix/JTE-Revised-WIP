#pragma once
#include "Vector2.h"

namespace JTL
{

	struct Matrix4;

	namespace SIM
	{
		struct AABB2D;
		struct Plane2D;
		struct Ray2D;
		struct Convex2D;

		struct CollisionData;

		struct Circle { Vector2 position; float radius; };
	
		Circle operator*(const Matrix4 &m, const Circle &c);


		bool iTest(const Circle &a, const Circle &b);

		bool iTest(const Circle &a, const AABB2D &b);

		bool iTest(const Circle &a, const Plane2D &b);

		bool iTest(const Circle &a, const Ray2D &b);

		CollisionData iTest_data(const Circle &a, const Circle &b);

		CollisionData iTest_data(const Circle &a, const AABB2D &b);

		CollisionData iTest_data(const Circle &a, const Plane2D &b);

		CollisionData iTest_data(const Circle &a, const Ray2D &b);

		CollisionData iTest_data(const Circle &a, const Convex2D &b);
	}
}