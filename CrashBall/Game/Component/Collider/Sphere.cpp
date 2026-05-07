#include "pch.h"
#include "Sphere.h"

#include "Game/CollisionManager/Collision.h"

Sphere::Sphere(Transform* transform, float radius)
	: Collider(ColliderType::Sphere)
	, m_radius{ radius }
	, m_transform{ transform }
{
}
