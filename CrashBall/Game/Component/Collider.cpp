#include <pch.h>
#include "Collider.h"
#include "Game/GameObject/GameObject.h"

using namespace DirectX;

Collider::Collider(ColliderType type)
	: m_type{ type }
{
	// SetOwner前に呼ばれるためエラー
	//m_transform = m_owner->GetComponent<Transform>();
}