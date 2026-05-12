// 多重インクルードの防止 =====================================================
#pragma once

#include "Component.h"
#include "Transform.h"
#include "Game/CollisionManager/CollisionLayerMask.h"

// コライダータイプ
enum class ColliderType
{
	None = -1,
	Sphere,
	Mesh,
};

// タイプ数
constexpr int TYPE_COUNT = 2;

/**
 * \brief 基底コライダー
 */
class Collider : public Component
{
	// 衝突時処理
	using CollisionCmd = std::function<void(Collider*)>;

protected:

	
	ColliderType m_type = ColliderType::None;								// コライダーのタイプ

	CollisionLayerMask m_layerMask = LayerMask::Default;					// レイヤーマスク

	std::vector<CollisionCmd> m_onCollisionEnterCmd = { [](Collider*) {} };	// 衝突開始命令
	std::vector<CollisionCmd> m_onCollisionStayCmd  = { [](Collider*) {} };	// 衝突継続命令
	std::vector<CollisionCmd> m_onCollisionExitCmd  = { [](Collider*) {} };	// 衝突終了命令

	bool m_isCollide = false;												// 衝突しているか

	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Collider(ColliderType type)
		: m_type{ type }
	{
		SetOnCollisionEnterCmd([this](Collider*)
			{
				m_isCollide = true;
			});

		SetOnCollisionExitCmd([this](Collider*)
			{
				m_isCollide = false;
			});
	}

	// デストラクタ
	virtual ~Collider() = default;

	// 操作
public:

	virtual void DrawCollider() = 0;

	void OnCollisionEnter(Collider* other) {
		for (auto& cmd : m_onCollisionEnterCmd) {
			cmd(other);
		}
	};

	void OnCollisionStay(Collider* other) {
		for (auto& cmd : m_onCollisionStayCmd) {
			cmd(other);
		}
	};

	void OnCollisionExit(Collider* other) {
		for (auto& cmd : m_onCollisionExitCmd) {
			cmd(other);
		}
	};

	// 取得 / 設定
public:

	CollisionLayerMask GetLayerMask() const { return m_layerMask; }

	ColliderType GetType() const { return m_type; }

	bool GetIsCollide() const { return m_isCollide; }

	void SetLayerMask(CollisionLayerMask layerMask){ m_layerMask = layerMask; }

	void SetOnCollisionEnterCmd(CollisionCmd cmd) { m_onCollisionEnterCmd.push_back(cmd); }

	void SetOnCollisionStayCmd(CollisionCmd cmd)  { m_onCollisionStayCmd.push_back(cmd); }

	void SetOnCollisionExitCmd(CollisionCmd cmd)  { m_onCollisionExitCmd.push_back(cmd); }
};

