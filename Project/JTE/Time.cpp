#include "RenderDeclarations.h"
#include "Time.h"

namespace JTL
{
	namespace SIM
	{
		float Time::GetTotalTime()
		{
			INIT_ASSERT(Time);
			return glfwGetTime();
		}

		float Time::GetDeltaTime()
		{
			INIT_ASSERT(Time);
			return GetTotalTime() - previousTime;
		}

		bool Time::step()
		{
			previousTime = glfwGetTime();
			INIT_ASSERT(Time); return true;
		}
	}
}