#pragma once
#include "CollisionDetection2D.h"

namespace JTL
{
	namespace SIM
	{
		class DynamicResolution2D : public Collision2DSystem
		{
			bool condition(Collision2D &c)
			{
				return c.first->rigidbody2D > -1 && c.second->rigidbody2D > -1
					&& c.first->collider2D->isTrigger == false
					&& c.second->collider2D->isTrigger == false;
			}

			void update(Collision2D &c)
			{
				Vector2 MTV = c.collision.collisionNormal.xy * c.collision.penDepth;

				Vector2 p1 = c.first->transform->GetPosition().xy - MTV / 2;
				Vector2 p2 = c.second->transform->GetPosition().xy + MTV / 2;

				c.first->transform->SetPosition({ p1.x, p1.y, 0 });
				c.second->transform->SetPosition({ p2.x, p2.y, 0 });

				std::swap(c.first->rigidbody2D->velocity, c.second->rigidbody2D->velocity);
			}
		};
	}
}