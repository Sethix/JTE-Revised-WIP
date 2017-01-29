#pragma once
#include "Transform.h"
#include "Component.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Assets.h"

namespace JTL
{
	namespace SIM
	{
		class Camera : public Component<Camera>
		{
		public:
			Handle<Transform> transform;

			std::string gFrame;
			std::string lFrame;
			std::string sFrame;
			std::string aoFrame;
			REN::FrameBuffer cameraOut;

			std::string skybox;

			float nearClipPlane;
			float farClipPlane;
			float FOV;

			Matrix4 screenSpace;

			Matrix4 View();
			Matrix4 Orthographic();
			Matrix4 Perspective();

			void SetScreenSpace();

			void update();

			Camera();
		};
	}
}