#include "pch.h"
#include "SliderController.h"
#include "Game/Engine/Time.h"

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
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
SliderController::SliderController(
	IGameObject* gameObject, 
	const SliderController& other)
	: Component(gameObject)
	, m_slideSpeed(other.m_slideSpeed)
	, m_targetAmount()
{
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
}

/**
 * \brief デストラクタ
 * 
 */
SliderController::~SliderController()
{
}

void SliderController::Slide()
{
	float fillAmount =
		std::lerp(m_spriteRenderer->GetFillAmount(), m_targetAmount, Time::GetElapsedTime() * m_slideSpeed);

	m_spriteRenderer->SetFillAmount(fillAmount);
}
