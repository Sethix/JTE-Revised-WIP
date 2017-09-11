#pragma once
#include "CollisionDetection3D.h"

namespace JTL
{
	namespace SIM
	{
		class TriggerResolution3D : public Collision3DSystem
		{
			bool condition(Collision3D &c)
			{
				return c.first->collider3D->isTrigger == true || c.second->collider3D->isTrigger == true;
			}

			void update(Collision3D &c)
			{
				if (c.first->collider3D->isTrigger == true)
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