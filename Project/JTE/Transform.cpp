#include "Transform.h"

namespace JTL
{
	namespace SIM
	{
		Transform::Transform()
			: parent(nullptr),
			scale({ 1,1 }),
			position({ 0,0 }),
			rotation(ID_QUAT) { }


		Transform::~Transform()
		{
			auto t = children;
			for each(Transform *child in t)
				child->SetParent(parent);

			SetParent(nullptr);
		}

		void Transform::SetParent(Transform *a_parent)
		{
			if (parent)
				parent->children.remove(this);

			if (a_parent)
				a_parent->children.push_front(this);

			parent = a_parent;
		}

		Matrix4 Transform::GetGlobalTransform() const
		{
			return
				Translation(position)
				* rotation.RotationMatrix()
				* Scale(scale)
				* (parent ? parent->GetGlobalTransform()
					: ID_MAT4);
		}

		Matrix4 Transform::GetLocalTransform() const
		{
			return
				Translation(position)
				* rotation.RotationMatrix()
				* Scale(scale);
		}

		void Transform::SetPosition(const Vector3&p)
		{
			position = p;
		}
		void Transform::SetScale(const Vector3&s)
		{
			scale = s;
		}
		void Transform::SetRotation(const Quaternion&r)
		{
			rotation = r;
		}

		Vector3	Transform::GetPosition()
		{
			return position;
		}
		Vector3	Transform::GetScale()
		{
			return scale;
		}

		Quaternion Transform::GetRotation()
		{
			return rotation;
		}

		void Transform::Rotate(const Vector3 &axis, const float &angle)
		{
			rotation = Quaternion(axis, angle) * rotation.Normalized();
		}

		void Transform::LocalRotate(const Vector3 &axis, const float &angle)
		{
			rotation = rotation.Normalized() * Quaternion(axis, angle);
		}


		void Transform::LookAt(const Vector3 &target, const Vector3 &up)
		{
			rotation = GetLookAtRotation(target, up);
		}

		Quaternion Transform::GetLookAtRotation(const Vector3 &target, const Vector3 &up)
		{
			return Rotation(Normalized(target - position), up);
		}

		Vector3	Transform::GetForward() const
		{
			return rotation.Forward();
		}

		Vector3	Transform::GetRight() const
		{
			return rotation.Right();
		}
		Vector3	Transform::GetUp() const
		{
			return rotation.Up();
		}
	}
}