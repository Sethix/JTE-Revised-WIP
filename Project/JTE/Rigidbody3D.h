#pragma once
#include "Vector3.h"
#include "Component.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		class Rigidbody3D : public Component<Rigidbody3D>
		{
		public:
			Rigidbody3D();

			Vector3 velocity, acceleration, force, jerk,
					angularVelocity, angularAcceleration, torque,
					angularJerk, gravity;
			float	angularDrag, mass, drag;

			void AddForce(const Vector3&);
			void AddTorque(const Vector3&);
			void Integrate(Transform*, const float &dt);
		};
	}
}