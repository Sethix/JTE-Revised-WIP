#pragma once
#include "SystemStructure.h"
#include "Input.h"
#include "Time.h"

namespace JTL
{
	namespace SIM
	{
		class PlayerUpdate : public System
		{
			bool condition(Handle<Entity> i)
			{
				return  i->rigidbody2D  > -1 &&
					i->transform  > -1 &&
					i->playerController > -1;
			}

			bool update(Handle<Entity> i)
			{
				auto &input = Input::instance();
				auto controller = *i->playerController;

				return true;
			}
		};
	}
}