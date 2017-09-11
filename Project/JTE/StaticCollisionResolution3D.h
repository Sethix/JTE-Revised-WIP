#pragma once
#include "CollisionDetection3D.h"

namespace JTL
{
	namespace SIM
	{
		class StaticResolution3D : public Collision3DSystem
		{
			bool condition(Collision3D &c)
			{
				return (c.first->rigidbody3D > -1 && c.second->rigidbody3D < 0)
					&& c.first->collider3D->isTrigger == false
					&& c.second->collider3D->isTrigger == false
					|| (c.first->rigidbody3D <  0 && c.second->rigidbody3D > -1)
					&& c.first->collider3D->isTrigger == false
					&& c.second->collider3D->isTrigger == false;
			}

			void update(Collision3D &c)
			{
				if (c.first->rigidbody3D > -1)
				{
					Vector3 MTV = c.collision.collisionNormal * c.collision.penDepth;

					Vector3 p1 = c.first->transform->GetPosition() - MTV;

					c.first->transform->SetPosition(p1);
					c.first->rigidbody3D->velocity = Reflect(c.first->rigidbody3D->velocity, c.collision.collisionNormal);
				}
				else
				{
					Vector3 MTV = c.collision.collisionNormal * c.collision.penDepth;

					Vector3 p1 = c.second->transform->GetPosition() + MTV;

					c.second->transform->SetPosition(p1);
					c.second->rigidbody3D->velocity = Reflect(c.second->rigidbody3D->velocity, c.collision.collisionNormal);
				}
			}
		};
	}
}