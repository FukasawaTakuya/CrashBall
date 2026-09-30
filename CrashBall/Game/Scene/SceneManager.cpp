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
 */
SceneManager::SceneManager(
	const GameContext*		pGameContext,
	const RenderContext*	pRenderContext,
	const ResourceContext*	pResourceContext,
	EditGuiManager*			pEditGuiManager)
	: m_pGameContext	(pGameContext)
	, m_pRenderContext	(pRenderContext)
	, m_pResourceContext(pResourceContext)
	, m_pEditGuiManager	(pEditGuiManager)
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
void SceneManager::SetStartScene(const std::string& sceneName)
{
	m_currentSceneName = sceneName;
	auto it = m_jsonManagers.find(sceneName);
	// シーンが未登録でないとき
	if (it != m_jsonManagers.end())
	{
		// シーン変更
		m_currentScene = std::make_unique<Scene>(m_jsonManagers[sceneName].get());
		m_currentScene->Start(*m_pGameContext);
	}
}

/**
 * \brief 初期化
 * 
 */
void SceneManager::Start()
{
	m_currentScene->Start(*m_pGameContext);
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
		m_pEditGuiManager->Reset();

		// シーン変更
		m_currentScene->Finalize();

		m_currentScene = std::make_unique<Scene>(m_jsonManagers[m_requestSceneName].get());

		// リソースの作成
		CreateDeviceResources();

		// 開始処理
		m_currentScene->Start(*m_pGameContext);

		// 現シーン名の変更
		m_currentSceneName = m_requestSceneName;
		// リクエストシーンのリセット
		m_requestSceneName = "";
	}
}

/**
 * \brief シーンの更新
 *
 */
void SceneManager::SceneUpdate()
{
	m_currentScene->Update(*m_pGameContext);
}

/**
 * \brief描画
 * 
 */
void SceneManager::Render()
{
	m_currentScene->Render(*m_pRenderContext);
}

/**
 * \brief デバイス依存のリソース作成
 * 
 */
void SceneManager::CreateDeviceResources()
{
	m_currentScene->CreateDeviceResources(*m_pResourceContext);
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

		// ファイルが存在すれば読み込み
		if (std::filesystem::exists(path))
		{
			// 指定パス内のファイルを読み込み
			for (auto& entity : std::filesystem::recursive_directory_iterator(path))
			{
				// ゲームオブジェクトデータの読み込み
				jsonManager->LoadGameObjectData(entity.path().string());
			}

			// jsonマネージャーのコンテナに追加
			m_jsonManagers.emplace(scene, std::move(jsonManager));
			// シーン名リストに追加
			m_sceneNameList.push_back(sceneName);
		}
	}
}

/**
 * \brief データの保存
 * 
 */
void SceneManager::SaveData()
{
	m_currentScene->SaveData();

	ordered_json sceneListData;
	sceneListData["scenes"] = m_sceneNameList;

	std::ofstream ofs("Resources/Data/Scenes.json");

	ofs << sceneListData.dump(4);
}

/**
 * \brief データの再読み込み
 * 
 */
void SceneManager::ReloadData()
{
	m_currentScene->ReloadData();
}

/**
 * \brief 新しいシーンの作成
 * 
 * \param newSceneName 新しいシーン名
 */
void SceneManager::CreateNewScene(const std::string& newSceneName)
{
	// シーン名リストに追加
	m_sceneNameList.push_back(newSceneName);

	// jsonDataManagerの追加
	auto newJsonManager = std::make_unique<JsonDataManager>();

	// フォルダの作成
	std::string path = "Resources/Data/Objects/" + newSceneName + "/";
	std::filesystem::create_directory(path);

	// 保存パスの設定
	newJsonManager->SetSaveFilePath(path);

	m_jsonManagers.emplace(newSceneName, std::move(newJsonManager));

	// シーンの変更
	RequestChangeScene(newSceneName);
}

/**
 * \brief シーンの変更
 * 
 * \param sceneName
 */
void SceneManager::RequestChangeScene(const std::string& sceneName)
{
	
	if (m_requestSceneName != "") return;


	auto it = m_jsonManagers.find(sceneName);
	// シーンが未登録でないとき
	if (it != m_jsonManagers.end())
	{
		// シーン変更
		m_requestSceneName = sceneName;
	}
}

/**
 * \brief 新しいオブジェクトの生成
 * 
 * \param objName オブジェクト名
 */
void SceneManager::CreateNewGameObject(const std::string& objName)
{
	// ゲームオブジェクトの生成
	GameObject* newObj = m_currentScene->CreateNewGameObject(objName);
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
