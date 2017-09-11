#pragma once
#include "Vector3.h"

namespace JTL
{
	struct Matrix4;

	namespace SIM
	{
		struct Sphere;
		struct Plane3D;
		struct Ray3D;
		struct Convex3D;

		struct CollisionData;

		struct AABB3D
		{
			AABB3D(const Vector3 &bl, const Vector3 &tr) : min(bl), max(tr) {};

			Vector3 min, max;

			Vector3 pos() const;
			Vector3 dim() const;
		};

		AABB3D operator*(const Matrix4 &m, const AABB3D &a);

		AABB3D genAABB3D(const Vector3 *pts, const size_t &n);


		bool iTest(const AABB3D &a, const AABB3D &b);

		bool iTest(const AABB3D &a, const Sphere &b);

		bool iTest(const AABB3D &a, const Plane3D &b);

		bool iTest(const AABB3D &a, const Ray3D &b);

		CollisionData iTest_data(const AABB3D &a, const AABB3D &b);

		CollisionData iTest_data(const AABB3D &a, const Sphere &b);

		CollisionData iTest_data(const AABB3D &a, const Plane3D &b);

		CollisionData iTest_data(const AABB3D &a, const Ray3D &b);

		CollisionData iTest_data(const AABB3D &a, const Convex3D &b);
	}
}