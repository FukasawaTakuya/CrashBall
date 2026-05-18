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
	m_pCurrentScene->Finalize();
}

// シーンの登録
void SceneManager::RegisterScene(SceneID sceneID, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneID, std::move(scene));
}

// 最初のシーンのセット
void SceneManager::SetStartScene()
{
	m_pCurrentScene = m_scenes[SceneID::Game].get();
	m_pCurrentScene->Initialize();
}

// 更新
void SceneManager::Update(float elapsedTime)
{
	if (m_pRequestScene) {
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
