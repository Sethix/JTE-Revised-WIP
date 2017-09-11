#pragma once
#include "Transform.h"
#include "Sphere.h"
#include "AABB3D.h"
#include "Plane3D.h"
#include "Ray3D.h"
#include "Convex3D.h"
#include "Component.h"
#include "CollisionData.h"

namespace JTL
{
	namespace SIM
	{
		class Collider3D : public Component<Collider3D>
		{
		public:
			enum SHAPE { _SPHERE = 1, _AABB = 2, _RAY = 4, _PLANE = 8, _CONVEX = 16 } shape;

			union
			{
				Sphere		sphere;
				AABB3D		cube;
				Ray3D		ray;
				Plane3D		plane;
				Convex3D	convex;
			};

			bool isTrigger;

			Collider3D();
		};

		
		CollisionData CollisionDetected(const Transform&, const Collider3D &,
								  const Transform&, const Collider3D &);
	}
}