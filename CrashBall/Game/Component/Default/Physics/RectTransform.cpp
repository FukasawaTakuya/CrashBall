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
	, m_localPosition(rectTransform.m_localPosition)
	, m_localRotate	(rectTransform.m_localRotate)
	, m_localScale	(rectTransform.m_localScale)
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
void RectTransform::Translate(const DirectX::SimpleMath::Vector2& trans)
{
	m_localPosition += trans;
}

/**
 * \brief 回転
 * 
 * \param ratate 回転角度
 */
void RectTransform::Rotate(float rotate)
{
	m_localRotate += rotate;
}
