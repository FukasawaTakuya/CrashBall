/*****************************************************************//**
 * \file   SliderController.cpp
 * \brief  スライダー操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "SliderController.h"
#include "Game/Engine/Time.h"

RegisterComponent(SliderController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
SliderController::SliderController(IGameObject* gameObject)
	: Component(gameObject)
	, m_slideSpeed()
	, m_targetAmount()
{
}

/**
 * \brief デストラクタ
 * 
 */
SliderController::~SliderController()
{
}

/**
 * \brief アタッチ時の処理
 *
 */
void SliderController::Awake()
{
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
}


/**
 * \brief スライド
 * 
 */
void SliderController::Slide()
{
	float fillAmount =
		std::lerp(m_spriteRenderer->GetFillAmount(), m_targetAmount, Time::GetElapsedTime() * m_slideSpeed);

	m_spriteRenderer->SetFillAmount(fillAmount);
}

