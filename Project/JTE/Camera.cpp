#include "RenderStructures.h"
#include "RenderDeclarations.h"
#include "RenderUtilities.h"
#include "Camera.h"
#include "Matrix3.h"
#include "Window.h"
#include "Entity.h"
#include "Assets.h"
#include <string>

namespace JTL
{
	namespace SIM
	{
		Camera::Camera()
		{
			bool isFtex[] = { false, true, false, true };

			gFrame = "gFrame" + std::to_string(getIndex());
			lFrame = "lFrame" + std::to_string(getIndex());
			sFrame = "sFrame" + std::to_string(getIndex());
			aoFrame = "aoFrame" + std::to_string(getIndex());

			int g = 1;

			Assets::instance().makeFrameBuffer(gFrame.c_str(), Window::instance().GetWidth(), Window::instance().GetHeight(), 4, isFtex);
			
			Assets::instance().makeFrameBuffer(lFrame.c_str(), Window::instance().GetWidth(), Window::instance().GetHeight(), 3);

			Assets::instance().makeFrameBuffer(sFrame.c_str(), Window::instance().GetWidth(), Window::instance().GetHeight(), 1);

			Assets::instance().makeFrameBuffer(aoFrame.c_str(), Window::instance().GetWidth(), Window::instance().GetHeight(), 1,(bool*)&g, (int*)&g);

			cameraOut.handle = 0;
			cameraOut.width = Window::instance().GetWidth();
			cameraOut.height = Window::instance().GetHeight();

			screenSpace = { 1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1 };
		};

		Matrix4 Camera::View()
		{
			return Inverse(transform->GetGlobalTransform());
		}

		Matrix4 Camera::Orthographic()
		{
			float halfW, halfH;
			halfW = Window::instance().GetWidth() / 2;
			halfH = Window::instance().GetHeight() / 2;
			return OrthographicProjection(-halfW, halfW, -halfH, halfH, nearClipPlane, farClipPlane);
		}

		Matrix4 Camera::Perspective()
		{
			return PerspectiveProjection(Window::instance().GetWidth(), Window::instance().GetHeight(), FOV, nearClipPlane, farClipPlane);
		}

		void Camera::update()
		{
			Matrix4 lightProj = OrthographicProjection(-10, 10, -10, 10, -10, 10);

			clearFrameBuffer(cameraOut);

			glViewport(0, 0, JTL::SIM::Window::instance().GetWidth(), JTL::SIM::Window::instance().GetHeight());

			for each (Entity e in Entity::getData())
			{
				if (e.sprite > -1 && e.transform > -1)
				{

				}
			}

			clearFrameBuffer(Assets::instance().frameBuffers[gFrame]);
			
			for each (Entity e in Entity::getData())
			{
				if (e.model > -1 && e.transform > -1)
				{ 
					Assets::instance().draw(Assets::instance().geometry[e.model->mesh],
						Assets::instance().shaders[e.model->shader],
						Assets::instance().frameBuffers[gFrame],
						e.transform->GetGlobalTransform(),
						View(), Perspective(),
						Assets::instance().textures[e.model->albedo],
						Assets::instance().textures[e.model->normal],
						Assets::instance().textures[e.model->specular]);
				}
			}

			//clearFrameBuffer(Assets::instance().frameBuffers[aoFrame]);

			/*Assets::instance().draw(Assets::instance().geometry["quad"],
				Assets::instance().shaders["SSAO"],
				Assets::instance().frameBuffers[aoFrame], Assets::instance().frameBuffers[gFrame].tex[1],
				Assets::instance().frameBuffers[gFrame].tex[2], Assets::instance().textures["RandNorms"]);*/

			clearFrameBuffer(Assets::instance().frameBuffers[lFrame]);

			for each (Entity e in Entity::getData())
			{
				if (e.light > -1 && e.transform > -1)
				{ 
						/*Assets::instance().draw(Assets::instance().geometry["quad"],
							Assets::instance().shaders["litPass"],
							Assets::instance().frameBuffers[lFrame], View(),
							Assets::instance().frameBuffers[gFrame].tex[0], Assets::instance().frameBuffers[gFrame].tex[1], 
							Assets::instance().frameBuffers[gFrame].tex[2], Assets::instance().frameBuffers[gFrame].tex[3],
							Assets::instance().frameBuffers[gFrame].depth, e.transform->GetForward(), e.light->color);*/
					
					clearFrameBuffer(Assets::instance().frameBuffers[sFrame]);

					for each (Entity se in Entity::getData())
					{
						if (se.model > -1 && se.transform > -1)
						{
							Assets::instance().draw(Assets::instance().geometry[se.model->mesh],
								Assets::instance().shaders["sPass"],
								Assets::instance().frameBuffers[sFrame],
								se.transform->GetGlobalTransform(),
								Inverse(e.transform->GetGlobalTransform()), lightProj);
						}
					}

					Assets::instance().draw(Assets::instance().geometry["quad"],
						Assets::instance().shaders["ltsPass"],
						Assets::instance().frameBuffers[lFrame], View(),
						Assets::instance().frameBuffers[gFrame].tex[0], Assets::instance().frameBuffers[gFrame].tex[1],
						Assets::instance().frameBuffers[gFrame].tex[2], Assets::instance().frameBuffers[gFrame].tex[3],
						Assets::instance().frameBuffers[sFrame].depth, e.light->color, Inverse(e.transform->GetGlobalTransform()), lightProj);
				}
			}

			//if(skybox.length() > 0)
				Assets::instance().draw(Assets::instance().geometry["skybox"], Assets::instance().shaders["skybox"],
										cameraOut, Perspective(), View(), Assets::instance().textures[skybox]);

			/*for(int i = 0; i < 4; ++i)
				Assets::instance().draw(Assets::instance().geometry["quad"],
										Assets::instance().shaders["postProcess"],
										cameraOut, gFrame.tex[i]);*/

			/*Assets::instance().draw(Assets::instance().geometry["quad"],
									Assets::instance().shaders["postProcess"],
									cameraOut, gFrame.depth);*/

			Assets::instance().draw(Assets::instance().geometry["quad"],
				Assets::instance().shaders["sobel"],
				cameraOut, Assets::instance().frameBuffers[gFrame].depth);

			for (int i = 0; i < 3; ++i)
			{
				Assets::instance().draw(Assets::instance().geometry["quad"],
					Assets::instance().shaders["postProcess"],
					cameraOut, Assets::instance().frameBuffers[lFrame].tex[i], Assets::instance().frameBuffers[gFrame].depth);
			}

			/*Assets::instance().draw(Assets::instance().geometry["quad"],
				Assets::instance().shaders["postProcess"],
				cameraOut, Assets::instance().frameBuffers[aoFrame].tex[0]);*/

			/*Assets::instance().draw(Assets::instance().geometry["quad"],
				Assets::instance().shaders["sobel"],
				cameraOut, Assets::instance().frameBuffers[gFrame].depth);*/
		}
	}
}