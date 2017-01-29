#pragma once
#include "Vector2.h"

namespace JTL
{
	struct Matrix4;

	namespace SIM
	{
		struct AABB3D;
		struct Sphere;
		struct Ray3D;
		struct Convex3D;

		struct CollisionData;

		struct Plane3D { Vector3 position, normal; };

		Plane3D operator*(const Matrix4 &m, const Plane3D &p);


		bool iTest(const Plane3D &a, const AABB3D &b);

		bool iTest(const Plane3D &a, const Sphere &b);

		bool iTest(const Plane3D &a, const Ray3D &b);

		CollisionData iTest_data(const Plane3D &a, const AABB3D &b);

		CollisionData iTest_data(const Plane3D &a, const Sphere &b);

		CollisionData iTest_data(const Plane3D &a, const Ray3D &b);

		CollisionData iTest_data(const Plane3D &a, const Convex3D &b);
	}
}