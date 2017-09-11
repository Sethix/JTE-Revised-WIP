#include "JTE.h"
#include "JTLMath.h"
#include "Entity.h"
#include <iostream>

int main()
{
	JTE::instance().StartJTE();

#pragma region  shiet

	JTL::SIM::Assets::instance().loadGeometry("spear", "../res/models/soulspear.obj");
	JTL::SIM::Assets::instance().loadGeometry("cube", "../res/models/cube.obj");
	JTL::SIM::Assets::instance().loadGeometry("sphere", "../res/models/sphere.obj");
	JTL::SIM::Assets::instance().loadGeometry("torus", "../res/models/torus.obj");
	JTL::SIM::Assets::instance().loadTexture("hexMap", "../res/textures/hexMap.jpg", 1, 1);
	JTL::SIM::Assets::instance().loadTexture("spearTex", "../res/textures/soulspear_diffuse.tga", 1, 1);
	JTL::SIM::Assets::instance().loadTexture("spearSpec", "../res/textures/soulspear_specular.tga", 1, 1);
	JTL::SIM::Assets::instance().loadTexture("spearNorm", "../res/textures/soulspear_normal.tga", 1, 1);
	JTL::SIM::Assets::instance().loadTexture("torusNorm", "../res/textures/torus_norms.png", 1, 1);
	JTL::SIM::Assets::instance().loadTexture("RandNorms", "../res/textures/RandNorms.jpg", 1, 1);
	JTL::SIM::Assets::instance().loadCubeMap("DefaultSky", "../res/textures/midnight-silence_rt.tga", "../res/textures/midnight-silence_lt.tga",
														   "../res/textures/midnight-silence_up.tga", "../res/textures/midnight-silence_dn.tga",
														   "../res/textures/midnight-silence_ft.tga", "../res/textures/midnight-silence_bk.tga");

#pragma region messyshit

	JTL::SIM::Handle<JTL::SIM::Entity> &obj = JTL::SIM::Entity::make();
	
	obj->transform = JTL::SIM::Transform::make();
	obj->model = JTL::SIM::Model::make();
	obj->rigidbody3D = JTL::SIM::Rigidbody3D::make();

	obj->transform->SetPosition({ -2,0,-5 });
	obj->transform->SetRotation(JTL::Quaternion(JTL::Vector3{0,1,0}, 90));
	obj->transform->SetScale({ 1.1f,1.1f,1.1f });

	obj->model->mesh = "spear";
	obj->model->albedo = "spearTex";
	obj->model->specular = "spearSpec";
	obj->model->normal = "spearNorm";
	obj->model->tint = { 1,1,1,1 };
	obj->model->shaderFlags = JTL::SIM::Assets::instance().shaders[obj->model->shader].flags;

	JTL::SIM::Handle<JTL::SIM::Entity> &cub = JTL::SIM::Entity::make();

	cub->transform = JTL::SIM::Transform::make();
	cub->model = JTL::SIM::Model::make();
	cub->rigidbody3D = JTL::SIM::Rigidbody3D::make();

	cub->transform->SetPosition({ 2,0,-5 });
	cub->transform->SetRotation(JTL::Quaternion(JTL::Vector3{ 0,1,0 }, 90));
	cub->transform->SetScale({ 1.1f,1.1f,1.1f });

	cub->model->mesh = "cube";
	cub->model->albedo = "default";
	cub->model->specular = "default";
	cub->model->normal = "default";
	cub->model->tint = { 1,1,1,1 };
	cub->model->shaderFlags = JTL::SIM::Assets::instance().shaders[obj->model->shader].flags;

	JTL::SIM::Handle<JTL::SIM::Entity> &trs = JTL::SIM::Entity::make();

	trs->transform = JTL::SIM::Transform::make();
	trs->model = JTL::SIM::Model::make();
	trs->rigidbody3D = JTL::SIM::Rigidbody3D::make();

	trs->transform->SetPosition({ 0,-1,1 });
	trs->transform->SetRotation(JTL::Quaternion(JTL::Vector3{ 0,1,0 }, 90));
	trs->transform->SetScale({ 0.5f,0.5f,0.5f });

	trs->model->mesh = "torus";
	trs->model->albedo = "default";
	trs->model->specular = "default";
	trs->model->normal = "torusNorm";
	trs->model->tint = { 1,1,1,1 };
	trs->model->shaderFlags = JTL::SIM::Assets::instance().shaders[obj->model->shader].flags;

	JTL::SIM::Handle<JTL::SIM::Entity> &bak = JTL::SIM::Entity::make();

	bak->transform = JTL::SIM::Transform::make();
	bak->model = JTL::SIM::Model::make();
	bak->rigidbody3D = JTL::SIM::Rigidbody3D::make();

	bak->transform->SetPosition({ 0,0,-10 });
	bak->transform->SetScale({ 20,20,0.5f });

	bak->model->mesh = "cube";
	bak->model->albedo = "default";
	bak->model->specular = "default";
	bak->model->normal = "default";
	bak->model->tint = { 1,1,1,1 };
	bak->model->shaderFlags = JTL::SIM::Assets::instance().shaders[obj->model->shader].flags;

	JTL::SIM::Handle<JTL::SIM::Entity> &spr = JTL::SIM::Entity::make();

	spr->transform = JTL::SIM::Transform::make();
	spr->model = JTL::SIM::Model::make();
	spr->rigidbody3D = JTL::SIM::Rigidbody3D::make();

	spr->transform->SetPosition({ 2,0,5 });
	spr->transform->SetRotation(JTL::Quaternion(JTL::Vector3{ 0,1,0 }, 90));
	spr->transform->SetScale({ 1.1f,1.1f,1.1f });

	spr->model->mesh = "sphere";
	spr->model->albedo = "default";
	spr->model->specular = "default";
	spr->model->normal = "hexMap";
	spr->model->tint = { 1,1,1,1 };
	spr->model->shaderFlags = JTL::SIM::Assets::instance().shaders[obj->model->shader].flags;

#pragma endregion

	auto cam = JTL::SIM::Entity::make();

	cam->transform = JTL::SIM::Transform::make();
	cam->camera = JTL::SIM::Camera::make();
	cam->camera->transform = cam->transform;

	cam->transform->SetPosition({ 0,0,0 });
	cam->transform->SetRotation(ID_QUAT);
	cam->transform->SetScale({ 1,1,1 });

	cam->camera->nearClipPlane = 0.1f;
	cam->camera->farClipPlane = 200;
	cam->camera->FOV = 120;

	cam->camera->skybox = "DefaultSky";

	obj->transform->GetGlobalTransform();

	float turnspeed = 5;

	bool camControls = false;

	auto lit = JTL::SIM::Entity::make();

	lit->transform = JTL::SIM::Transform::make();

	lit->transform->SetPosition({ 0,0,0 });
	lit->transform->SetScale({ 1,1,1 });

	lit->light = JTL::SIM::Light::make();

	bool ignoreFrame = false;

#pragma endregion

	while (JTE::instance().UpdateJTE())
	{
		//lit->light->color = { fabs(sin(JTL::SIM::Time::instance().GetTotalTime())),
		//	fabs(cos(JTL::SIM::Time::instance().GetTotalTime())),
		//	fabs(tan(JTL::SIM::Time::instance().GetTotalTime())),1 };

		if (JTL::SIM::Input::instance().GetKeyPress(KEY_X))
			camControls = !camControls;

		lit->transform->Rotate({ 0 ,1 ,0 }, 10 * JTL::SIM::Time::instance().GetDeltaTime());
		/*lit->transform->Rotate({ 0,1,0 }, 31.5f * JTL::SIM::Time::instance().GetDeltaTime());
		lit->transform->Rotate({ 0,0 ,1 }, 66.2f * JTL::SIM::Time::instance().GetDeltaTime());*/
		if (!camControls)
		{
			if (JTL::SIM::Input::instance().GetKey(KEY_D))
			{
				obj->transform->Rotate({ 0,1,0 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
			if (JTL::SIM::Input::instance().GetKey(KEY_A))
			{
				obj->transform->Rotate({ 0,-1,0 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
			if (JTL::SIM::Input::instance().GetKey(KEY_W))
			{
				obj->transform->Rotate({ 1,0,0 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
			if (JTL::SIM::Input::instance().GetKey(KEY_S))
			{
				obj->transform->Rotate({ -1,0,0 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
			if (JTL::SIM::Input::instance().GetKey(KEY_E))
			{
				obj->transform->Rotate({ 0,0,1 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
			if (JTL::SIM::Input::instance().GetKey(KEY_Q))
			{
				obj->transform->Rotate({ 0,0,-1 }, 45 * JTL::SIM::Time::instance().GetDeltaTime());
			}
		}
		else
		{
			if (JTL::SIM::Input::instance().GetKey(KEY_W))
				cam->transform->SetPosition(cam->transform->GetPosition() + (JTL::Inverse(cam->transform->GetGlobalTransform()) * JTL::Vector4{ 0,0,10,1 } * JTL::SIM::Time::instance().GetDeltaTime() * -5).xyz);
		}

		if (JTL::SIM::Input::instance().GetMouseButtonPress(1)) JTL::SIM::Input::instance().ResetCursor();

		JTL::SIM::Window::instance().lockMouse = JTL::SIM::Input::instance().GetMouseButton(1);
		//bool ignoreFrame = false;
		//ignoreFrame = JTL::SIM::Input::instance().GetMouseButtonPress(1);

		if (JTL::SIM::Window::instance().lockMouse)
		{
			cam->transform->Rotate({ 0,1,0 }, turnspeed * JTL::SIM::Time::instance().GetDeltaTime() * (JTL::SIM::Window::instance().GetWidth() / 2 - JTL::SIM::Input::instance().GetMouseX()));
			cam->transform->LocalRotate({ 1,0,0 }, turnspeed * JTL::SIM::Time::instance().GetDeltaTime() * (JTL::SIM::Window::instance().GetHeight() / 2 - JTL::SIM::Input::instance().GetMouseY()));
		}

	}
	JTE::instance().TermJTE();
	return 0;
}