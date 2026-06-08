#include <pch.h>
#include "Collider.h"
#include "Game/GameObject/GameObject.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param owner
 * \param type
 */
Collider::Collider(
	IGameObject* owner,
	ColliderType type)
	: Component(owner)
	, m_type{ type }
{
	m_transform = GetGameObject()->GetComponent<Transform>();
}

/**
 * \brief 衝突時の処理の実行
 * 
 * \param other 衝突したコライダー
 */
void Collider::OnCollisionEnter(Collider* other)
{
	for (auto& cmd : m_onCollisionEnterCmd) {
		cmd(other);
	}
}

/**
 * \brief 衝突中の処理の実行
 * 
 * \param other 衝突したコライダー
 */
void Collider::OnCollisionStay(Collider* other)
{
	for (auto& cmd : m_onCollisionStayCmd) {
		cmd(other);
	}
}

/**
 * \brief 衝突から抜けた時の処理の実行
 * 
 * \param other 衝突したコライダー
 */
void Collider::OnCollisionExit(Collider* other)
{
	for (auto& cmd : m_onCollisionExitCmd) {
		cmd(other);
	}
}

/**
 * \brief 衝突中のオブジェクトに追加
 * 
 * \param collider コライダー
 */
void Collider::AddCollideObject(Collider* collider)
{
	m_collideObject.insert(collider);
}

/**
 * \brief 衝突中のオブジェクトから削除
 * 
 * \param collider コライダー
 */
void Collider::EraseCollideObject(Collider* collider)
{
	if (m_collideObject.find(collider) != m_collideObject.end())
	{
		m_collideObject.erase(collider);
	}
}

/**
 * \brief 衝突中のオブジェクトか調べる
 * 
 * \param collider コライダー
 * \return 
 */
bool Collider::IsCollideObject(Collider* collider) const
{
	return (m_collideObject.find(collider) != m_collideObject.end());
}
