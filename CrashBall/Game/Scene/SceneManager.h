/*****************************************************************//**
 * \file   SceneManager.h
 * \brief  シーン管理
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once
#include "Interface/ISceneChanger.h"
#include "Interface/ISceneEditer.h"
#include "Interface/ISceneManager.h"

#include "Game/Json/JsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"

#include "Game/Scene/SceneChangeScreen/FadeChangeScreen.h"

#include "Scene.h"
#include "Game/Camera/DebugCamera.h"

class Camera;

/**
 * \brief シーン管理
 */
class SceneManager 
	: public ISceneChanger
	, public ISceneEditer
	, public ISceneManager
{
	
	// データメンバの宣言 -----------------------------------------------
private:

	std::string m_currentSceneName;

	// リクエストシーン名
	std::string m_requestSceneName;

	// シーン遷移スクリーン
	std::unique_ptr<FadeChangeScreen> m_changeScreen;

	const GameContext* m_gameContext;			// ゲーム用のコンテキスト
	const RenderContext* m_renderContext;		// 描画用のコンテキスト
	const ResourceContext* m_resourceContext;	// リソース用のコンテキスト

	std::unordered_map<std::string, std::unique_ptr<JsonDataManager>> m_jsonManagers;

	std::unique_ptr<Scene> m_currentScene;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneManager(
		const GameContext*		gameContext,
		const RenderContext*	renderContext,
		const ResourceContext*	resourceContext,
		IJsonDataManager* jsonDataManager
	);

	// デストラクタ
	~SceneManager();

	//// シーンの作成
	//template<typename SceneType>
	//requires std::derived_from<SceneType, Scene>
	//void CreateScene(SceneID sceneID)
	//{
	//	//// シーンの作成
	//	//std::unique_ptr<SceneType> scene
	//	//	= std::make_unique<SceneType>(this, m_jsonDataManager);
	//	//// コンテナに追加
	//	//m_scenes.emplace(sceneID, std::move(scene));
	//}

	// 最初のシーンのセット
	void SetStartScene(const std::string& sceneName);

	// 初期化
	void Start() override;

	// 更新
	void Update();

	// 描画
	void Render();

	// デバイス依存のリソース作成
	void CreateDeviceResources();

	// ウインドウサイズ依存のリソース作成
	void CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj);

	// データの読み込み
	void LoadData();

	// データの保存
	void SaveData() override;

	// シーンの変更
	void RequestChangeScene(const std::string& sceneName) override;

	// 新しいオブジェクトの生成
	void CreateNewGameObject() override;

	// ゲームオブジェクトの削除
	void DeleteGameObject(GameObject* obj) override;

	// 取得/設定
public:
	// カメラの取得
	ICamera* GetCamera() const
	{
		return m_currentScene->GetCamera();
	}

	// ゲームオブジェクトの取得
	std::vector<std::unique_ptr<GameObject>>& GetGameObjects() override
	{
		return m_currentScene->GetObjects();
	}

	// 現在のシーンの取得
	Scene* GetCurrentScene() const
	{
		return m_currentScene.get();
	}

	// ゲームオブジェクトの検索
	GameObject* FindGameObject(const std::string& objectName) const override;

	// ゲームオブジェクトのタグでの検索
	GameObject* FindGameObjectWithTag(ObjectTag tag) const override;

	// ゲームオブジェクトのタグでの検索
	std::pair<TagMapIt, TagMapIt> FindGameObjectsWithTag(ObjectTag tag) const override;

	// 内部実装
private:

};
