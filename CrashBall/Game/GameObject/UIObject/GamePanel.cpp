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
GamePanel::GamePanel(json* data)
	: Panel(data)
	, m_playerMeshGauge		 (std::make_unique<Slider>(&(*data)["playerMeshGauge"]))
	, m_enemyMeshGauge		 (std::make_unique<Slider>(&(*data)["enemyMeshGauge"]))
	, m_playerMeshNumText	 (std::make_unique<TextObject>(&(*data)["playerMeshNumText"]))
	, m_enemyMeshNumText	 (std::make_unique<TextObject>(&(*data)["enemyMeshNumText"]))
	, m_gaugeBackGround		 (std::make_unique<Object2D>(&(*data)["gaugeBackGround"]))
	, m_gaugeTrack			 (std::make_unique<Object2D>(&(*data)["gaugeTrack"]))
	, m_attackGauge			 (std::make_unique<Slider>(&(*data)["attackGauge"]))
	, m_attackPowerText		 (std::make_unique<TextObject>(&(*data)["attackPowerText"]))
	, m_attackGaugeTrack	 (std::make_unique<Object2D>(&(*data)["attackGaugeTrack"]))
	, m_enemyHpGauge		 (std::make_unique<Slider>(&(*data)["enemyHpGauge"]))
	, m_enemyHpGaugeTrack	 (std::make_unique<Object2D>(&(*data)["enemyHpGaugeTrack"]))
	, m_enemyHpText			 (std::make_unique<TextObject>(&(*data)["enemyHpText"]))
{

	m_floorMeshGaugeController =
		AddComponent<FloorMeshGaugeController>(
			m_playerMeshGauge.get(),
			m_enemyMeshGauge.get(),
			m_playerMeshNumText.get(),
			m_enemyMeshNumText.get()
		);

	m_attackGaugeController =
		AddComponent<AttackGaugeController>(
			m_attackGauge.get(),
			m_attackPowerText.get()
		);

	m_enemyHpGaugeController =
		AddComponent<EnemyHpGaugeController>(
			m_enemyHpGauge.get(),
			m_enemyHpGaugeTrack.get(),
			m_enemyHpText.get()
		);

	RectTransform* rectTransform = GetComponent<RectTransform>();
	m_playerMeshGauge	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_enemyMeshGauge	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_playerMeshNumText	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_enemyMeshNumText	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_gaugeBackGround	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_gaugeTrack		->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_attackGauge		->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_attackPowerText	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_attackGaugeTrack	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_enemyHpGauge		->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_enemyHpGaugeTrack	->GetComponent<RectTransform>()->SetParent(rectTransform);
	m_enemyHpText		->GetComponent<RectTransform>()->SetParent(rectTransform);
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

void GamePanel::SaveParam()
{
	(*m_data)["rectTransform"] = *GetComponent<RectTransform>();

	(*m_data)["ObjectTag"] = GetTag();

	m_playerMeshGauge	->SaveParam();
	m_enemyMeshGauge	->SaveParam();
	m_playerMeshNumText	->SaveParam();
	m_enemyMeshNumText	->SaveParam();
	m_gaugeBackGround	->SaveParam();
	m_gaugeTrack		->SaveParam();
	m_attackGauge		->SaveParam();
	m_attackPowerText	->SaveParam();
	m_attackGaugeTrack	->SaveParam();
	m_enemyHpGauge		->SaveParam();
	m_enemyHpGaugeTrack	->SaveParam();
	m_enemyHpText		->SaveParam();
}

void GamePanel::SaveInitParam()
{
}

void GamePanel::ReloadParam()
{
	*GetComponent<RectTransform>() = (*m_data)["rectTransform"];

	SetTag((*m_data)["ObjectTag"]);

	m_playerMeshGauge->SetData(&(*m_data)["playerMeshGauge"]);
	m_enemyMeshGauge->SetData(&(*m_data)["enemyMeshGauge"]);
	m_playerMeshNumText	->SetData(&(*m_data)["playerMeshNumText"]);
	m_enemyMeshNumText	->SetData(&(*m_data)["enemyMeshNumText"]);
	m_gaugeBackGround	->SetData(&(*m_data)["gaugeBackGround"]);
	m_gaugeTrack		->SetData(&(*m_data)["gaugeTrack"]);
	m_attackGauge		->SetData(&(*m_data)["attackGauge"]);
	m_attackPowerText	->SetData(&(*m_data)["attackPowerText"]);
	m_attackGaugeTrack	->SetData(&(*m_data)["attackGaugeTrack"]);
	m_enemyHpGauge		->SetData(&(*m_data)["enemyHpGauge"]);
	m_enemyHpGaugeTrack	->SetData(&(*m_data)["enemyHpGaugeTrack"]);
	m_enemyHpText		->SetData(&(*m_data)["enemyHpText"]);

	m_playerMeshGauge->ReloadParam();
	m_enemyMeshGauge->ReloadParam();
	m_playerMeshNumText->ReloadParam();
	m_enemyMeshNumText->ReloadParam();
	m_gaugeBackGround->ReloadParam();
	m_gaugeTrack->ReloadParam();
	m_attackGauge->ReloadParam();
	m_attackPowerText->ReloadParam();
	m_attackGaugeTrack->ReloadParam();
	m_enemyHpGauge->ReloadParam();
	m_enemyHpGaugeTrack->ReloadParam();
	m_enemyHpText->ReloadParam();
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

	SpriteFont* defaultFont = textManager->GetSpriteFont("default");

	// FloorMeshGauge ==================================================

	m_gaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_enemyMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_playerMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_gaugeBackGround->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	m_playerMeshNumText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);
	m_enemyMeshNumText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);

	// AttackGauge ==================================================

	m_attackGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_attackGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	m_attackPowerText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);

	// EnemyHpGauge ==================================================

	m_enemyHpGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_enemyHpGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	m_enemyHpText
		->GetComponent<TextRenderer>()->SetSpriteFont(defaultFont);
}
