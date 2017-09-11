#pragma once
#include "Vector3.h"

namespace JTL
{
	namespace SIM
	{
		struct CollisionData
		{
			float penDepth;
			Vector3 collisionNormal;
		};
	}
}