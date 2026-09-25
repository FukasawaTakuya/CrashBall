/*****************************************************************//**
 * \file   SceneManager.h
 * \brief  シーン管理
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once
#include "Interface/ISceneEditer.h"
#include "Interface/ISceneManager.h"

#include "Game/Json/JsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"

#include "Game/EditGui/EditGuiManager.h"

#include "Game/Scene/SceneChangeScreen/FadeChangeScreen.h"

#include "Scene.h"
#include "Game/Camera/DebugCamera.h"

class Camera;

/**
 * \brief シーン管理
 */
class SceneManager 
	: public ISceneEditer	// シーン編集機能
	, public ISceneManager	// グローバルアクセス用インターフェース
{
	
	// データメンバの宣言 -----------------------------------------------
private:

	// 現在のシーン名
	std::string m_currentSceneName;

	// リクエストシーン名
	std::string m_requestSceneName;

	// シーン遷移スクリーン
	std::unique_ptr<FadeChangeScreen> m_changeScreen;

	const GameContext* m_pGameContext;			// ゲーム用のコンテキスト
	const RenderContext* m_pRenderContext;		// 描画用のコンテキスト
	const ResourceContext* m_pResourceContext;	// リソース用のコンテキスト

	EditGuiManager* m_pEditGuiManager;			// エディタGUI管理

	// jsonDataManagerのコンテナ
	std::unordered_map<std::string, std::unique_ptr<JsonDataManager>> m_jsonManagers;

	// 現在のシーン
	std::unique_ptr<Scene> m_currentScene;

	// シーン名リスト
	std::vector<std::string> m_sceneNameList;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneManager(
		const GameContext*		pGameContext,
		const RenderContext*	pRenderContext,
		const ResourceContext*	pResourceContext,
		EditGuiManager*			pEditGuiManager
	);

	// デストラクタ
	~SceneManager();

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

	// 新しいシーンの作成
	void CreateNewScene(const std::string& newSceneName) override;

	// シーンの変更
	void RequestChangeScene(const std::string& sceneName) override;

	// 新しいオブジェクトの生成
	void CreateNewGameObject() override;

	// ゲームオブジェクトの削除
	void DeleteGameObject(GameObject* obj) override;

	// ゲームオブジェクトの検索
	GameObject* FindGameObject(const std::string& objectName) const override;

	// ゲームオブジェクトのタグでの検索
	GameObject* FindGameObjectWithTag(ObjectTag tag) const override;

	// ゲームオブジェクトのタグでの検索
	std::pair<TagMapIt, TagMapIt> FindGameObjectsWithTag(ObjectTag tag) const override;

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

	// 現在のシーン名の取得
	const std::string& GetCurrrentSceneName() override
	{
		return m_currentSceneName;
	}

	// シーン名リストの取得
	std::vector<std::string>& GetSceneNameList() override
	{
		return m_sceneNameList;
	}

	// 内部実装
private:
};
