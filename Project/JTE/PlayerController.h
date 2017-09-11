#pragma once
#include "Component.h"

namespace JTL
{
	namespace SIM
	{
		class PlayerController : public Component<PlayerController>
		{
		public:
			bool gamepadEnabled;
			int ID;
		};
	}
}