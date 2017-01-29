#pragma once
#include "Vector3.h"
#include "SystemStructure.h"
#include "CollisionData.h"
#include "Entity.h"

namespace JTL
{
	namespace SIM
	{

		struct Collision2D
		{
			Handle<Entity> first, second;
			CollisionData collision;

			static std::vector<Collision2D> &getData()
			{
				static std::vector<Collision2D> data;
				return data;
			}
		};

		class Collision2DSystem
		{
			virtual bool condition(Collision2D &a) = 0;
			virtual void update(Collision2D &a) = 0;
			virtual void onStep() {}
		public:
			void step()
			{
				onStep();
				for each(Collision2D c in Collision2D::getData())
					if (condition(c) == true)
						update(c);
			}
		};

		class Collision2DDetection : public BinarySystem
		{
			void onStep() { Collision2D::getData().clear(); }

			bool condition(Handle<Entity> i) { return i->transform > -1 && i->collider2D > -1; }

			void update(Handle<Entity> i, Handle<Entity> j)
			{
				auto cd = CollisionDetected(*i->transform, *i->collider2D, *j->transform, *j->collider2D);
				if (cd.penDepth > 0) Collision2D::getData().push_back(Collision2D{ i,j,cd });
			}
		};
	}
}