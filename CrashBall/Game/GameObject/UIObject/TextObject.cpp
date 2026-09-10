/*****************************************************************//**
 * \file   TextObject.cpp
 * \brief  テキスト描画オブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "TextObject.h"

/**
 * \brief コンストラクタ
 * 
 */
TextObject::TextObject()
{
	AddComponent<RectTransform>();
	m_textRenderer = AddComponent<TextRenderer>();
}


TextObject::TextObject(ordered_json* data)
	: GameObject(data)
{
	//AddComponent<RectTransform>((*data)["rectTransform"]);
	//m_textRenderer = AddComponent<TextRenderer>((*data)["textRenderer"]);
}


/**
 * \brief デストラクタ
 * 
 */
TextObject::~TextObject()
{
}

/**
 * \brief 初期化
 * 
 */
void TextObject::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void TextObject::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void TextObject::Render(const RenderContext& renderContext)
{
	m_textRenderer->Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void TextObject::Finalize()
{
}
