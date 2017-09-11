#pragma once
#include "SystemStructure.h"
#include "Time.h"

namespace JTL
{
	namespace SIM
	{
		class RigidbodyDynamics2D : public System
		{
			bool condition(Handle<Entity> i)
			{
				return i->transform > -1 && i->rigidbody2D > -1;
			}

			bool update(Handle<Entity> i)
			{
				i->rigidbody2D->Integrate(&i->transform, Time::instance().GetDeltaTime());
				return true;
			}
		};
	}
}