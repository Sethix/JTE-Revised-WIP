#pragma once
#define INIT_ASSERT(name) assert(isInit && #name "not initialized!")
#include <assert.h>
#include "Settings.h"
#include "glfw3.h"

namespace JTL
{
	namespace SIM
	{

		class Window
		{
			bool isInit, exit;
			int width, height;
			Window() : isInit(false), exit(false) {}

#ifdef GL
			GLFWwindow *renderWindow;
#endif // GL

			friend class Input;

		public:

			bool lockMouse;

			static Window &instance() { static Window instance; return instance; }
			bool init(int Width = 800, int Height = 600, const char* Title = "JTL::TEST.EXE",
					  bool resizeable = false, bool fullscreen = false);
			bool step();
			void term();

			void Exit() { exit = true; }

			int GetWidth() { INIT_ASSERT(Window); return width; }
			int GetHeight() { INIT_ASSERT(Window); return height; }

			void SetWidth(int w) { INIT_ASSERT(Window); width = w; }
			void SetHeight(int h) { INIT_ASSERT(Window); height = h; }

			bool	 isInitialized() { return isInit; }
		};

	}
}