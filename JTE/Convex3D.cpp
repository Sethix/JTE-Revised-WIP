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

	const float feps = FLT_EPSILON;


	inline unsigned int hash(float f)
	{
		unsigned int ui, fe;
		memcpy(&ui, &f, sizeof(float));
		memcpy(&fe, &feps, sizeof(float));

		return ui & (0xfffffff - fe); // adjust this bitmask to change the significant bits
	}


	struct Vector3Hasher
	{
		size_t operator()(const Vector3 &t) const
		{
			return hash(t.x) ^ (hash(t.y) ^ (hash(t.z) << 1));
		}
	};

	namespace SIM
	{
		Convex3D operator*(const Matrix4 &m, const Convex3D &a)
		{
			Convex3D r = a;
			r.size = a.size;

			for (int i = 0; i < a.size; ++i)
				r.verts[i] = (m * Vector4{ a.verts[i].x, a.verts[i].y, a.verts[i].z }).xyz;

			return r;
		}

#pragma region CollisionFunctions

		CollisionData iTest_data(const Convex3D &a, const Convex3D &b)
		{
			std::vector<Vector3> axes;
			std::unordered_set<Vector3, Vector3Hasher> saxes;

			CollisionData cd{ INFINITY };



			for (size_t i = 0; i < a.size; ++i)
			{
				//auto axis = perp(normal(a.verts[i] - a.verts[(i + 1) % a.size]));
				//axes.push_back(a.normals[i]);

				//if (!saxes.count(-axis))
				saxes.insert(a.normals[i]);
			}
			for (size_t i = 0; i < b.size; ++i)
			{
				//auto axis = perp(normal(b.verts[i] - b.verts[(i + 1) % b.size]));
				//axes.push_back(b.normals[i]);

				//if (!saxes.count(-axis))
				saxes.insert(b.normals[i]);
			}

			for each(Vector3 axis in saxes)
			{
				float amin = INFINITY;
				float bmin = INFINITY;
				float amax = -INFINITY;
				float bmax = -INFINITY;

				for (size_t j = 0; j < a.size; ++j)
				{
					float pp = JTL::Dot(axis, a.verts[j]);

					amin = fminf(pp, amin);
					amax = fmaxf(pp, amax);
				}

				for (size_t j = 0; j < b.size; ++j)
				{
					float pp = JTL::Dot(axis, b.verts[j]);

					bmin = fminf(pp, bmin);
					bmax = fmaxf(pp, bmax);
				}

				float pdepth = fminf(amax - bmin, bmax - amin);

				if (pdepth < cd.penDepth)
					cd = { pdepth, (pdepth == (amax - bmin)) ? Vector3{ axis.x, axis.y, axis.z } : Vector3{ -axis.x, -axis.y, -axis.z } };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex3D &a, const AABB3D &b)
		{
			Vector3  cubeVerts[8] = { {-1,-1,-1 },{-1,-1, 1 },{ 1,-1, 1 },{ 1,-1,-1 },
									  {-1, 1,-1 },{-1, 1, 1 },{ 1, 1, 1 },{ 1, 1,-1 } };
			
			unsigned cubeIdcs[36] = { 0,1,2,1,3,2,
									  5,2,1,6,2,5,
									  2,6,7,7,3,2,
									  0,4,3,7,3,4,
									  0,4,2,5,2,4,
									  4,5,6,5,7,6 };

			Convex3D temp(cubeVerts,cubeIdcs,8,36);

			std::vector<Vector3> axes;

			CollisionData cd{ INFINITY };

			for (size_t i = 0; i < a.size; ++i)
				axes.push_back(a.normals[i]);

			for (size_t i = 0; i < temp.size; ++i)
				axes.push_back(temp.normals[i]);

			for (size_t i = 0; i < axes.size(); ++i)
			{
				float amin = INFINITY;
				float bmin = INFINITY;
				float amax = -INFINITY;
				float bmax = -INFINITY;

				//cd.collisionNormal = axes[i];

				for (size_t j = 0; j < a.size; ++j)
				{
					float pp = JTL::Dot(axes[i], a.verts[j]);

					amin = fminf(pp, amin);
					amax = fmaxf(pp, amax);
				}

				for (size_t j = 0; j < temp.size; ++j)
				{
					float pp = JTL::Dot(axes[i], temp.verts[j]);

					bmin = fminf(pp, bmin);
					bmax = fmaxf(pp, bmax);
				}

				float pdepth = fminf(amax - bmin, bmax - amin);

				if (pdepth < cd.penDepth)
					cd = { pdepth, (pdepth == (amax - bmin)) ? Vector3{ axes[i].x, axes[i].y, axes[i].z } : -Vector3{ axes[i].x, axes[i].y, axes[i].z } };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex3D &a, const Sphere &b)
		{
			std::vector<Vector3> axes;

			CollisionData cd{ INFINITY };

			for (size_t i = 0; i < a.size; ++i)
				axes.push_back(a.normals[i]);

			for (size_t i = 0; i < axes.size(); ++i)
			{
				float amin = INFINITY;
				float bmin = INFINITY;
				float amax = -INFINITY;
				float bmax = -INFINITY;

				//cd.collisionNormal = axes[i];

				for (size_t j = 0; j < a.size; ++j)
				{
					float pp = JTL::Dot(axes[i], a.verts[j]);

					amin = fminf(pp, amin);
					amax = fmaxf(pp, amax);
				}


				float pp = JTL::Dot(axes[i], b.position);

				bmin = pp - b.radius;
				bmax = pp + b.radius;

				float pdepth = fminf(amax - bmin, bmax - amin);

				if (pdepth < cd.penDepth)
					cd = { pdepth, pdepth == (amax - bmin) ? Vector3{ axes[i].x, axes[i].y, axes[i].z } : Vector3{ -axes[i].x, -axes[i].y, -axes[i].z } };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex3D &a, const Plane3D &b)
		{

			CollisionData cd{ INFINITY };

			Vector3 axis = b.normal;

			float amin = INFINITY;
			float amax = -INFINITY;

			//cd.collisionNormal = axis;

			for (size_t j = 0; j < a.size; ++j)
			{
				float pp = JTL::Dot(axis, b.position - a.verts[j]);

				amin = fminf(pp, amin);
				amax = fmaxf(pp, amax);
			}

			float pdepth = fminf(amax, amin);

			if (pdepth < cd.penDepth)
				cd = { pdepth,{ axis.x, axis.y, axis.z } };

			return cd;

		}

		CollisionData iTest_data(const Convex3D &a, const Ray3D &b)
		{
			CollisionData cd = { false, INFINITY };

			std::vector<Vector3> axes;

			axes.reserve(a.size);
			for (int i = 0; i < a.size; ++i)
				axes.push_back(a.normals[i]);


			float tmin = 0, tmax = 1;

			for (int i = 0; i < axes.size(); ++i)
			{
				float N = -Dot(axes[i], b.position - a.verts[i]);
				float D = Dot(axes[i], b.direction);

				if (fabs(D) < FLT_EPSILON)
				{
					if (N < 0) return cd = { 0 };
					else continue;
				}

				float t = N / D;

				if (D < 0)
				{
					if (t > tmin)
					{
						tmin = t;
						cd = { (Length(b.direction * b.length)) - tmin,{ axes[i].x, axes[i].y, axes[i].z } };
					}
				}
				else    tmax = t;

				if (tmin > tmax) return cd = { 0 };
			}
			return cd;
		}
		Convex3D::Convex3D(Vector3 * v, size_t * idx, unsigned int vSize, unsigned int iSize)
		{
			verts   = new Vector3[vSize];
			normals = new Vector3[iSize /  3];
			indices = new unsigned int[iSize];
			for (int i = 0; i < iSize; i += 3)
			{
				normals[i / 3] = Normalized(
								 Cross(-v[idx[i]] + v[idx[i + 1]],
									   -v[idx[i]] + v[idx[i + 2]]));
			}
		}
	}
}