/*****************************************************************//**
 * \file   Collider.h
 * \brief  基底コライダー 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

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


	ColliderType m_type = ColliderType::None;			// コライダーのタイプ

	CollisionLayerMask m_layerMask = LayerMask::Default;// レイヤーマスク

	std::vector<CollisionCmd> m_onCollisionEnterCmd = { [](Collider*) {} };	// 衝突開始命令
	std::vector<CollisionCmd> m_onCollisionStayCmd  = { [](Collider*) {} };	// 衝突継続命令
	std::vector<CollisionCmd> m_onCollisionExitCmd  = { [](Collider*) {} };	// 衝突終了命令

	std::unordered_set<Collider*> m_collideObject;							// 衝突しているオブジェクト

	Transform* m_transform = nullptr;	// トランスフォーム

	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Collider(IGameObject* owner, ColliderType type);

	// デストラクタ
	virtual ~Collider() = default;

	// 操作
public:

	// コライダーの描画
	virtual void DrawCollider() = 0;

	// 衝突検知時の処理の実行
	void OnCollisionEnter(Collider* other) {
		for (auto& cmd : m_onCollisionEnterCmd) {
			cmd(other);
		}
	};

	// 衝突検知中の処理の実行
	void OnCollisionStay(Collider* other) {
		for (auto& cmd : m_onCollisionStayCmd) {
			cmd(other);
		}
	};

	// 衝突から抜けた時の処理の実行
	void OnCollisionExit(Collider* other) {
		for (auto& cmd : m_onCollisionExitCmd) {
			cmd(other);
		}
	};

	// 衝突中のオブジェクトに追加
	void AddCollideObject(Collider* collider)
	{
		m_collideObject.insert(collider);
	}

	// 衝突中のオブジェクトから削除
	void EraseCollideObject(Collider* collider)
	{
		if (m_collideObject.find(collider) != m_collideObject.end())
		{
			m_collideObject.erase(collider);
		}
	}

	// 衝突中のオブジェクトか調べる
	bool IsCollideObject(Collider* collider) const
	{
		return (m_collideObject.find(collider) != m_collideObject.end());
	}


	// 取得 / 設定
public:

	// レイヤーマスクの取得
	CollisionLayerMask GetLayerMask() const { return m_layerMask; }

	ColliderType GetType() const { return m_type; }

	// トランスフォームの取得
	Transform* GetTransform() { return m_transform; }

	void SetTransform(Transform* transfrom) { m_transform = transfrom; }

	void SetLayerMask(CollisionLayerMask layerMask){ m_layerMask = layerMask; }

	void SetOnCollisionEnterCmd(CollisionCmd cmd) { m_onCollisionEnterCmd.push_back(cmd); }

	void SetOnCollisionStayCmd(CollisionCmd cmd)  { m_onCollisionStayCmd.push_back(cmd); }

	void SetOnCollisionExitCmd(CollisionCmd cmd)  { m_onCollisionExitCmd.push_back(cmd); }
};

