#include "RenderDeclarations.h"
#include "Window.h"
#include "Input.h"
#include <cstring>

namespace JTL
{
	namespace SIM
	{
		bool Input::init()
		{
			memset(keyRelease, 0, NUM_OF_KEYS);
			memset(keyPress, 0, NUM_OF_KEYS);
			memset(mouseRelease, 0, NUM_OF_MOUSE_BTNS);
			memset(mousePress, 0, NUM_OF_MOUSE_BTNS);
			memset(joyRelease, 0, NUM_OF_JOY_BTNS * NUM_OF_JOYSTICKS);
			memset(joyPress, 0, NUM_OF_JOY_BTNS * NUM_OF_JOYSTICKS);
			memset(joyAxes, 0, NUM_OF_JOY_AXES * NUM_OF_JOYSTICKS);

			activeJoysticks = 0;

			for (unsigned i = 0; i < NUM_OF_JOYSTICKS; ++i)
				if (glfwJoystickPresent(i) == GL_TRUE) activeJoysticks++;

			mouseX = mouseY = 0;

			return isInit = Window::instance().isInitialized();
		}

		bool Input::step()
		{
			INIT_ASSERT(Input);

			int count;

			for (unsigned i = 0; i < NUM_OF_KEYS; ++i)
			{
				keyState[i] = keyPress[i] > keyRelease[i];

				if (glfwGetKey(Window::instance().renderWindow, i) == GLFW_PRESS) keyPress[i] = glfwGetTime();
				else														keyRelease[i] = glfwGetTime();
			}

			for (unsigned i = 0; i < NUM_OF_MOUSE_BTNS; ++i)
			{
				mouseState[i] = mousePress[i] > mouseRelease[i];

				if (glfwGetMouseButton(Window::instance().renderWindow, i) == GLFW_PRESS) mousePress[i] = glfwGetTime();
				else																mouseRelease[i] = glfwGetTime();
			}

			for (unsigned i = 0; i < activeJoysticks; ++i)
			{
				for (unsigned j = 0; j < NUM_OF_JOY_BTNS; ++j)
				{
					joyState[i][j] = joyPress[i][j] > joyRelease[i][j];

					if (glfwGetJoystickButtons(i, &count)[j] == GLFW_PRESS) joyPress[i][j] = glfwGetTime();
					else													joyRelease[i][j] = glfwGetTime();
				}
			}

			double x, y;
			glfwGetCursorPos(Window::instance().renderWindow, &x, &y);

			mouseX = x;
			mouseY = y;

			if (Window::instance().lockMouse) ResetCursor();

			for (unsigned i = 0; i < activeJoysticks; ++i)
				for (unsigned j = 0; j < NUM_OF_JOY_AXES; ++j)
					joyAxes[i][j] = glfwGetJoystickAxes(i, &count)[j];

			return false;
		}

		bool Input::GetKey(unsigned key) { INIT_ASSERT(Input); return keyPress[key] > keyRelease[key]; }
		bool Input::GetKeyPress(unsigned key) { INIT_ASSERT(Input); return GetKey(key) && !keyState[key]; }
		bool Input::GetKeyRelease(unsigned key) { INIT_ASSERT(Input); return !GetKey(key) && keyState[key]; }

		float Input::KeyDelta(unsigned key) { INIT_ASSERT(Input); return keyPress[key] - keyRelease[key]; }

		bool Input::GetMouseButton(unsigned key) { INIT_ASSERT(Input); return mousePress[key] > mouseRelease[key]; }
		bool Input::GetMouseButtonPress(unsigned key) { INIT_ASSERT(Input); return GetMouseButton(key) && !mouseState[key]; }
		bool Input::GetMouseButtonRelease(unsigned key) { INIT_ASSERT(Input); return !GetMouseButton(key) && mouseState[key]; }

		int Input::GetActiveJoysticks() { INIT_ASSERT(Input); return activeJoysticks; }

		float Input::GetJoyAxis(int joy, unsigned axis) { INIT_ASSERT(Input); return joyAxes[joy][axis]; }
		bool Input::GetJoy(int joy, unsigned key) { INIT_ASSERT(Input); return joyPress[joy][key] > joyRelease[joy][key]; }
		bool Input::GetJoyPress(int joy, unsigned key) { INIT_ASSERT(Input); return GetJoy(joy, key) && !joyState[joy][key]; }
		bool Input::GetJoyRelease(int joy, unsigned key) { INIT_ASSERT(Input); return !GetJoy(joy, key) && joyState[joy][key]; }

		float Input::GetMouseX() { INIT_ASSERT(Input); return mouseX; }
		float Input::GetMouseY() { INIT_ASSERT(Input); return mouseY; }

		void Input::ResetCursor()
		{
			glfwSetCursorPos(Window::instance().renderWindow, Window::instance().width / 2, Window::instance().height / 2);

			if (GetMouseButtonPress(1))
			{
				mouseX = Window::instance().width / 2;
				mouseY = Window::instance().height / 2;
			}
		}
	}
}