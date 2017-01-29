#pragma once
#include "Vector3.h"
#include "SystemStructure.h"
#include "CollisionData.h"
#include "Entity.h"

namespace JTL
{
	namespace SIM
	{

		struct Collision3D
		{
			Handle<Entity> first, second;
			CollisionData collision;

			static std::vector<Collision3D> &getData()
			{
				static std::vector<Collision3D> data;
				return data;
			}
		};

		class Collision3DSystem
		{
			virtual bool condition(Collision3D &a) = 0;
			virtual void update(Collision3D &a) = 0;
			virtual void onStep() {}
		public:
			void step()
			{
				onStep();
				for each(Collision3D c in Collision3D::getData())
					if (condition(c) == true)
						update(c);
			}
		};

		class Collision3DDetection : public BinarySystem
		{
			void onStep() { Collision3D::getData().clear(); }

			bool condition(Handle<Entity> i) { return i->transform > -1 && i->collider3D > -1; }

			void update(Handle<Entity> i, Handle<Entity> j)
			{
				auto cd = CollisionDetected(*i->transform, *i->collider2D, *j->transform, *j->collider2D);
				if (cd.penDepth > 0) Collision3D::getData().push_back(Collision3D{ i,j,cd });
			}
		};
	}
}