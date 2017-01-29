#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <Math.h>
#include "CollisionData.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Plane2D.h"
#include "Ray2D.h"
#include "Convex2D.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix3.h"
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


	struct Vector2Hasher
	{
		size_t operator()(const Vector2 &t) const
		{
			return hash(t.x) ^ (hash(t.y) << 1);
		}
	};

	namespace SIM
	{
		Convex2D operator*(const Matrix4 &m, const Convex2D &a)
		{
			Convex2D r = a;
			r.size = a.size;

			for (int i = 0; i < a.size; ++i)
				r.verts[i] = (m * Vector4{ a.verts[i].x, a.verts[i].y, 0, 1 }).xyz.xy;

			return r;
		}

#pragma region CollisionFunctions

		CollisionData iTest_data(const Convex2D &a, const Convex2D &b)
		{
			std::vector<Vector2> axes;
			std::unordered_set<Vector2, Vector2Hasher> saxes;

			CollisionData cd{ INFINITY };

			for (size_t i = 0; i < a.size; ++i)
			{
				auto axis = Perpendicular(Normalized(a.verts[i] - a.verts[(i + 1) % a.size]));
				axes.push_back(axis);

				//if (!saxes.count(-axis))
				saxes.insert(axis);
			}
			for (size_t i = 0; i < b.size; ++i)
			{
				auto axis = Perpendicular(Normalized(b.verts[i] - b.verts[(i + 1) % b.size]));
				axes.push_back(axis);

				//if (!saxes.count(-axis))
				saxes.insert(axis);
			}

			//for (size_t i = 0; i < axes.size(); ++i)
			for each(Vector2 axis in saxes)
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
					cd = { pdepth, (pdepth == (amax - bmin)) ? Vector3{axis.x, axis.y, 0} : Vector3{ -axis.x, -axis.y, 0 } };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex2D &a, const AABB2D &b)
		{
			Convex2D temp;

			temp.size = 4;

			temp.verts[0] = b.min;
			temp.verts[1] = Vector2{ b.min.x, b.max.y };
			temp.verts[2] = b.max;
			temp.verts[3] = Vector2{ b.max.x, b.min.y };

			return iTest_data(temp, a);

			std::vector<Vector2> axes;

			CollisionData cd{ INFINITY };

			for (size_t i = 0; i < a.size; ++i)
				axes.push_back(Perpendicular(Normalized(a.verts[i] - a.verts[(i + 1) % a.size])));

			for (size_t i = 0; i < temp.size; ++i)
				axes.push_back(Perpendicular(Normalized(temp.verts[i] - temp.verts[(i + 1) % temp.size])));

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
					cd = { pdepth, (pdepth == (amax - bmin)) ? Vector3{ axes[i].x, axes[i].y, 0 } : -Vector3{ axes[i].x, axes[i].y, 0 } };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex2D &a, const Circle &b)
		{
			std::vector<Vector2> axes;

			CollisionData cd{ INFINITY };

			for (size_t i = 0; i < a.size; ++i)
				axes.push_back(Perpendicular(Normalized(a.verts[i] - a.verts[(i + 1) % a.size])));

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
					cd = { pdepth, pdepth == (amax - bmin) ? Vector3{axes[i].x, axes[i].y, 0} : Vector3{-axes[i].x, -axes[i].y, 0} };

				if (pdepth < 0)
				{
					return cd;
				}
			}

			return cd;

		}

		CollisionData iTest_data(const Convex2D &a, const Plane2D &b)
		{

			CollisionData cd{ INFINITY };

			Vector2 axis = b.normal;

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
				cd = { pdepth,{ axis.x, axis.y, 0 } };

			return cd;

		}

		CollisionData iTest_data(const Convex2D &a, const Ray2D &b)
		{
			CollisionData cd = { false, INFINITY };

			std::vector<Vector2> axes;

			axes.reserve(a.size);
			for (int i = 0; i < a.size; ++i)
				axes.push_back(Perpendicular(Normalized(a.verts[i] - a.verts[(i + 1) % a.size])));


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
						cd = { (Length(b.direction * b.length)) - tmin, {axes[i].x, axes[i].y, 0} };
					}
				}
				else    tmax = t;

				if (tmin > tmax) return cd = { 0 };
			}
			return cd;
		}
	}
}