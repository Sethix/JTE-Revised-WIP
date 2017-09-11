#pragma once
#include "Vector2.h"

namespace JTL
{

	struct Matrix3;
	struct Matrix4;

	namespace SIM
	{
		struct Circle;
		struct Plane2D;
		struct Ray2D;
		struct Convex2D;
	
		struct CollisionData;

		struct AABB2D
		{
			AABB2D(const Vector2 &bl, const Vector2 &tr) : min(bl), max(tr) {};
			
			Vector2 min, max;

			Vector2 pos() const;
			Vector2 dim() const;
		};

		AABB2D operator*(const Matrix4 &m, const AABB2D &a);

		AABB2D genAABB2D(const Vector2 *pts, const size_t &n);

		AABB2D rotate(const AABB2D &aabb, const float &angle);


		bool iTest(const AABB2D &a, const AABB2D &b);

		bool iTest(const AABB2D &a, const Circle &b);

		bool iTest(const AABB2D &a, const Plane2D &b);

		bool iTest(const AABB2D &a, const Ray2D &b);

		CollisionData iTest_data(const AABB2D &a, const AABB2D &b);

		CollisionData iTest_data(const AABB2D &a, const Circle &b);

		CollisionData iTest_data(const AABB2D &a, const Plane2D &b);

		CollisionData iTest_data(const AABB2D &a, const Ray2D &b);

		CollisionData iTest_data(const AABB2D &a, const Convex2D &b);
	}
}