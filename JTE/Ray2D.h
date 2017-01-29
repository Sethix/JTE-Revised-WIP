#pragma once
#include "Vector2.h"

namespace JTL
{

	struct Matrix3;

	namespace SIM
	{
		struct AABB2D;
		struct Circle;
		struct Plane2D;
		struct Convex2D;

		struct CollisionData;

		struct Ray2D { Vector2 position, direction; float length; };

		Ray2D operator*(const Matrix4 &m, const Ray2D &r);


		bool iTest(const Ray2D &a, const AABB2D &b);

		bool iTest(const Ray2D &a, const Circle &b);

		bool iTest(const Ray2D &a, const Plane2D &b);

		CollisionData iTest_data(const Ray2D &a, const AABB2D &b);

		CollisionData iTest_data(const Ray2D &a, const Circle &b);

		CollisionData iTest_data(const Ray2D &a, const Plane2D &b);

		CollisionData iTest_data(const Ray2D &a, const Convex2D &b);
	}
}