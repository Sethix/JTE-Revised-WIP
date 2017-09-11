#pragma once
#include "SystemStructure.h"
#include "Time.h"

namespace JTL
{
	namespace SIM
	{
		class RigidbodyDynamics3D : public System
		{
			bool condition(Handle<Entity> i)
			{
				return i->transform > -1 && i->rigidbody3D > -1;
			}

			bool update(Handle<Entity> i)
			{
				i->rigidbody3D->Integrate(&i->transform, Time::instance().GetDeltaTime());
				return true;
			}
		};
	}
}