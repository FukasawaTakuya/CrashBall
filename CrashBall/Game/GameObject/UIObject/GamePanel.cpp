/*****************************************************************//**
 * \file   GamePanel.cpp
 * \brief  ゲーム用のパネル
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GamePanel.h"

using namespace DirectX;

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
	, m_attackPowerText		 (std::make_unique<TextObject>())
	, m_attackGaugeTrack	 (std::make_unique<Object2D>())
	, m_enemyHpGauge		 (std::make_unique<Object2D>())
	, m_enemyHpGaugeTrack	 (std::make_unique<Object2D>())
	, m_enemyHpText			 (std::make_unique<TextObject>())
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
			m_attackGaugeTrack.get(),
			m_attackPowerText.get()
		);

	m_enemyHpGaugeController =
		AddComponent<EnemyHpGaugeController>(
			m_enemyHpGauge.get(),
			m_enemyHpGaugeTrack.get(),
			m_enemyHpText.get()
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
	m_enemyHpGaugeController->Initialize();
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GamePanel::Update(const GameContext& gameContext)
{
	// UIの数値を設定
	m_floorMeshGaugeController->SetUIValue(
		m_playerMeshCount,
		m_enemyMeshCount,
		m_totalMeshCount);
	m_attackGaugeController->SetUIValue(
		m_playerMeshCount,
		m_playerAttackCost,
		m_playerAttackPower
	);
	m_enemyHpGaugeController->SetUIValue(
		m_enemyHp,
		m_enemyMaxHp
	);

	m_floorMeshGaugeController->Update();
	m_attackGaugeController->Update();
	m_enemyHpGaugeController->Update();
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
	m_attackPowerText->Render(renderContext);

	m_enemyHpGauge->Render(renderContext);
	m_enemyHpGaugeTrack->Render(renderContext);
	m_enemyHpText->Render(renderContext);
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

	ID3D11ShaderResourceView* gaugeSprite =
		spriteManager->GetSprite("Gauge");
	ID3D11ShaderResourceView* attakcIconSprite =
		spriteManager->GetSprite("AttackIcon");
	SpriteFont* defaultFont = textManager->GetSpriteFont("default");


	m_gaugeTrack->
		GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);
	m_playerMeshGauge->
		GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);
	m_enemyMeshGauge->
		GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);
	m_gaugeBackGround->
		GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);

	m_playerMeshNumText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);
	m_enemyMeshNumText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);

	m_attackGauge->
		GetComponent<SpriteRenderer>()->SetSprite(attakcIconSprite);
	m_attackGaugeTrack->
		GetComponent<SpriteRenderer>()->SetSprite(attakcIconSprite);
	m_attackPowerText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);

	m_enemyHpGauge
		->GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);
	m_enemyHpGaugeTrack
		->GetComponent<SpriteRenderer>()->SetSprite(gaugeSprite);
	m_enemyHpText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);
}
