#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Component.h"
#include <list>

namespace JTL
{
	namespace SIM
	{
		class Transform : public Component<Transform>
		{
			Transform *parent;
			std::list<Transform*> children;
			Vector3 position, scale;
			Quaternion rotation;

		public:
			Transform();
			~Transform();

			Matrix4 GetGlobalTransform() const;
			Matrix4 GetLocalTransform() const;
			
			void		SetParent	(Transform*);

			void		SetPosition	(const Vector3&);
			void		SetScale	(const Vector3&);
			void		SetRotation	(const Quaternion&);

			Vector3		GetPosition	();
			Vector3		GetScale	();
			Quaternion	GetRotation ();
		
			void Rotate(const Vector3 &axis, const float &angle);
			void LocalRotate(const Vector3 &axis, const float &angle);
			void LookAt(const Vector3 &target, const Vector3 &up);
			Quaternion GetLookAtRotation(const Vector3 &target, const Vector3 &up);

			Vector3		GetForward	() const;
			Vector3		GetRight	() const;
			Vector3		GetUp		() const;
		};
	}
}