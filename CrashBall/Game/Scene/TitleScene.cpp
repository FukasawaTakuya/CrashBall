/*****************************************************************//**
 * \file   TitleScene.cpp
 * \brief  タイトルシーン
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"

#include "TitleScene.h"
#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"

#include "Game/Component/Camera/TargetCamera.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param pSceneController シーン変更インターフェース
 */
TitleScene::TitleScene(
	ISceneController* pSceneController,
	IJsonDataManager* jsonDataManager)
	: Scene(pSceneController, jsonDataManager)
	, m_camera(std::make_unique<TitleCamera>())
	, m_player(std::make_unique<Player>(jsonDataManager->GetJsonData("player")))
	, m_stage(std::make_unique<Stage>())
	, m_titleSprite(std::make_unique<Object2D>())
	, m_startButton(std::make_unique<Button>())
{
	m_camera->GetComponent<TargetCamera>()->SetTargetTransform(
		m_player->GetComponent<Transform>()
	);

	m_player->GetComponent<Transform>()->SetPosition({ 0.0f, 10.25f, 0.0f });

	m_titleSprite->GetComponent<RectTransform>()->SetPosition(
		TITLE_INIT_POS
	);

	m_titleSpriteTransform = m_titleSprite->GetComponent<RectTransform>();
	m_titleSpriteTransform->SetScale(1.3f);



	m_startButton->GetComponent<RectTransform>()
		->SetPosition({ 800.0f, 500.0f });

	m_startButton->GetComponent<ButtonController>()
		->SetOnDrugCommand([&]()
			{
				m_pSceneController->RequestChangeScene(SceneID::Game);
			});
}

/**
 * \brief デストラクタ
 * 
 */
TitleScene::~TitleScene()
{
}

/**
 * \brief 初期化
 * 
 */
void TitleScene::Initialize()
{
	m_camera->Initialize();
	m_stage->Initialize();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleScene::Update(const GameContext& gameContext)
{
	if (Input::GetKeyDown(Keyboard::Space))
	{
		m_pSceneController->RequestChangeScene(SceneID::Game);
	}

	if (m_radian >= 360.0f)
	{
		m_radian = 0.0f;
	}

	m_radian += Time::GetElapsedTime();

	m_titleSpriteTransform->SetPosition(
		TITLE_INIT_POS + SimpleMath::Vector2(0.0f, std::sin(m_radian) * 20.0f)
	);

	m_camera->Update(gameContext);
	m_startButton->Update(gameContext);
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void TitleScene::Render(const RenderContext& renderContext)
{
	m_player->Render(renderContext);
	m_stage->Render(renderContext);
	m_titleSprite->Render(renderContext);
	m_startButton->Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void TitleScene::Finalize()
{
}

/**
 * \brief デバイス依存のリソース作成
 * 
 * \param resourceContext リソース用のコンテキスト
 */
void TitleScene::CreateDeviceResources(const ResourceContext& resourceContext)
{
	ModelRenderer* playerRenderer = m_player->GetComponent<ModelRenderer>();

	playerRenderer->SetModel(resourceContext.modelManager->GetModel("player"));
	playerRenderer->SetDiffuseColor(GameColor::PLAYER);

	ISpriteManager* spriteManager = resourceContext.spriteManager;

	m_titleSprite->GetComponent<SpriteRenderer>()->SetSpriteKey("Title");
	m_startButton->GetComponent<SpriteRenderer>()->SetSpriteKey("Button");

	m_titleSprite->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_startButton->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	m_startButton->GetComponent<TextRenderer>()->SetSpriteFont(
		resourceContext.textManager->GetSpriteFont("default")
	);

	m_startButton->GetComponent<TextRenderer>()->SetText(L"START");
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 * 
 * \param proj 射影行列
 */
void TitleScene::CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj)
{
}
