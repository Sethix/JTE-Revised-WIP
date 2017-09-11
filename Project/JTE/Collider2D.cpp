#include "CollisionData.h"
#include "Collider2D.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		Collider2D::Collider2D() : shape(Collider2D::_CIRCLE), circle({ {0,0},1 }) { }

		CollisionData CollisionDetected(const Transform&at, const Collider2D &ac,
								  const Transform&bt, const Collider2D &bc)
		{
			Transform  t_lhs = at;
			Transform  t_rhs = bt;
			Collider2D lhs   = ac;
			Collider2D rhs   = bc;

			if (lhs.shape > rhs.shape)
			{
				std::swap(lhs, rhs);
				std::swap(t_lhs, t_rhs);
			}

#pragma region Shape_switch_statement

			switch (lhs.shape | rhs.shape)
			{
			case Collider2D::_CIRCLE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.circle,
					t_rhs.GetGlobalTransform() * rhs.circle);
			case Collider2D::_CIRCLE | Collider2D::_AABB:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.circle,
					t_rhs.GetGlobalTransform() * rhs.box);
			case Collider2D::_CIRCLE | Collider2D::_RAY:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.circle,
					t_rhs.GetGlobalTransform() * rhs.ray);
			case Collider2D::_CIRCLE | Collider2D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.circle,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider2D::_CIRCLE | Collider2D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.circle,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider2D::_AABB:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.box,
					t_rhs.GetGlobalTransform() * rhs.convex);
			case Collider2D::_AABB | Collider2D::_RAY:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.box,
					t_rhs.GetGlobalTransform() * rhs.ray);
			case Collider2D::_AABB | Collider2D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.box,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider2D::_AABB | Collider2D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.box,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider2D::_RAY | Collider2D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.ray,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider2D::_RAY | Collider2D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.ray,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider2D::_PLANE | Collider2D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.plane,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider2D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.convex,
					t_rhs.GetGlobalTransform() * rhs.convex);
			}

#pragma endregion

		}
	}
}
