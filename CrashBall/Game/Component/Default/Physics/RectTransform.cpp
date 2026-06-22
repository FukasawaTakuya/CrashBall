/*****************************************************************//**
 * \file   RectTransform.h
 * \brief  2Dのトランスフォームコンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "RectTransform.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
RectTransform::RectTransform(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param rectTransform レクトトランスフォーム
 */
RectTransform::RectTransform(
	IGameObject* gameObject,
	const RectTransform& rectTransform)
	: Component(gameObject)
	, m_position(rectTransform.m_position)
	, m_rotate	(rectTransform.m_rotate)
	, m_scale	(rectTransform.m_scale)
	, m_origin	(rectTransform.m_origin)
{
}

/**
 * \brief デストラクタ
 * 
 */
RectTransform::~RectTransform()
{
}

/**
 * \brief 移動
 * 
 * \param trans 移動ベクトル
 */
void RectTransform::Translate(DirectX::SimpleMath::Vector2 trans)
{
	m_position += trans;
}

/**
 * \brief 回転
 * 
 * \param ratate 回転角度
 */
void RectTransform::Rotate(float rotate)
{
	m_rotate += rotate;
}
