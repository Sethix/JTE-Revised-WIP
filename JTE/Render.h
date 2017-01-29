#pragma once
#include "SystemStructure.h"
#include "Assets.h"

namespace JTL
{
	namespace SIM
	{
		class RenderSystem : public System
		{
			bool condition(Handle<Entity> i)
			{
				return i->camera > -1;
			}

			bool update(Handle<Entity> i)
			{
				i->camera->update();
				return true;
			}
		};
	}
}