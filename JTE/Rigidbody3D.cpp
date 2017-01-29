#include "Rigidbody3D.h"
#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		Rigidbody3D::Rigidbody3D() :
			acceleration({ 0,0 }), velocity({ 0,0 }), mass(1),
			force({ 0,0 }), drag(0), angularVelocity({0,0,0}), angularAcceleration({ 0,0,0 }),
			torque({ 0,0,0 }), angularDrag(0) {}

		void Rigidbody3D::AddForce(const Vector3 &a) { force = force + a; }

		void Rigidbody3D::AddTorque(const Vector3 &a) { torque = torque + a; }

		void Rigidbody3D::Integrate(Transform *t, const float &dt)
		{
			jerk = force / mass - acceleration;
			angularJerk = torque / mass - angularAcceleration;

			acceleration = acceleration + jerk * dt;
			angularAcceleration = angularAcceleration + angularJerk * dt;

			velocity = velocity + acceleration * dt;
			angularVelocity = angularVelocity + angularAcceleration * dt;

			t->SetPosition(t->GetPosition() + Vector3{ velocity.x, velocity.y, velocity.z } *dt);

			Quaternion r = t->GetRotation() * Quaternion(RGT_VEC3, angularVelocity.x * dt);
			t->SetRotation(r);

			Quaternion u = t->GetRotation() * Quaternion(UP_VEC3, angularVelocity.y * dt);
			t->SetRotation(u);

			Quaternion f = t->GetRotation() * Quaternion(FWD_VEC3, angularVelocity.z * dt);
			t->SetRotation(f);

			velocity = velocity - velocity * drag * dt;
			angularVelocity = angularVelocity - angularVelocity * angularDrag * dt;

			force = { 0,0,0 };
			torque = { 0,0,0 };
		}
	}
}