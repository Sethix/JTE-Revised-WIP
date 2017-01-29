#pragma once
#include "Vector3.h"

namespace JTL
{
	struct Matrix4;

	namespace SIM
	{
		struct AABB3D;
		struct Sphere;
		struct Plane3D;
		struct Convex3D;

		struct CollisionData;

		struct Ray3D { Vector3 position, direction; float length; };

		Ray3D operator*(const Matrix4 &m, const Ray3D &r);


		bool iTest(const Ray3D &a, const AABB3D &b);

		bool iTest(const Ray3D &a, const Sphere &b);

		bool iTest(const Ray3D &a, const Plane3D &b);

		CollisionData iTest_data(const Ray3D &a, const AABB3D &b);

		CollisionData iTest_data(const Ray3D &a, const Sphere &b);

		CollisionData iTest_data(const Ray3D &a, const Plane3D &b);

		CollisionData iTest_data(const Ray3D &a, const Convex3D &b);
	}
}