#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: m_pCurrentScene{ nullptr }
	, m_pRequestScene{ nullptr }
{
}

SceneManager::~SceneManager()
{
}

// シーンの登録
void SceneManager::RegisterScene(SceneID sceneID, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneID, std::move(scene));
}

/**
 * \brief 最初のシーンのセット
 * 
 */
void SceneManager::SetStartScene()
{
	m_pCurrentScene = m_scenes[SceneID::Game].get();
	m_pCurrentScene->Initialize();
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
	if (m_pRequestScene) {
		ChangeScene();
	}

	if (m_pCurrentScene && !m_pRequestScene) {
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
	if (m_pCurrentScene) m_pCurrentScene->Draw(renderCotext);
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
	auto it = m_scenes.find(nextSceneID);
	// シーンが未登録
	if (it == m_scenes.end())
	{
		OutputDebugString(L"登録されていません。");
		return;
	}

	// 登録されたリクエストシーンを取得
	m_pRequestScene = it->second.get();
}

/**
 * \brief シーン変更
 * 
 */
void SceneManager::ChangeScene()
{
	m_pCurrentScene->Finalize();

	m_pCurrentScene = m_pRequestScene;

	m_pCurrentScene->Initialize();

	m_pRequestScene = nullptr;
}
