/*****************************************************************//**
 * \file   GamePanel.cpp
 * \brief  ゲーム用のパネル
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GamePanel.h"

#include "Game/ScriptableObject/Scriptable.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
GamePanel::GamePanel(ordered_json* data)
	: Panel(data)
	, m_playerMeshGauge		 (std::make_unique<Slider>(&(*data)["playerMeshGauge"]))
	, m_enemyMeshGauge		 (std::make_unique<Slider>(&(*data)["enemyMeshGauge"]))
	, m_playerMeshNumText	 (std::make_unique<TextObject>(&(*data)["playerMeshNumText"]))
	, m_enemyMeshNumText	 (std::make_unique<TextObject>(&(*data)["enemyMeshNumText"]))
	, m_gaugeBackGround		 (std::make_unique<Object2D>(&(*data)["gaugeBackGround"]))
	, m_meshGaugeTrack		 (std::make_unique<Object2D>(&(*data)["meshGaugeTrack"]))
	, m_attackGauge			 (std::make_unique<Slider>(&(*data)["attackGauge"]))
	, m_attackPowerText		 (std::make_unique<TextObject>(&(*data)["attackPowerText"]))
	, m_attackGaugeTrack	 (std::make_unique<Object2D>(&(*data)["attackGaugeTrack"]))
	, m_enemyHpGauge		 (std::make_unique<Slider>(&(*data)["enemyHpGauge"]))
	, m_enemyHpGaugeTrack	 (std::make_unique<Object2D>(&(*data)["enemyHpGaugeTrack"]))
	, m_enemyHpText			 (std::make_unique<TextObject>(&(*data)["enemyHpText"]))
{

	//m_floorMeshGaugeController =
	//	AddComponent<FloorMeshGaugeController>(
	//		m_playerMeshGauge.get(),
	//		m_enemyMeshGauge.get(),
	//		m_playerMeshNumText.get(),
	//		m_enemyMeshNumText.get()
	//	);

	////m_attackGaugeController =
	////	AddComponent<AttackGaugeController>(
	////		m_attackGauge.get(),
	////		m_attackPowerText.get()
	////	);

	//m_enemyHpGaugeController =
	//	AddComponent<EnemyHpGaugeController>(
	//		m_enemyHpGauge.get(),
	//		m_enemyHpGaugeTrack.get(),
	//		m_enemyHpText.get()
	//	);

	//RectTransform* rectTransform = GetComponent<RectTransform>();
	//for (auto& childe : GetChildren())
	//{
	//	childe->GetComponent<RectTransform>()->SetParentInBuildTime(rectTransform);
	//}
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
void GamePanel::Start(const GameContext& gameContext)
{
	m_floorMeshGaugeController->Start(gameContext);
	m_attackGaugeController->Start(gameContext);
	m_enemyHpGaugeController->Start(gameContext);
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
	m_enemyHpGaugeController->Update(gameContext);
}

/**
 * \brief 描画
 *
 * \param RenderContext 描画用のコンテキスト
 */
void GamePanel::Render(const RenderContext& renderContext)
{
}

/**
 * \brief スプライトの設定
 *
 * \param resourceContext リソース用のコンテキスト
 */
void GamePanel::SetSprite(const ResourceContext& resourceContext)
{
	ISpriteManager* spriteManager = resourceContext.spriteManager;
	ITextManager* textManager = resourceContext.textManager;

	auto gameColor = Scriptable::GetScriptableObject<GameColor>;

	// FloorMeshGauge ==================================================

	// スプライトの設定
	m_meshGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_enemyMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_playerMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_gaugeBackGround->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	//　色の設定
	//m_playerMeshGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
	//m_enemyMeshGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));

	// フォントの設定
	m_playerMeshNumText->GetComponent<TextRenderer>()->SetSpriteFont(textManager);
	m_enemyMeshNumText->GetComponent<TextRenderer>()->SetSpriteFont(textManager);

	// 色の設定
	//m_playerMeshNumText->GetComponent<TextRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
	//m_enemyMeshNumText->GetComponent<TextRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));

	// AttackGauge ==================================================

	// スプライトの設定
	m_attackGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_attackGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	// フォントの設定
	m_attackPowerText
		->GetComponent<TextRenderer>()->SetSpriteFont(textManager);

	// EnemyHpGauge ==================================================

	// スプライトの設定
	m_enemyHpGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_enemyHpGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	// 色の設定
	//m_enemyHpGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));


	// フォントの設定
	m_enemyHpText
		->GetComponent<TextRenderer>()->SetSpriteFont(textManager);
}
