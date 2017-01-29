#pragma once
#include "Entity.h"

namespace JTL
{
	namespace SIM
	{
		class System
		{
			virtual bool condition(Handle<Entity> i) = 0;
			virtual bool update(Handle<Entity> i) = 0;
			virtual void onStep() {}

		public:
			void step()
			{
				onStep();
				for (unsigned i = 0; i < Entity::getData().size(); ++i)
					if (Entity::at(i).isValid() && condition(i))
						update(i);
			}
		};

		class BinarySystem
		{
			virtual bool condition(Handle<Entity> i) = 0;
			virtual void update(Handle<Entity> i, Handle<Entity> j) = 0;
			virtual void onStep() {}

		public:
			void step()
			{
				onStep();
				for (unsigned i = 0; i < Entity::getData().size() - 1; ++i)
					for (unsigned j = i + 1; j < Entity::getData().size(); ++j)
						if (Entity::at(i).isValid() && condition(i)
							&& Entity::at(j).isValid() && condition(j))
							update(i, j);
			}
		};
	}
}