#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: m_pCurrentScene{ nullptr }
	, m_pRequestScene{ nullptr }
	, m_alpha{ 255 }
{
}

SceneManager::~SceneManager()
{
	m_pCurrentScene->Finalize();
}

// シーンの登録
void SceneManager::RegisterScene(std::string sceneName, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

// 最初のシーンのセット
void SceneManager::SetStartScene()
{
	m_pCurrentScene = m_scenes["GameScene"].get();
	m_pCurrentScene->Initialize();
}

// 更新
void SceneManager::Update(float elapsedTime)
{
	if (m_pRequestScene) {
		if(m_alpha >= 255)
			ChangeScene();
	}

	if (m_pCurrentScene && !m_pRequestScene) {
		m_pCurrentScene->Update(elapsedTime);
	}
}

// 描画
void SceneManager::Draw()
{
	if (m_pCurrentScene) m_pCurrentScene->Draw();
}

void SceneManager::CreateResources(DirectX::SimpleMath::Matrix projMat)
{
	if (m_pCurrentScene) m_pCurrentScene->CreateResources(projMat);
}

// シーン変更のリクエスト
void SceneManager::RequestScene(std::string nextScene)
{
	// シーンが未登録？
	if (m_scenes.count(nextScene) == 0)
	{
		OutputDebugString(L"%sは登録されていません。", nextScene.c_str());
		return;
	}

	// 登録されたリクエストシーンを取得
	m_pRequestScene = m_scenes[nextScene].get();
}

Camera* SceneManager::GetCamera()
{
	return m_pCurrentScene->GetCamera();
}

// シーン変更
void SceneManager::ChangeScene()
{
	m_pCurrentScene->Finalize();

	m_pCurrentScene = m_pRequestScene;

	m_pCurrentScene->Initialize();

	m_pRequestScene = nullptr;
}
