/*****************************************************************//**
 * \file   Object2D.cpp
 * \brief  2Dオブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "Object2D.h"
#include "Game/Component/Default/Physics/RectTransform.h"

/**
 * \brief コンストラクタ
 * 
 */
Object2D::Object2D()
{
	AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();
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
void Object2D::Initialize()
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

void Object2D::SaveParam()
{
}

void Object2D::SaveInitParam()
{
}

void Object2D::ReloadJson()
{
}
