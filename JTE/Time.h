#pragma once
#include "Window.h"

namespace JTL
{
	namespace SIM
	{
		class Time
		{
			bool isInit;
			Time() : isInit(false) {}

			double previousTime;

		public:
			static Time &instance() { static Time instance; return instance; }

			float GetTotalTime();
			float GetDeltaTime();

			bool init() { return isInit = Window::instance().isInitialized(); }
			bool step();
			void term() { INIT_ASSERT(Time); }

			bool isInitialized() { return isInit; }
		};
	}
}