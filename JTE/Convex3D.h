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
		struct Ray3D;

		struct CollisionData;

		struct Convex3D 
		{ 
			Convex3D(Vector3 *v, size_t *i, unsigned int vSize, unsigned int iSize);
			Vector3 *verts; 
			Vector3 *normals; 
			size_t *indices; 
			size_t size; 
		};

		Convex3D operator*(const Matrix4 &m, const Convex3D &cvex);


		CollisionData iTest_data(const Convex3D &a, const Convex3D &b);

		CollisionData iTest_data(const Convex3D &a, const AABB3D &b);

		CollisionData iTest_data(const Convex3D &a, const Sphere &b);

		CollisionData iTest_data(const Convex3D &a, const Plane3D &b);

		CollisionData iTest_data(const Convex3D &a, const Ray3D &b);

	}
}