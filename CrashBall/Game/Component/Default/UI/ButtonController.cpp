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

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ButtonController::ButtonController(IGameObject* gameObject)
	: Component(gameObject)
{
	// キャッシュの取得
	m_rectTransform  = GetGameObject()->GetComponent<RectTransform>();
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();

	GetGameObject()->GetComponent<TextRenderer>()->SetColor(Colors::Black);
}

/**
 * \brief デストラクタ
 * 
 */
ButtonController::~ButtonController()
{
}

/**
 * \brief 更新
 * 
 */
void ButtonController::Update()
{
	SimpleMath::Vector2 mousePos = Input::GetMousePos();

	float width = m_spriteRenderer->GetWidth()  ;
	float height = m_spriteRenderer->GetHeight();

	m_prevIsHover = m_isHover;

	// ホバー状態か判定
	if( mousePos.x >= m_rectTransform->GetLeft(width)	 * Screen::GetScreenRate() &&
		mousePos.x <= m_rectTransform->GetRight(width)	 * Screen::GetScreenRate() &&
		mousePos.y >= m_rectTransform->GetTop(height)	 * Screen::GetScreenRate() &&
		mousePos.y <= m_rectTransform->GetBottom(height) * Screen::GetScreenRate())
	{
		m_isHover = true;
	}
	else
	{
		m_isHover = false;
	}

	// クリックされたか判定
	if (m_isHover && Input::GetMouseTrigger(MouseButton::Left))
	{
		m_isOnClick = true;
	}

	// キーが離されたか
	if (Input::GetMouseRelease(MouseButton::Left))
	{
		// ホバー時かつクリックされていたらフラグをオンにする
		if (m_isHover && m_isOnClick)
		{
			m_isPush = true;
		}
		m_isOnClick = false;
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

	// ホバー中の処理の実行
	if (m_isHover)
	{
		m_onHoverStayCommand();
	}
	// ホバー時の処理の実行
	if (m_isHover && !m_prevIsHover)
	{
		m_onHoverEnterCommand();
	}
	// ホバー離脱時の処理の実行
	else if (!m_isHover && m_prevIsHover)
	{
		m_onHoverExitCommand();
	}
}
