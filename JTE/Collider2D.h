#pragma once
#include "Transform.h"
#include "CollisionData.h"
#include "Component.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Ray2D.h"
#include "Plane2D.h"
#include "Convex2D.h"

namespace JTL
{
	namespace SIM
	{
		class Collider2D : public Component<Collider2D>
		{
		public:
			enum SHAPE { _CIRCLE = 1, _AABB = 2, _RAY = 4, _PLANE = 8, _CONVEX = 16 } shape;

			union
			{
				Circle		circle;
				AABB2D		box;
				Ray2D		ray;
				Plane2D		plane;
				Convex2D	convex;
			};

			bool isTrigger;

			Collider2D();
		};

		CollisionData CollisionDetected(const Transform&, const Collider2D &,
								  const Transform&, const Collider2D &);
	}
}