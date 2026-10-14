/*****************************************************************//**
 * \file   ButtonManager.cpp
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "ButtonManager.h"

RegisterComponent(ButtonManager)
#include "Game/Engine/Input.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 *
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return
 */
ButtonManager::ButtonManager(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 *
 */
void ButtonManager::Awake()
{
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonManager::Start(const GameContext& gameContext)
{
	m_currentButton = m_firstButton;
	m_currentButton->SetIsFocus(true);
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonManager::Update(const GameContext& gameContext)
{
	float valueX = Input::GetInputState(InputAction::UIMoveX).value;
	float valueY = Input::GetInputState(InputAction::UIMoveY).value;

	if (valueX >= 0.5f)
	{
		m_nextButton = m_currentButton->GetRightButton();
	}
	else if (valueX <= -0.5f)
	{
		m_nextButton = m_currentButton->GetLeftButton();
	}
	if (valueY >= 0.5f)
	{
		m_nextButton = m_currentButton->GetTopButton();
	}
	else if (valueY <= -0.5f)
	{
		m_nextButton = m_currentButton->GetBottomButton();
	}

	if (m_nextButton != nullptr)
	{
		m_currentButton->SetIsFocus(false);
		m_currentButton = m_nextButton;
		m_currentButton->SetIsFocus(true);
		m_nextButton = nullptr;
	}
}
