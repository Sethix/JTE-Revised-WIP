#include "RenderDeclarations.h"
#include "RenderStructures.h"
#include "Window.h"
#include "Assets.h"
#include "Camera.h"
#include "Entity.h"

void WindowSizeCallback(GLFWwindow *w, int pWidth, int pHeight)
{
	JTL::SIM::Window::instance().SetWidth(pWidth);
	JTL::SIM::Window::instance().SetHeight(pHeight);

	glViewport(0, 0, pWidth, pHeight);

	for each (JTL::SIM::Entity e in JTL::SIM::Entity::getData())
	{
		if (e.camera > -1)
		{
			JTL::SIM::Assets::instance().frameBuffers[e.camera->gFrame].Resize(pWidth, pHeight);
			JTL::SIM::Assets::instance().frameBuffers[e.camera->lFrame].Resize(pWidth, pHeight);
			JTL::SIM::Assets::instance().frameBuffers[e.camera->sFrame].Resize(pWidth, pHeight);
			e.camera->cameraOut.width = pWidth;
			e.camera->cameraOut.height = pHeight;
		}
	}
}

namespace JTL
{
	namespace SIM
	{
		bool Window::init(int Width, int Height, const char* Title, bool resizeable, bool fullscreen)
		{
			isInit = glfwInit();

			if (resizeable) glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
			else glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			if (fullscreen) renderWindow = glfwCreateWindow(Width, Height, Title, glfwGetPrimaryMonitor(), nullptr);
			else renderWindow = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);

			glfwMakeContextCurrent(renderWindow);

			glewExperimental = GL_TRUE;
			glewInit();

			glfwSwapInterval(1);

			width = Width;
			height = Height;

			glfwSetWindowSizeCallback(renderWindow, WindowSizeCallback);

			glViewport(0, 0, width, height);

			return isInit;
		}

		bool Window::step()
		{
			glfwSwapBuffers(renderWindow);
			glfwPollEvents();

			glfwGetFramebufferSize(renderWindow, &width, &height);

			glClearColor(0.f, 0.f, 0.f, 0.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			return !glfwWindowShouldClose(renderWindow) && !exit;
		}

		void Window::term()
		{
			glfwWindowShouldClose(renderWindow);
			glfwTerminate();
		}
	}
}