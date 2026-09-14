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
#include "Game/IDGenerator/GameObejctIDGenerator.h"

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
	, m_changeScreen(std::make_unique<FadeChangeScreen>())
{
	m_changeScreen->Awake();
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
void SceneManager::SetStartScene(const std::string& sceneName)
{
	m_currentSceneName = sceneName;
	auto it = m_jsonManagers.find(sceneName);
	// シーンが未登録でないとき
	if (it != m_jsonManagers.end())
	{
		// シーン変更
		m_currentScene = std::make_unique<Scene>(this, m_jsonManagers[sceneName].get());
		m_currentScene->Start(*m_gameContext);
	}
}

/**
 * \brief 初期化
 * 
 */
void SceneManager::Start()
{
	m_currentScene->Start(*m_gameContext);
}

/**
 * \brief 更新
 * 
 */
void SceneManager::Update()
{
	// 変更リクエストがnullじゃないなら変更
	if (m_requestSceneName  != "")
	{
		// フェードアウトが完了したら
		if (!m_changeScreen->GetIsFadeOut())
		{
			// シーン変更
			m_currentScene->Finalize();
			m_currentScene = std::make_unique<Scene>(this, m_jsonManagers[m_requestSceneName].get());

			// フェードイン開始
			m_changeScreen->StartFadeIn();
		}
	}

	// シーン遷移スクリーンの更新
	//m_changeScreen->Update(*m_gameContext);

	m_currentScene->Update(*m_gameContext);
}

/**
 * \brief描画
 * 
 */
void SceneManager::Render()
{
	m_currentScene->Render(*m_renderContext);

	//m_changeScreen->Render(*m_renderContext);
}

/**
 * \brief デバイス依存のリソース作成
 * 
 */
void SceneManager::CreateDeviceResources()
{
	m_changeScreen->GetComponent<SpriteRenderer>()->SetSpriteKey("Screen");
	m_changeScreen->GetComponent<SpriteRenderer>()->SetSprite(m_resourceContext->spriteManager);

	m_currentScene->CreateDeviceResources(*m_resourceContext);
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 * 
 * \param proj 射影行列
 */
void SceneManager::CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj)
{
	m_currentScene->CreateWindowSizeResources(proj);
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

		jsonManager->SetSaveFilePath(path + "/");

		for (auto& entity : std::filesystem::recursive_directory_iterator(path))
		{
			jsonManager->LoadGameObject(entity.path().string());
		}

		m_jsonManagers.emplace(scene, std::move(jsonManager));
	}
}

/**
 * \brief データの保存
 * 
 */
void SceneManager::SaveData()
{
	m_currentScene->SaveData();
}

/**
 * \brief シーンの変更
 * 
 * \param sceneName
 */
void SceneManager::RequestChangeScene(const std::string& sceneName)
{
	auto it = m_jsonManagers.find(sceneName);
	// シーンが未登録でないとき
	if (it != m_jsonManagers.end())
	{
		// シーン変更
		m_currentScene->Finalize();
		m_currentScene = std::make_unique<Scene>(this, m_jsonManagers[sceneName].get());

	}

	//// フェードインが終わっていなければリターン
	//if (m_changeScreen->GetIsFadeIn()) return;

	//if (m_requestSceneName != "") return;

	//auto it = m_jsonManagers.find(sceneName);
	//// シーンが未登録でないとき
	//if (it != m_jsonManagers.end())
	//{
	//	// フェードアウト開始
	//	m_changeScreen->StartFadeOut();
	//}

}

/**
 * \brief 新しいオブジェクトの生成
 * 
 */
void SceneManager::CreateNewGameObject()
{
	GameObject* newObj = m_currentScene->CreateNewGameObject();
	//m_jsonManagers[m_currentSceneName]->AddGameObjectData(newObj->GetName());

	//ordered_json* data = m_jsonManagers[m_currentSceneName]->GetGameObjectData(newObj->GetName());
	//newObj->SetData(data);

	//newObj->SetID(GameObejctIDGenerator::GetID());
}

void SceneManager::DeleteGameObject(GameObject* obj)
{
	m_jsonManagers[m_currentSceneName]->DeleteGameObjectData(obj->GetName());
	m_currentScene->DeleteGameObject(obj);
}

/**
 * \brief ゲームオブジェクトの検索
 * 
 * \param objectName ゲームオブジェクト名
 * \return ゲームオブジェクト
 */
GameObject* SceneManager::FindGameObject(const std::string& objectName) const
{
	if (m_currentScene.get() != nullptr)
	{
		return m_currentScene->FindGameObject(objectName);
	}
	else
	{
		return nullptr;
	}
}

/**
 * \brief ゲームオブジェクトのタグでの検索
 *
 * \param tag タグ
 * \return ゲームオブジェクト
 */
GameObject* SceneManager::FindGameObjectWithTag(ObjectTag tag) const
{
	if (m_currentScene.get() != nullptr)
	{
		return m_currentScene->FindGameObjectWithTag(tag);
	}
	else
	{
		return nullptr;
	}
}

/**
 * \brief ゲームオブジェクトのタグでの検索(複数)
 *
 * \param tag タグ
 * \return 見つかったゲームオブジェクトの先頭から終端までのイテレータ
 */
std::pair<TagMapIt, TagMapIt> SceneManager::FindGameObjectsWithTag(ObjectTag tag) const
{
	if (m_currentScene.get() != nullptr)
	{
		return m_currentScene->FindGameObjectsWithTag(tag);
	}
	else
	{
		return std::pair<TagMapIt, TagMapIt>{};
	}
}
