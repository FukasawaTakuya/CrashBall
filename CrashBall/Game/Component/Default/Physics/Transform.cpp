
/*****************************************************************//**
 * \file   Transform.cpp
 * \brief  トランスフォーム 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Transform.h"

RegisterComponent(Transform)

/**
 * \brief コンストラクタ
 * 
 * \param コンポーネントを所有するゲームオブジェクト
 */
Transform::Transform(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief デストラクタ
 * 
 */
Transform::~Transform()
{
}

/**
 * \brief 開始処理
 * 
 * \param gameContext　ゲーム用のコンテキスト
 */
void Transform::Start(const GameContext& gameContext)
{
	UpdateWarldMat();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Transform::Update(const GameContext& gameContext)
{
	m_isDirty = false;
}

/**
 * \brief 移動
 * 
 * \param trans 移動ベクトル
 */
void Transform::Translate(const DirectX::SimpleMath::Vector3& trans)
{
	m_localPosition += trans;
	m_isDirty = true;
}

/**
 * \brief 回転
 * 
 * \param rotate クオータニオン
 */
void Transform::Rotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_localRotate *= rotate;
	m_isDirty = true;
}

/**
 * \brief ワールド行列の更新
 * 
 */
void Transform::UpdateWarldMat() const
{
	// 拡大行列
	DirectX::SimpleMath::Matrix scale
		= DirectX::SimpleMath::Matrix::CreateScale(GetWorldScale());
	// 回転行列
	DirectX::SimpleMath::Matrix rotate
		= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetWorldRotate());
	// 移動行列
	DirectX::SimpleMath::Matrix trans
		= DirectX::SimpleMath::Matrix::CreateTranslation(GetWorldPosition());

	// ワールド行列
	m_world = (scale * rotate * trans);

}
