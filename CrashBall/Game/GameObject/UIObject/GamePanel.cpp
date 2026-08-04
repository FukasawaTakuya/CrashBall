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
GamePanel::GamePanel(json* data)
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

	AddChildren(m_playerMeshGauge.get());
	AddChildren(m_enemyMeshGauge.get());
	AddChildren(m_playerMeshNumText.get());
	AddChildren(m_enemyMeshNumText.get());
	AddChildren(m_gaugeBackGround.get());
	AddChildren(m_meshGaugeTrack.get());
	AddChildren(m_attackGauge.get());
	AddChildren(m_attackPowerText.get());
	AddChildren(m_attackGaugeTrack.get());
	AddChildren(m_enemyHpGauge.get());
	AddChildren(m_enemyHpGaugeTrack.get());
	AddChildren(m_enemyHpText.get());

	RectTransform* rectTransform = GetComponent<RectTransform>();
	for (auto& childe : GetChildren())
	{
		childe->GetComponent<RectTransform>()->SetParentInBuildTime(rectTransform);
	}
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
	m_floorMeshGaugeController->Start();
	m_attackGaugeController->Initilize();
	m_enemyHpGaugeController->Start();
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

	UpdateChildren(gameContext);
}

/**
 * \brief 描画
 *
 * \param RenderContext 描画用のコンテキスト
 */
void GamePanel::Render(const RenderContext& renderContext)
{
	RenderChildren(renderContext);
}

/**
 * \brief 終了処理
 *
 */
void GamePanel::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void GamePanel::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["rectTransform"] = *GetComponent<RectTransform>();

	m_playerMeshGauge		->SetData(&(*m_data)["playerMeshGauge"]);
	m_enemyMeshGauge		->SetData(&(*m_data)["enemyMeshGauge"]);
	m_playerMeshNumText		->SetData(&(*m_data)["playerMeshNumText"]);
	m_enemyMeshNumText		->SetData(&(*m_data)["enemyMeshNumText"]);
	m_gaugeBackGround		->SetData(&(*m_data)["gaugeBackGround"]);
	m_meshGaugeTrack		->SetData(&(*m_data)["meshGaugeTrack"]);
	m_attackGauge			->SetData(&(*m_data)["attackGauge"]);
	m_attackPowerText		->SetData(&(*m_data)["attackPowerText"]);
	m_attackGaugeTrack		->SetData(&(*m_data)["attackGaugeTrack"]);
	m_enemyHpGauge			->SetData(&(*m_data)["enemyHpGauge"]);
	m_enemyHpGaugeTrack		->SetData(&(*m_data)["enemyHpGaugeTrack"]);
	m_enemyHpText			->SetData(&(*m_data)["enemyHpText"]);

	m_enemyMeshGauge	->SaveParam();
	m_playerMeshNumText	->SaveParam();
	m_enemyMeshNumText	->SaveParam();
	m_gaugeBackGround	->SaveParam();
	m_meshGaugeTrack	->SaveParam();
	m_attackGauge		->SaveParam();
	m_attackPowerText	->SaveParam();
	m_attackGaugeTrack	->SaveParam();
	m_enemyHpGauge		->SaveParam();
	m_enemyHpGaugeTrack	->SaveParam();
	m_enemyHpText		->SaveParam();
	m_playerMeshGauge	->SaveParam();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void GamePanel::ReloadParam()
{
	GameObject::ReloadParam();

	*GetComponent<RectTransform>() = (*m_data)["rectTransform"];

	m_playerMeshGauge	->SetData(&(*m_data)["playerMeshGauge"]);
	m_enemyMeshGauge	->SetData(&(*m_data)["enemyMeshGauge"]);
	m_playerMeshNumText	->SetData(&(*m_data)["playerMeshNumText"]);
	m_enemyMeshNumText	->SetData(&(*m_data)["enemyMeshNumText"]);
	m_gaugeBackGround	->SetData(&(*m_data)["gaugeBackGround"]);
	m_meshGaugeTrack	->SetData(&(*m_data)["meshGaugeTrack"]);
	m_attackGauge		->SetData(&(*m_data)["attackGauge"]);
	m_attackPowerText	->SetData(&(*m_data)["attackPowerText"]);
	m_attackGaugeTrack	->SetData(&(*m_data)["attackGaugeTrack"]);
	m_enemyHpGauge		->SetData(&(*m_data)["enemyHpGauge"]);
	m_enemyHpGaugeTrack	->SetData(&(*m_data)["enemyHpGaugeTrack"]);
	m_enemyHpText		->SetData(&(*m_data)["enemyHpText"]);

	m_playerMeshGauge	->ReloadParam();
	m_enemyMeshGauge	->ReloadParam();
	m_playerMeshNumText	->ReloadParam();
	m_enemyMeshNumText	->ReloadParam();
	m_gaugeBackGround	->ReloadParam();
	m_meshGaugeTrack	->ReloadParam();
	m_attackGauge		->ReloadParam();
	m_attackPowerText	->ReloadParam();
	m_attackGaugeTrack	->ReloadParam();
	m_enemyHpGauge		->ReloadParam();
	m_enemyHpGaugeTrack	->ReloadParam();
	m_enemyHpText		->ReloadParam();
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

	auto gameColor = Scriptable::GetScriptableObject("gameColor");

	// FloorMeshGauge ==================================================

	// スプライトの設定
	m_meshGaugeTrack->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_enemyMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_playerMeshGauge->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_gaugeBackGround->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	//　色の設定
	m_playerMeshGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
	m_enemyMeshGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));

	// フォントの設定
	m_playerMeshNumText->GetComponent<TextRenderer>()->SetSpriteFont(textManager);
	m_enemyMeshNumText->GetComponent<TextRenderer>()->SetSpriteFont(textManager);

	// 色の設定
	m_playerMeshNumText->GetComponent<TextRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
	m_enemyMeshNumText->GetComponent<TextRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));

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
	m_enemyHpGauge->GetComponent<SpriteRenderer>()->SetColor(gameColor->GetValue<SimpleMath::Color>("EnemyColor"));


	// フォントの設定
	m_enemyHpText
		->GetComponent<TextRenderer>()->SetSpriteFont(textManager);
}
