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
	// 変更リクエストがnullじゃないなら変更
	if (m_pRequestScene) {
		ChangeScene();
	}

	// 更新
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
	if (it != m_scenes.end())
	{
		// 登録されたリクエストシーンを取得
		m_pRequestScene = it->second.get();
	}
	else {
		//OutputDebugStringA(std::format(
		//	"ID:{} のシーンは登録されていません\n",
		//	nextSceneID
		//).c_str());
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
