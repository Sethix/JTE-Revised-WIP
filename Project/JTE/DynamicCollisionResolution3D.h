#pragma once
#include "CollisionDetection3D.h"

namespace JTL
{
	namespace SIM
	{
		class DynamicResolution3D : public Collision3DSystem
		{
			bool condition(Collision3D &c)
			{
				return c.first->rigidbody3D > -1 && c.second->rigidbody3D > -1
					&& c.first->collider3D->isTrigger == false
					&& c.second->collider3D->isTrigger == false;
			}

			void update(Collision3D &c)
			{
				Vector3 MTV = c.collision.collisionNormal * c.collision.penDepth;

				Vector3 p1 = c.first->transform->GetPosition() - MTV / 2;
				Vector3 p2 = c.second->transform->GetPosition() + MTV / 2;

				c.first->transform->SetPosition(p1);
				c.second->transform->SetPosition(p2);

				std::swap(c.first->rigidbody3D->velocity, c.second->rigidbody3D->velocity);
			}
		};
	}
}