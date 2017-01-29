#pragma once
#include "Vector2.h"
#include "Transform.h"
#include "Component.h"

namespace JTL
{
	namespace SIM
	{
		class Rigidbody2D : public Component<Rigidbody2D>
		{
		public:
			Rigidbody2D();
			
			Vector2 velocity, acceleration, force, jerk, gravity;
			float	angularVelocity, angularAcceleration, torque, 
					angularJerk, angularDrag, mass, drag;
		
			void AddForce	(const Vector2&);
			void AddTorque	(const float&);
			void Integrate	(Transform*, const float &dt);
		};
	}
}