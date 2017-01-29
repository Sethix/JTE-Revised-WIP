#include "Collider3D.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		Collider3D::Collider3D() : shape(Collider3D::_SPHERE), sphere({ { 0,0 },1 }) { }

		CollisionData CollisionDetected(const Transform&at, const Collider3D &ac,
								  const Transform&bt, const Collider3D &bc)
		{
			Transform  t_lhs = at;
			Transform  t_rhs = bt;
			Collider3D lhs = ac;
			Collider3D rhs = bc;

			if (lhs.shape > rhs.shape)
			{
				std::swap(lhs, rhs);
				std::swap(t_lhs, t_rhs);
			}

#pragma region Shape_switch_statement

			switch (lhs.shape | rhs.shape)
			{
			case Collider3D::_SPHERE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.sphere,
					t_rhs.GetGlobalTransform() * rhs.sphere);
			case Collider3D::_SPHERE | Collider3D::_AABB:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.sphere,
					t_rhs.GetGlobalTransform() * rhs.cube);
			case Collider3D::_SPHERE | Collider3D::_RAY:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.sphere,
					t_rhs.GetGlobalTransform() * rhs.ray);
			case Collider3D::_SPHERE | Collider3D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.sphere,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider3D::_SPHERE | Collider3D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.sphere,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider3D::_AABB:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.cube,
					t_rhs.GetGlobalTransform() * rhs.convex);
			case Collider3D::_AABB | Collider3D::_RAY:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.cube,
					t_rhs.GetGlobalTransform() * rhs.ray);
			case Collider3D::_AABB | Collider3D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.cube,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider3D::_AABB | Collider3D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.cube,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider3D::_RAY | Collider3D::_PLANE:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.ray,
					t_rhs.GetGlobalTransform() * rhs.plane);
			case Collider3D::_RAY | Collider3D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.ray,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider3D::_PLANE | Collider3D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.plane,
					t_rhs.GetGlobalTransform() * rhs.convex);

			case Collider3D::_CONVEX:
				return iTest_data(t_lhs.GetGlobalTransform() * lhs.convex,
					t_rhs.GetGlobalTransform() * rhs.convex);
			}

#pragma endregion

		}
	}
}
