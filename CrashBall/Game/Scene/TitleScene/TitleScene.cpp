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

#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/ScriptableObject/Scriptable.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param pSceneChanger シーン変更インターフェース
 */
TitleScene::TitleScene(
	ISceneChanger* pSceneChanger,
	IJsonDataManager* jsonDataManager)
	: Scene(pSceneChanger, jsonDataManager)
	, m_camera(std::make_unique<TitleCamera>(jsonDataManager->GetJsonData("titleCamera")))
	, m_player(std::make_unique<Player>(jsonDataManager->GetJsonData("titlePlayer")))
	, m_stage(std::make_unique<Stage>(jsonDataManager->GetJsonData("stage")))
	, m_titleLogo(std::make_unique<TitleLogo>(jsonDataManager->GetJsonData("titleLogo")))
	, m_startButton(std::make_unique<Button>(jsonDataManager->GetJsonData("startButton")))
{
	// ターゲットのセット
	m_camera->GetComponent<TitleCameraController>()->SetTargetTransform(
		m_player->GetComponent<Transform>()
	);

	// 押したときの処理の設定
	m_startButton->GetComponent<ButtonController>()
		->SetOnPushCommand([&]()
			{
				m_pSceneChanger->RequestChangeScene(SceneID::Game);
			});

	m_gameColor = Scriptable::GetScriptableObject("gameColor");

	m_gameObjects.push_back(m_camera.get());
	m_gameObjects.push_back(m_player.get());
	m_gameObjects.push_back(m_stage.get());
	m_gameObjects.push_back(m_titleLogo.get());
	m_gameObjects.push_back(m_startButton.get());

	m_sceneName = "TitleScene";
}

/**
 * \brief デストラクタ
 *
 */
TitleScene::~TitleScene()
{
}

/**
 * \brief 遷移時の処理
 * 
 * \param resourceContext リソース用のコンテキスト
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleScene::OnEnter(
	const ResourceContext& resourceContext, 
	const GameContext& gameContext)
{
	CreateDeviceResources(resourceContext);
	gameContext.soundManager->RegisterPlayBgmCommand("title");
}

/**
 * \brief 初期化
 *
 */
void TitleScene::Initialize()
{
	m_camera->Start();
	m_stage->Start();
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleScene::Update(const GameContext& gameContext)
{
	if (Input::GetKeyTrigger(Keyboard::Space))
	{
		m_pSceneChanger->RequestChangeScene(SceneID::Game);
	}

	m_camera->Update(gameContext);
	m_startButton->Update(gameContext);
	m_titleLogo->Update(gameContext);
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
	m_titleLogo->Render(renderContext);
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

	playerRenderer->SetModel(resourceContext.modelManager);
	playerRenderer->SetDiffuseColor(m_gameColor->GetValue<SimpleMath::Color>("PlayerColor"));

	ISpriteManager* spriteManager = resourceContext.spriteManager;

	m_titleLogo->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);
	m_startButton->GetComponent<SpriteRenderer>()->SetSprite(spriteManager);

	m_startButton->GetComponent<TextRenderer>()->SetSpriteFont(resourceContext.textManager);
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 *
 * \param proj 射影行列
 */
void TitleScene::CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj)
{
}

/**
 * \brief パラメータの書き込み
 *
 */
void TitleScene::SaveParam()
{
	m_player->SaveParam();
	m_titleLogo->SaveParam();
	m_startButton->SaveParam();
	m_camera->SaveParam();
}

/**
 * \brief パラメータの再読み込み
 *
 */
void TitleScene::ReloadParam()
{
	m_player->ReloadParam();
	m_titleLogo->ReloadParam();
	m_startButton->ReloadParam();
	m_camera->ReloadParam();
}
