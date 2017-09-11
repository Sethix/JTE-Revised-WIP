#pragma once
#include "Vector3.h"

namespace JTL
{
	struct Matrix4;

	namespace SIM
	{
		struct AABB3D;
		struct Plane3D;
		struct Ray3D;
		struct Convex3D;

		struct CollisionData;

		struct Sphere { Vector3 position; float radius; };

		Sphere operator*(const Matrix4 &m, const Sphere &s);


		bool iTest(const Sphere &a, const Sphere &b);

		bool iTest(const Sphere &a, const AABB3D &b);

		bool iTest(const Sphere &a, const Plane3D &b);

		bool iTest(const Sphere &a, const Ray3D &b);

		CollisionData iTest_data(const Sphere &a, const Sphere &b);

		CollisionData iTest_data(const Sphere &a, const AABB3D &b);

		CollisionData iTest_data(const Sphere &a, const Plane3D &b);

		CollisionData iTest_data(const Sphere &a, const Ray3D &b);

		CollisionData iTest_data(const Sphere &a, const Convex3D &b);
	}
}