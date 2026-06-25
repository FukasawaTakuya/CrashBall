#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: m_pCurrentScene{ nullptr }
	, m_pRequestScene{ nullptr }
	, m_changeScreen(std::make_unique<FadeChangeScreen>())
{
}

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
	Initialize();
	m_changeScreen->StartFadeIn();
}

/**
 * \brief 初期化
 * 
 */
void SceneManager::Initialize()
{
	m_pCurrentScene->Initialize();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SceneManager::Update(const GameContext& gameContext)
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

	m_changeScreen->Update(gameContext);

	// 更新
	if (m_pCurrentScene) {
		m_pCurrentScene->Update(gameContext);
	}
}

/**
 * \brief描画
 * 
 * \param renderCotext 描画用のコンテキスト
 */
void SceneManager::Render(const RenderContext& renderCotext)
{
	if (m_pCurrentScene) m_pCurrentScene->Render(renderCotext);

	m_changeScreen->Render(renderCotext);
}

/**
 * \brief デバイス依存のリソース作成
 * 
 * \param resourceCotext リソース用のコンテキスト
 */
void SceneManager::CreateDeviceResources(const ResourceContext& resourceCotext)
{
	for (auto& scene : m_scenes)
	{
		scene.second->CreateDeviceResources(resourceCotext);
	}


	m_changeScreen->GetComponent<SpriteRenderer>()->SetSpriteKey("Screen");

	m_changeScreen->GetComponent<SpriteRenderer>()->SetSprite(resourceCotext.spriteManager);
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

		m_changeScreen->StartFadeOut();
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

	// 新シーンの初期化
	m_pCurrentScene->Initialize();

	// リクエストを削除
	m_pRequestScene = nullptr;
}
