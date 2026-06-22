/*****************************************************************//**
 * \file   Button.h
 * \brief  ボタン
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "Button.h"

/**
 * \brief コンストラクタ
 * 
 */
Button::Button()
{
	m_rectTransform  = AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();
	m_textRenderer	 = AddComponent<TextRenderer>();
	m_controller	 = AddComponent<ButtonController>();
}

/**
 * \brief デストラクタ
 * 
 */
Button::~Button()
{
}

/**
 * \brief 初期化
 * 
 */
void Button::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Button::Update(const GameContext& gameContext)
{
	m_controller->Update();
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Button::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->Render(renderContext.spriteRendererManager);
	m_textRenderer->Render(renderContext.textRendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void Button::Finalize()
{
}
