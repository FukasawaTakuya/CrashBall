// 多重インクルードの防止 =====================================================
#pragma once

#include "Component.h"
#include "Transform.h"
#include "Game/CollisionManager/CollisionLayerMask.h"

class Sphere;
class Mesh;

enum class ColliderType
{
	None,
	Sphere,
	Plane,
	Trianle,
	Segment,
	Mesh,
};

class Collider : public Component
{
protected:

	ColliderType m_type = ColliderType::None;

	// レイヤーマスク
	CollisionLayerMask m_layerMask = LayerMask::DefaultLayerMask;

	// コンストラクタ/デストラクタ
public:

	Collider(ColliderType type)
		: m_type{ type }
	{}

	virtual ~Collider() = default;

	// 操作
public:

	virtual void DrawCollider()  = 0;

	virtual bool OnCollide(Collider* collider) = 0;

	virtual bool OnCollideWith(Sphere* sphere) = 0;

	virtual bool OnCollideWith(Mesh* mash) = 0;

	// 取得 / 設定
public:

	CollisionLayerMask GetLayerMask() const { return m_layerMask; }

	ColliderType GetColliderType() const { return m_type; }

	void SetLayerMask(CollisionLayerMask layerMask)
	{
		m_layerMask = layerMask;
	}
};

