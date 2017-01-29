#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <Math.h>
#include "CollisionData.h"
#include "AABB3D.h"
#include "Sphere.h"
#include "Plane3D.h"
#include "Ray3D.h"
#include "Convex3D.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "JTLMath.h"

namespace JTL
{
	namespace SIM
	{
		Vector3 AABB3D::dim() const { return max - min; }

		Vector3 AABB3D::pos() const { return (max + min) / 2; }

#pragma region ShapeFunctions

		AABB3D	operator*	(const Matrix4 &m, const AABB3D &a)
		{
			Vector3 omin = a.min;
			Vector3 omax = a.max;

			Vector3 rmin = { m.mm[0][2], m.mm[1][2], m.mm[2][2] };
			Vector3 rmax = { m.mm[0][2], m.mm[1][2], m.mm[2][2] };

			float p, q;

			for (unsigned j = 0; j < 2; ++j)
				for (unsigned i = 0; i < 2; ++i)
				{
					p = omin[i] * m.mm[j][i];
					q = omax[i] * m.mm[j][i];

					if (p > q) std::swap(p, q);
					rmin[j] += p;
					rmax[j] += q;
				}
			return{ rmin, rmax };
		}

		AABB3D	genAABB3D(const Vector3 *pts, const size_t &n)
		{
			return AABB3D(Min(pts, n), Max(pts, n));
		}

#pragma endregion

#pragma region CollisionFunctions

		bool	iTest(const AABB3D &ac, const AABB3D &bc)
		{
			return !(ac.max.x < bc.min.x || bc.max.x < ac.min.x
				|| ac.max.y < bc.min.y || bc.max.y < ac.min.y);
		}

		bool	iTest(const AABB3D &ac, const Sphere &bc)
		{
			return iTest(Sphere{ Clamp(bc.position, ac.min, ac.max) , 0 }, bc);
		}

		bool	iTest(const AABB3D &ac, const Plane3D &bc)
		{
			return Dot(bc.normal, (ac.pos() - bc.position)) <=
				  (ac.dim().x / 2) * Dot(bc.normal, Vector3{ 1,0,0 })
				+ (ac.dim().y / 2) * Dot(bc.normal, Vector3{ 0,1,0 })
				+ (ac.dim().z / 2) * Dot(bc.normal, Vector3{ 0,0,1 });
		}

		bool	iTest(const AABB3D &ac, const Ray3D &bc)
		{
			assert(bc.direction[0] + bc.direction[1] + bc.direction[2] != 0);

			Ray3D ray = bc;

			for (int i = 0; i < 2; ++i)
				ray.direction[i] = (ray.direction[i] == 0) ? FLT_EPSILON : ray.direction[i];

			Plane3D planes[6];

			planes[0] = { Vector3{ ac.min.x  , ac.pos().y, ac.pos().z },Vector3{-1, 0, 0 } };
			planes[1] = { Vector3{ ac.pos().x, ac.min.y	 , ac.pos().z },Vector3{ 0,-1, 0 } };
			planes[2] = { Vector3{ ac.pos().x, ac.pos().y, ac.min.z   },Vector3{ 0, 0,-1 } };
			planes[3] = { Vector3{ ac.max.x  , ac.pos().y, ac.pos().z },Vector3{ 1, 0, 0 } };
			planes[4] = { Vector3{ ac.pos().x, ac.max.y  , ac.pos().z },Vector3{ 0, 1, 0 } };
			planes[5] = { Vector3{ ac.pos().x, ac.pos().y, ac.max.z   },Vector3{ 0, 0, 1 } };


			float dists[6];

			float tmin = FLT_MAX;
			float tmax = -FLT_MAX;

			for (int i = 0; i < 6; ++i)
			{
				float deno = -(Dot(planes[i].normal, ray.direction));

				dists[i] = Dot(planes[i].normal, (ray.position - planes[i].position)) / deno;
			}

			tmin = fmaxf(fminf(dists[0], dists[3]), fminf(dists[1], dists[4]));
			tmin = fmaxf(tmin, fminf(dists[2], dists[5]));
			tmax = fminf(fmaxf(dists[0], dists[3]), fmaxf(dists[1], dists[4]));
			tmax = fminf(tmax, fmaxf(dists[2], dists[5]));

			return tmin <= tmax && 0 <= tmin <= bc.length;
		}

		CollisionData iTest_data(const AABB3D &ac, const AABB3D &bc)
		{
			if (iTest(ac, bc))
			{
				Vector3 aVerts[8] = { ac.min, {ac.min.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.min.z},
									  ac.max, {ac.min.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.min.z}};
				Vector3 bVerts[8] = { bc.min, {bc.min.x, bc.min.y, bc.max.z}, {bc.max.x, bc.min.y, bc.max.z}, {bc.max.x, bc.min.y, bc.min.z},
									  bc.max, {bc.min.x, bc.max.y, bc.max.z}, {bc.max.x, bc.max.y, bc.max.z}, {bc.max.x, bc.max.y, bc.min.z}};

				unsigned cubeIdcs[36] = { 0,1,2,1,3,2,
									  	  5,2,1,6,2,5,
										  2,6,7,7,3,2,
										  0,4,3,7,3,4,
										  0,4,2,5,2,4,
										  4,5,6,5,7,6 };

				Convex3D a(aVerts, cubeIdcs, 8, 36), b(bVerts, cubeIdcs, 8, 36);

				return iTest_data(a, b);
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const AABB3D &ac, const Sphere &bc)
		{
			if (iTest(ac, bc))
			{
				Vector3 aVerts[8] = { ac.min, {ac.min.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.min.z},
									  ac.max, {ac.min.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.min.z}};

				unsigned cubeIdcs[36] = { 0,1,2,1,3,2,
									  	  5,2,1,6,2,5,
										  2,6,7,7,3,2,
										  0,4,3,7,3,4,
										  0,4,2,5,2,4,
										  4,5,6,5,7,6 };

				Convex3D a(aVerts, cubeIdcs, 8, 36);

				return iTest_data(a, bc);
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const AABB3D &ac, const Plane3D &bc)
		{
			if (iTest(ac, bc))
			{
				CollisionData r;
				r.collisionNormal = { bc.normal.x, bc.normal.y, bc.normal.z };
				r.penDepth = Dot(bc.normal, (ac.pos() - bc.position));
				if (r.penDepth < 0) r.penDepth = 0;
				return r;
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const AABB3D &ac, const Ray3D &bc)
		{
			if (iTest(ac, bc))
			{
				Vector3 aVerts[8] = { ac.min, {ac.min.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.max.z}, {ac.max.x, ac.min.y, ac.min.z},
									  ac.max, {ac.min.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.max.z}, {ac.max.x, ac.max.y, ac.min.z}};

				unsigned cubeIdcs[36] = { 0,1,2,1,3,2,
									  	  5,2,1,6,2,5,
										  2,6,7,7,3,2,
										  0,4,3,7,3,4,
										  0,4,2,5,2,4,
										  4,5,6,5,7,6 };

				Convex3D a(aVerts, cubeIdcs, 8, 36);

				a.size = 4;

				return iTest_data(a, bc);
			}
			else return CollisionData{ 0,0 };
		}

		CollisionData iTest_data(const AABB3D &ac, const Convex3D &bc)
		{
			return iTest_data(bc, ac);
		}
	}
}