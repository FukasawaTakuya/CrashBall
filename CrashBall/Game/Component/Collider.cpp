#include <pch.h>
#include "Collider.h"
#include "Game/GameObject/GameObject.h"

using namespace DirectX;

Collider::Collider(
	IGameObject* owner,
	ColliderType type)
	: Component(owner)
	, m_type{ type }
{
	m_transform = m_owner->GetComponent<Transform>();
}