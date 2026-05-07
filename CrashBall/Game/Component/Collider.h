// 多重インクルードの防止 =====================================================
#pragma once

#include "Component.h"
#include "Transform.h"
#include "Game/CollisionManager/CollisionLayerMask.h"

class Sphere;
class Mesh;

enum class ColliderType
{
	None = -1,
	Sphere,
	Mesh,
};

constexpr int TYPE_COUNT = 2;

class Collider : public Component
{
protected:

	// コライダーのタイプ
	ColliderType m_type = ColliderType::None;

	// レイヤーマスク
	CollisionLayerMask m_layerMask = LayerMask::Default;

	std::function<void(Collider*)> m_onCollisionEnterCmd = [](Collider*) {};	// 衝突開始命令
	std::function<void(Collider*)> m_onCollisionStayCmd  = [](Collider*) {};	// 衝突継続命令
	std::function<void(Collider*)> m_onCollisionExitCmd  = [](Collider*) {};	// 衝突終了命令

	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Collider(ColliderType type)
		: m_type{ type }
	{
	}

	virtual ~Collider() = default;

	// 操作
public:

	virtual void DrawCollider() = 0;


	void OnCollisionEnter(Collider* other) {
		m_onCollisionEnterCmd(other);
	};

	void OnCollisionStay(Collider* other) {
		m_onCollisionStayCmd(other);
	};

	void OnCollisionExit(Collider* other) {
		m_onCollisionExitCmd(other);
	};

	// 取得 / 設定
public:

	CollisionLayerMask GetLayerMask() const { return m_layerMask; }

	ColliderType GetType() const { return m_type; }

	void SetLayerMask(CollisionLayerMask layerMask){ m_layerMask = layerMask; }

	void SetOnCollisionEnterCmd(std::function<void(Collider*)> cmd) { m_onCollisionEnterCmd = cmd; }

	void SetOnCollisionStayCmd(std::function<void(Collider*)> cmd)  { m_onCollisionStayCmd = cmd; }

	void SetOnCollisionExitCmd(std::function<void(Collider*)> cmd)  { m_onCollisionExitCmd = cmd; }
};

