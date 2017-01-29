#pragma once
#include "Vector4.h"
#include "Assets.h"
#include "Component.h"

namespace JTL
{
	namespace SIM
	{
		class Model : public Component<Model>
		{
		public:
			Vector4 tint;

			std::string mesh;
			std::string albedo;
			std::string specular;
			std::string normal;
			std::string shader;

			REN::ShaderFlags shaderFlags;

			Model() { mesh = "cube"; albedo = "default"; shader = "geoPass"; }
		};
	}
}