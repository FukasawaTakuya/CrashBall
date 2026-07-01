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
	m_buttonController = AddComponent<ButtonController>();
}

Button::Button(json* data)
	: GameObject(data)
{
	m_rectTransform = AddComponent<RectTransform>((*data)["rectTransform"]);
	m_spriteRenderer = AddComponent<SpriteRenderer>((*data)["spriteRenderer"]);
	m_textRenderer = AddComponent<TextRenderer>((*data)["textRenderer"]);
	m_buttonController = AddComponent<ButtonController>();
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
	m_buttonController->Update();
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

/**
 * \brief パラメータの書き込み
 * 
 */
void Button::SaveParam()
{
	(*m_data)["rectTransform"] = *m_rectTransform;
	(*m_data)["spriteRenderer"] = *m_spriteRenderer;
	(*m_data)["textRenderer"] = *m_textRenderer;
}

/**
 * \brief 初期化時のパラメータの書き込み
 *
 */
void Button::SaveInitParam()
{
}

/**
 * \brief パラメータの再読み込み
 *
 */
void Button::ReloadParam()
{
	*m_rectTransform = (*m_data)["rectTransform"];
	*m_spriteRenderer = (*m_data)["spriteRenderer"];
	*m_textRenderer = (*m_data)["textRenderer"];
}
