#pragma once
#include "Component.h"

namespace JTL
{
	namespace SIM
	{
		class Lifespan : public Component<Lifespan>
		{
		public:
			float limit, timer;

			Lifespan() : limit(5), timer(0) {};
		};
	}
}