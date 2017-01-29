#pragma once
#include "Entity.h"
#include "Assets.h"
#include "Input.h"
#include "Time.h"
#include "Window.h"
#include "CollisionDetection2D.h"
#include "CollisionDetection3D.h"
#include "DynamicCollisionResolution2D.h"
#include "DynamicCollisionResolution3D.h"
#include "StaticCollisionResolution2D.h"
#include "StaticCollisionResolution3D.h"
#include "TriggerCollisionResolution2D.h"
#include "TriggerCollisionResolution3D.h"
#include "RigidbodyDynamics2D.h"
#include "RigidbodyDynamics3D.h"
#include "PlayerUpdate.h"
#include "Render.h"

class JTE
{

	JTL::SIM::Window *window;
	JTL::SIM::Input *input;
	JTL::SIM::Time *time;
	JTL::SIM::Assets *assets;
	JTL::SIM::RigidbodyDynamics2D rigidbody2DSystem;
	JTL::SIM::RigidbodyDynamics3D rigidbody3DSystem;
	JTL::SIM::Collision2DDetection collision2DSystem;
	JTL::SIM::Collision3DDetection collision3DSystem;
	JTL::SIM::PlayerUpdate playerUpdate;
	JTL::SIM::RenderSystem renderSystem;

	JTE()
	{
		window = &JTL::SIM::Window::instance();
		input = &JTL::SIM::Input::instance();
		time = &JTL::SIM::Time::instance();
	}

public:
	static JTE &instance() { static JTE instance; return instance; }

	void StartJTE()
	{
		window->init(800,800,"EXE.EXE", true, false);
		time->init();
		input->init();
		assets = &JTL::SIM::Assets::instance();
	}

	bool UpdateJTE()
	{
		bool live = window->step();
		time->step();
		input->step();
		rigidbody2DSystem.step();
		rigidbody3DSystem.step();
		collision2DSystem.step();
		collision3DSystem.step();
		playerUpdate.step();
		renderSystem.step();
		return live;
	}

	void TermJTE()
	{
		input->term();
		time->term();
		window->term();
	}
};