/*****************************************************************//**
 * \file   GamePanel.cpp
 * \brief  ゲーム用のパネル
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GamePanel.h"
#include <Game/Component/Default/SpriteRenderer.h>

/**
 * \brief コンストラクタ
 * 
 */
GamePanel::GamePanel()
	: Panel()
	, m_floorMeshGauge(std::make_unique<FloorMeshGauge>())
{
}

/**
 * \brief デストラクタ
 * 
 */
GamePanel::~GamePanel()
{
}

/**
 * \brief 初期化
 * 
 */
void GamePanel::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */ 
void GamePanel::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param RenderContext 描画用のコンテキスト
 */
void GamePanel::Render(const RenderContext& renderContext)
{
	m_floorMeshGauge->Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void GamePanel::Finalize()
{
}

/**
 * \brief スプライトの設定
 * 
 * \param resourceContext
 */
void GamePanel::SetSprite(const ResourceContext& resourceContext)
{
	ISpriteManager* spriteManager = resourceContext.spriteManager;
	ITextManager* textManager = resourceContext.textManager;

	m_floorMeshGauge->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("UI"));

	m_floorMeshGauge->
		GetComponent<TextRenderer>()->SetSpriteFont(textManager->GetSpriteFont("default"));
}
