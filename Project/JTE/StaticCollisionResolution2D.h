#pragma once
#include "CollisionDetection2D.h"

namespace JTL
{
	namespace SIM
	{
		class StaticResolution2D : public Collision2DSystem
		{
			bool condition(Collision2D &c)
			{
				return (c.first->rigidbody2D > -1 && c.second->rigidbody2D < 0)
					&& c.first->collider2D->isTrigger == false
					&& c.second->collider2D->isTrigger == false
					|| (c.first->rigidbody2D <  0 && c.second->rigidbody2D > -1)
					&& c.first->collider2D->isTrigger == false
					&& c.second->collider2D->isTrigger == false;
			}

			void update(Collision2D &c)
			{
				if (c.first->rigidbody2D > -1)
				{
					Vector3 MTV = c.collision.collisionNormal * c.collision.penDepth;

					Vector3 p1 = c.first->transform->GetPosition() - MTV;

					c.first->transform->SetPosition(p1);
					c.first->rigidbody2D->velocity = Reflect(c.first->rigidbody2D->velocity, c.collision.collisionNormal.xy);
				}
				else
				{
					Vector3 MTV = c.collision.collisionNormal * c.collision.penDepth;

					Vector3 p1 = c.second->transform->GetPosition() + MTV;

					c.second->transform->SetPosition(p1);
					c.second->rigidbody2D->velocity = Reflect(c.second->rigidbody2D->velocity, c.collision.collisionNormal.xy);
				}
			}
		};
	}
}