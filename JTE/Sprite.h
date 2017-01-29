#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include "Assets.h"
#include "Component.h"

namespace JTL
{
	namespace SIM
	{
		class Sprite : public Component<Sprite>
		{
		public:
			int frame;

			Vector4 tint;

			std::string texture;
			std::string shader;

			Sprite();
		};
	}
}