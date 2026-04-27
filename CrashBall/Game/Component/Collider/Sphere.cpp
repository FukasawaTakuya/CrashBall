#include "pch.h"
#include "Sphere.h"

#include "Game/CollisionManager/Collision.h"

Sphere::Sphere(Transform* transform, float radius)
	: Collider(ColliderType::Sphere)
	, m_radius{ radius }
	, m_transform{ transform }
{
}

bool Sphere::OnCollide(Collider* collider)
{
	return collider->OnCollideWith(this);
}


bool Sphere::OnCollideWith(Sphere* sphere)
{
	return Collision::IsCollision(this, sphere);
}

bool Sphere::OnCollideWith(Mesh* mesh)
{
	return Collision::IsCollision(this, mesh);
}