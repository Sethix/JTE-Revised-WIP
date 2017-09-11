#pragma once
#include "Component.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		class Light : public Component<Light>
		{
		public:
			Vector4 color;

			Light() { color = {1,1,1,1}; }
		};
	}
}
