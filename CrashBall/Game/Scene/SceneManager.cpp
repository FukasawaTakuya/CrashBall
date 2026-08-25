/*****************************************************************//**
 * \file   SceneManager.cpp
 * \brief  シーン管理
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include <fstream>

/**
 * \brief コンストラクタ
 * 
 * \param gameContext ゲーム用のコンテキスト
 * \param renderContext 描画用のコンテキスト
 * \param resourceContext リソース用のコンテキスト
 * \param jsonDataManager json管理 
 */
SceneManager::SceneManager(
	const GameContext*		gameContext,
	const RenderContext*	renderContext,
	const ResourceContext*	resourceContext,
	IJsonDataManager* jsonDataManager)
	: m_gameContext(gameContext)
	, m_renderContext(renderContext)
	, m_resourceContext(resourceContext)
	, m_jsonDataManager(jsonDataManager)
	, m_pCurrentScene(nullptr)
	, m_pRequestScene(nullptr)
	, m_changeScreen(std::make_unique<FadeChangeScreen>())
{
}

/**
 * \brief デストラクタ
 * 
 */
SceneManager::~SceneManager()
{
}

/**
 * \brief 最初のシーンのセット
 * 
 */
void SceneManager::SetStartScene()
{
	m_pCurrentScene = m_scenes[SceneID::Title].get();
	// 新シーンの遷移時の処理
	m_pCurrentScene->OnEnter(
		*m_resourceContext,
		*m_gameContext
	);
	m_changeScreen->StartFadeIn();
}

/**
 * \brief 初期化
 * 
 */
void SceneManager::Initialize()
{
	m_pCurrentScene->Start(*m_gameContext);
}

/**
 * \brief 更新
 * 
 */
void SceneManager::Update()
{
	// 変更リクエストがnullじゃないなら変更
	if (m_pRequestScene) 
	{
		// フェードアウトが完了したら
		if (!m_changeScreen->GetIsFadeOut())
		{
			// シーン遷移
			ChangeScene();
			// フェードイン開始
			m_changeScreen->StartFadeIn();
		}
	}

	// シーン遷移スクリーンの更新
	m_changeScreen->Update(*m_gameContext);

	m_current->Update(*m_gameContext);

	// 更新
	if (m_pCurrentScene) {
		m_pCurrentScene->Update(*m_gameContext);
	}
}

/**
 * \brief描画
 * 
 */
void SceneManager::Render()
{
	if (m_pCurrentScene) m_pCurrentScene->Render(*m_renderContext);

	//m_changeScreen->Render(*m_renderContext);
}

/**
 * \brief デバイス依存のリソース作成
 * 
 */
void SceneManager::CreateDeviceResources()
{
	if(m_pCurrentScene) m_pCurrentScene->CreateDeviceResources(*m_resourceContext);

	m_changeScreen->GetComponent<SpriteRenderer>()->SetSpriteKey("Screen");
	m_changeScreen->GetComponent<SpriteRenderer>()->SetSprite(m_resourceContext->spriteManager);
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 * 
 * \param proj 射影行列
 */
void SceneManager::CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj)
{
	for (auto& scene : m_scenes)
	{
		scene.second->CreateWindowSizeResources(proj);
	}
}

/**
 * \brief シーン変更のリクエスト
 * 
 * \param nextSceneID 次のシーンのID
 */
void SceneManager::RequestChangeScene(SceneID nextSceneID)
{
	// フェードインが終わっていなければリターン
	if (m_changeScreen->GetIsFadeIn()) return;

	if (m_pRequestScene != nullptr) return;

	auto it = m_scenes.find(nextSceneID);
	// シーンが未登録
	if (it != m_scenes.end())
	{
		// 登録されたリクエストシーンを取得
		m_pRequestScene = it->second.get();

		// フェードアウト開始
		m_changeScreen->StartFadeOut();
	}
}

/**
 * \brief パラメータの書き込み
 * 
 */
void SceneManager::SaveParam()
{
	m_pCurrentScene->SaveParam();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void SceneManager::ReloadParam()
{
	m_pCurrentScene->ReloadParam();
}

/**
 * \brief データの読み込み
 * 
 */
void SceneManager::LoadData()
{
	std::ifstream ifs("Resources/Data/Scenes.json");
	ordered_json data;
	ifs >> data;

	for (auto& scene : data["scenes"])
	{
		auto jsonManager = std::make_unique<JsonDataManager>();
		std::string sceneName = scene;
		std::string path = "Resources/Data/Objects/" + sceneName;

		for (auto& entity : std::filesystem::recursive_directory_iterator(path))
		{
			jsonManager->LoadGameObject(entity.path().string());
		}

		//jsonManager->LoadPlayManager("Resources/Data/PlayManager/" + scene);
		m_jsonManagers.emplace(scene, std::move(jsonManager));
	}

	m_current = std::make_unique<Scene>(this, m_jsonManagers["TitleScene"].get());
}

void SceneManager::SetScene(const std::string& sceneName)
{
	auto it = m_jsonManagers.find(sceneName);
	if (it != m_jsonManagers.end())
	{
		auto scene = std::make_unique<Scene>(this, it->second.get());
	}
}

/**
 * \brief シーン変更
 * 
 */
void SceneManager::ChangeScene()
{
	// 現シーンの終了処理
	m_pCurrentScene->Finalize();

	// シーン切り替え
	m_pCurrentScene = m_pRequestScene;

	// 新シーンの遷移時の処理
	m_pCurrentScene->OnEnter(
		*m_resourceContext,
		*m_gameContext
	);

	// 新シーンの初期化
	m_pCurrentScene->Start(*m_gameContext);

	// リクエストを削除
	m_pRequestScene = nullptr;
}
