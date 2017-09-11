#pragma once
#include "Component.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Collider3D.h"
#include "Rigidbody2D.h"
#include "Rigidbody3D.h"
#include "Sprite.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Lifespan.h"
#include "PlayerController.h"

namespace JTL
{
	namespace SIM
	{
		struct Entity : Component<Entity>
		{
			Handle<Transform		> transform;
			Handle<Collider2D		> collider2D;
			Handle<Collider3D		> collider3D;
			Handle<Rigidbody2D		> rigidbody2D;
			Handle<Rigidbody3D		> rigidbody3D;
			Handle<Sprite			> sprite;
			Handle<Model			> model;
			Handle<Light			> light;
			Handle<Camera			> camera;
			Handle<Lifespan			> lifespan;
			Handle<PlayerController	> playerController;
		
			void onFree()
			{
				Transform			::free(transform.idx);
				Collider2D			::free(collider2D.idx);
				Collider3D			::free(collider3D.idx);
				Rigidbody2D			::free(rigidbody2D.idx);
				Rigidbody3D			::free(rigidbody3D.idx);
				Sprite				::free(sprite.idx);
				Model				::free(model.idx);
				Light				::free(light.idx);
				Camera				::free(camera.idx);
				Lifespan			::free(lifespan.idx);
				PlayerController	::free(playerController.idx);
			}
		};
	}
}