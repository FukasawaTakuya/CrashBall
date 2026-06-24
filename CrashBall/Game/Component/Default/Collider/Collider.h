/*****************************************************************//**
 * \file   Collider.h
 * \brief  基底コライダー 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/CollisionManager/CollisionLayerMask.h"

// コライダータイプ
enum class ColliderType
{
	None = -1,
	Sphere,
	Mesh,
	TypeCount,
};

// タイプ数
constexpr int TYPE_COUNT = static_cast<int>(ColliderType::TypeCount);

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

	std::unordered_set<Collider*> m_collideObject;	// 衝突しているオブジェクト

	Transform* m_transform = nullptr;	// トランスフォーム

	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Collider() = default;

	// コンストラクタ
	Collider(IGameObject* gameObject, ColliderType type);

	// デストラクタ
	virtual ~Collider() = default;

	// 操作
public:

	// コライダーの描画
	virtual void DrawCollider() = 0;

	// 衝突検知時の処理の実行
	void OnCollisionEnter(Collider* other);

	// 衝突検知中の処理の実行
	void OnCollisionStay(Collider* other);

	// 衝突から抜けた時の処理の実行
	void OnCollisionExit(Collider* other);

	// 衝突中のオブジェクトに追加
	void AddCollideObject(Collider* collider);

	// 衝突中のオブジェクトから削除
	void EraseCollideObject(Collider* collider);

	// 衝突中のオブジェクトか調べる
	bool IsCollideObject(Collider* collider) const;

	// 取得/設定
public:

	// レイヤーマスクの取得
	CollisionLayerMask GetLayerMask() const { return m_layerMask; }

	ColliderType GetType() const { return m_type; }

	// トランスフォームの取得
	Transform* GetTransform() { return m_transform; }

	// トランスフォームの取得
	void SetTransform(Transform* transfrom) { m_transform = transfrom; }

	// レイヤーマスクの取得
	void SetLayerMask(CollisionLayerMask layerMask){ m_layerMask = layerMask; }

	// 衝突時の処理の設定
	void SetOnCollisionEnterCmd(CollisionCmd cmd) { m_onCollisionEnterCmd.push_back(cmd); }

	// 衝突中の処理の設定
	void SetOnCollisionStayCmd(CollisionCmd cmd)  { m_onCollisionStayCmd.push_back(cmd); }

	// 衝突から抜けた時の処理の設定
	void SetOnCollisionExitCmd(CollisionCmd cmd)  { m_onCollisionExitCmd.push_back(cmd); }
};

