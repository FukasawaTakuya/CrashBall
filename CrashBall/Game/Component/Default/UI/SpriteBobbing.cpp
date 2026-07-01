/*****************************************************************//**
 * \file   SpriteBobbing.cpp
 * \brief  スプライトを浮遊させるコンポーネント
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/


#include "pch.h"
#include "SpriteBobbing.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
SpriteBobbing::SpriteBobbing(IGameObject* gameObject)
	: Component(gameObject)
	, m_amplitude()
	, m_frequency()
	, m_radian()
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
	m_initPos = m_rectTransform->GetLocalPosition();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
SpriteBobbing::SpriteBobbing(
	IGameObject* gameObject, 
	const SpriteBobbing& other)
	: Component(gameObject)
	, m_amplitude(other.m_amplitude)
	, m_frequency(other.m_frequency)
	, m_initPos(other.m_initPos)
	, m_radian()
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
	m_initPos = m_rectTransform->GetLocalPosition();
}

/**
 * \brief デストラクタ
 * 
 */
SpriteBobbing::~SpriteBobbing()
{
}

/**
 * \brief 浮遊
 * 
 */
void SpriteBobbing::Bobbing()
{
	// 角度の加算
	m_radian += XM_2PI / m_frequency * Time::GetElapsedTime();

	// オーバーフロー防止
	if (m_radian >= XM_2PI)
	{
		m_radian = 0.0f;
	}

	m_rectTransform->SetLocalPosition(
		SimpleMath::Vector2(m_initPos.x, m_initPos.y + std::sin(m_radian) * m_amplitude)
	);
}
