#include "Rigidbody2D.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		Rigidbody2D::Rigidbody2D() :
			acceleration({ 0,0 }), velocity({ 0,0 }), mass(1),
			force({ 0,0 }), drag(0), angularVelocity(0), angularAcceleration(0),
			torque(0), angularDrag(0) {}

		void Rigidbody2D::AddForce(const Vector2 &a) { force = force + a; }

		void Rigidbody2D::AddTorque(const float &a) { torque = torque + a; }

		void Rigidbody2D::Integrate(Transform *t, const float &dt)
		{
			jerk = force / mass - acceleration;
			angularJerk = torque / mass - angularAcceleration;

			acceleration = acceleration + jerk * dt;
			angularAcceleration = angularAcceleration + angularJerk * dt;

			velocity = velocity + acceleration * dt;
			angularVelocity = angularVelocity + angularAcceleration * dt;

			t->SetPosition(t->GetPosition() + Vector3{ velocity.x, velocity.y, 0 } * dt);
			t->SetRotation(t->GetRotation() * Quaternion{FWD_VEC3, angularVelocity * dt });

			velocity = velocity - velocity * drag * dt;
			angularVelocity = angularVelocity - angularVelocity * angularDrag * dt;

			force = { 0, 0 };
			torque = 0;
		}
	}
}