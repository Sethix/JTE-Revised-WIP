#pragma once
#include "CollisionDetection2D.h"

namespace JTL
{
	namespace SIM
	{
		class TriggerResolution2D : public Collision2DSystem
		{
			bool condition(Collision2D &c)
			{
				return c.first->collider2D->isTrigger == true || c.second->collider2D->isTrigger == true;
			}

			void update(Collision2D &c)
			{
				if (c.first->collider2D->isTrigger == true)
				{
					// TODO
				}
				else
				{
					// TODO
				}
			}
		};
	}
}