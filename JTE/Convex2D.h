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
		struct Ray2D;

		struct CollisionData;

		struct Convex2D { Vector2 verts[32]; size_t size; };

		Convex2D operator*(const Matrix4 &m, const Convex2D &cvex);


		CollisionData iTest_data(const Convex2D &a, const Convex2D &b);

		CollisionData iTest_data(const Convex2D &a, const AABB2D &b);

		CollisionData iTest_data(const Convex2D &a, const Circle &b);

		CollisionData iTest_data(const Convex2D &a, const Plane2D &b);

		CollisionData iTest_data(const Convex2D &a, const Ray2D &b);

	}
}