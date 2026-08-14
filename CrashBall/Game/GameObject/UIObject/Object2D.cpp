/*****************************************************************//**
 * \file   Object2D.cpp
 * \brief  2Dオブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "Object2D.h"

/**
 * \brief コンストラクタ
 * 
 */
Object2D::Object2D()
{
	AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();
}

Object2D::Object2D(json* data)
	: GameObject(data)
{
	AddComponent<RectTransform>((*data)["rectTransform"]);
	m_spriteRenderer = AddComponent<SpriteRenderer>((*data)["spriteRenderer"]);
}

/**
 * \brief デストラクタ
 * 
 */
Object2D::~Object2D()
{
}

/**
 * \brief 初期化
 * 
 */
void Object2D::Start()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Object2D::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Object2D::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->Render(renderContext.spriteRendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void Object2D::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void Object2D::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["rectTransform"] = *GetComponent<RectTransform>();
	(*m_data)["spriteRenderer"] = *GetComponent<SpriteRenderer>();
}

/**
 * \brief データの再読み込み
 * 
 */
void Object2D::ReloadParam()
{
	GameObject::ReloadParam();

	*GetComponent<RectTransform>() = (*m_data)["rectTransform"];
	*GetComponent<SpriteRenderer>() = (*m_data)["spriteRenderer"];
	SetTag((*m_data)["ObjectTag"]);
}
