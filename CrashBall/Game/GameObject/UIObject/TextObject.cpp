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


TextObject::TextObject(json* data)
	: GameObject(data)
{
	AddComponent<RectTransform>((*data)["rectTransform"]);
	m_textRenderer = AddComponent<TextRenderer>((*data)["textRenderer"]);
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
void TextObject::Initialize()
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
	m_textRenderer->Render(renderContext.textRendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void TextObject::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void TextObject::SaveParam()
{
	(*m_data)["rectTransform"] = *GetComponent<RectTransform>();
	(*m_data)["textRenderer"] = *GetComponent<TextRenderer>();

	(*m_data)["ObjectTag"] = GetTag();
}

void TextObject::SaveInitParam()
{
}

void TextObject::ReloadJson()
{
	*GetComponent<RectTransform>() = (*m_data)["rectTransform"];
	*GetComponent<TextRenderer>() = (*m_data)["textRenderer"];
	
	SetTag((*m_data)["ObjectTag"]);
}
