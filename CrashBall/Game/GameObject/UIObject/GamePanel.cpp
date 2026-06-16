/*****************************************************************//**
 * \file   GamePanel.cpp
 * \brief  ゲーム用のパネル
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GamePanel.h"
#include "Game/Component/Default/SpriteRenderer.h"

/**
 * \brief コンストラクタ
 * 
 */
GamePanel::GamePanel()
	: Panel()
	, m_playerMeshGauge		 (std::make_unique<Object2D>())
	, m_enemyMeshGauge		 (std::make_unique<Object2D>())
	, m_playerMeshNumText	 (std::make_unique<TextObject>())
	, m_enemyMeshNumText	 (std::make_unique<TextObject>())
	, m_gaugeBackGround		 (std::make_unique<Object2D>())
	, m_gaugeTrack			 (std::make_unique<Object2D>())
	, m_attackGauge			 (std::make_unique<Object2D>())
	, m_attackGaugeTrack		 (std::make_unique<Object2D>())
{

	m_floorMeshGaugeController =
		AddComponent<FloorMeshGaugeController>(
			m_playerMeshGauge.get(),
			m_enemyMeshGauge.get(),
			m_gaugeTrack.get(),
			m_gaugeBackGround.get(),
			m_playerMeshNumText.get(),
			m_enemyMeshNumText.get()
		);

	m_attackGaugeController =
		AddComponent<AttackGaugeController>(
			m_attackGauge.get(),
			m_attackGaugeTrack.get()
		);
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
	m_floorMeshGaugeController->Initialize();
	m_attackGaugeController->Initilize();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */ 
void GamePanel::Update(const GameContext& gameContext)
{
	m_floorMeshGaugeController->Update(gameContext);
	m_attackGaugeController->Update(gameContext);
}

/**
 * \brief 描画
 * 
 * \param RenderContext 描画用のコンテキスト
 */
void GamePanel::Render(const RenderContext& renderContext)
{
	m_enemyMeshGauge->Render(renderContext);
	m_playerMeshGauge->Render(renderContext);
	m_playerMeshNumText->Render(renderContext);
	m_enemyMeshNumText->Render(renderContext);
	m_gaugeBackGround->Render(renderContext);
	m_gaugeTrack->Render(renderContext);
	m_attackGauge->Render(renderContext);
	m_attackGaugeTrack->Render(renderContext);
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

	m_gaugeTrack->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("Gauge"));
	m_playerMeshGauge->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("Gauge"));
	m_enemyMeshGauge->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("Gauge"));
	m_gaugeBackGround->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("Gauge"));

	m_playerMeshNumText->GetComponent<TextRenderer>()
		->SetSpriteFont(textManager->GetSpriteFont("default"));
	m_enemyMeshNumText->GetComponent<TextRenderer>()
		->SetSpriteFont(textManager->GetSpriteFont("default"));

	m_attackGauge->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("AttackIcon"));
	m_attackGaugeTrack->
		GetComponent<SpriteRenderer>()->SetSprite(spriteManager->GetSprite("AttackIcon"));
}
