/*****************************************************************//**
 * \file   ButtonController.cpp
 * \brief  ボタン操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "ButtonController.h"
#include "Game/Common/Screen.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"


using namespace DirectX;

RegisterComponent(ButtonController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ButtonController::ButtonController(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void ButtonController::Awake()
{
	// キャッシュの取得
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonController::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonController::Update(const GameContext& gameContext)
{
	SimpleMath::Vector2 mousePos = Input::GetMousePos();

	//float width = m_spriteRenderer->GetWidth();
	//float height = m_spriteRenderer->GetHeight();

	//// フォーカス状態か判定
	//if( mousePos.x >= m_rectTransform->GetLeft(width)	 * Screen::GetScreenRate() &&
	//	mousePos.x <= m_rectTransform->GetRight(width)	 * Screen::GetScreenRate() &&
	//	mousePos.y >= m_rectTransform->GetTop(height)	 * Screen::GetScreenRate() &&
	//	mousePos.y <= m_rectTransform->GetBottom(height) * Screen::GetScreenRate())
	//{
	//	m_isHover = true;
	//}
	//else
	//{
	//	m_isHover = false;
	//}

	//// クリックされたか判定
	//if (m_isHover && Input::GetMouseDown(MouseButton::Left))
	//{
	//	m_isOnClick = true;
	//}

	// キーが離されたか
	//if (Input::GetMouseRelease(MouseButton::Left))
	//{
	//	// フォーカス時かつクリックされていたらフラグをオンにする
	//	if (m_isHover && m_isOnClick)
	//	{
	//		m_isPush = true;
	//	}
	//	m_isOnClick = false;
	//}

	if (Input::GetInputState(InputAction::Deside).isTrigger)
	{
		if (m_isFocus)
		{
			m_isPush = true;
		}
	}

	// 押されたときの処理の実行
	if (m_isPush)
	{
		m_onPushCommand();

		m_isPush = false;
	}

	// ドラック中の処理の実行
	if (m_isOnClick)
	{
		m_onDrugCommand();
	}

	// フォーカス中の処理の実行
	if (m_isFocus)
	{
		m_onFocusStayCommand();
	}
	// フォーカス時の処理の実行
	if (m_isFocus && !m_prevIsFocus)
	{
		m_onFocusEnterCommand();
	}
	// フォーカス離脱時の処理の実行
	else if (!m_isFocus && m_prevIsFocus)
	{
		m_onFocusExitCommand();
	}

	m_prevIsFocus = m_isFocus;
}
