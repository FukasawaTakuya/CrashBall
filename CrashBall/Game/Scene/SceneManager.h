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
{
	
	// データメンバの宣言 -----------------------------------------------
private:

	// シーンのキャッシュ
	std::unordered_map<SceneID, std::unique_ptr<Scene>> m_scenes;

	// 現在のシーン
	Scene* m_pCurrentScene;

	// シーン変更リクエスト
	Scene* m_pRequestScene;

	// シーン遷移スクリーン
	std::unique_ptr<FadeChangeScreen> m_changeScreen;

	const GameContext* m_gameContext;			// ゲーム用のコンテキスト
	const RenderContext* m_renderContext;		// 描画用のコンテキスト
	const ResourceContext* m_resourceContext;	// リソース用のコンテキスト

	IJsonDataManager* m_jsonDataManager;		// Json管理

	std::unordered_map<std::string, std::unique_ptr<JsonDataManager>> m_jsonManagers;

	std::unique_ptr<Scene> m_current;

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

	// シーンの作成
	template<typename SceneType>
	requires std::derived_from<SceneType, Scene>
	void CreateScene(SceneID sceneID)
	{
		// シーンの作成
		std::unique_ptr<SceneType> scene
			= std::make_unique<SceneType>(this, m_jsonDataManager);
		// コンテナに追加
		m_scenes.emplace(sceneID, std::move(scene));
	}

	// 最初のシーンのセット
	void SetStartScene();

	// 初期化
	void Initialize() override;

	// 更新
	void Update();

	// 描画
	void Render();

	// デバイス依存のリソース作成
	void CreateDeviceResources();

	// ウインドウサイズ依存のリソース作成
	void CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj);

	// シーン変更のリクエスト
	void RequestChangeScene(SceneID nextSceneID) override;

	// パラメータの書き込み
	void SaveParam() override;

	// パラメータの再読み込み
	void ReloadParam() override;

	// データの読み込み
	void LoadData();

	// データの保存
	void SaveData();

	// シーンのセット
	void SetScene(const std::string& sceneName);

	// 取得/設定
public:
	// カメラの取得
	ICamera* GetCamera() const
	{
		return m_current->GetCamera();
	}

	// ゲームオブジェクトの取得
	std::vector<GameObject*>* GetGameObjects()
	{
		return m_current->GetGameObjects();
	}

	// 現在のシーンの取得
	Scene* GetCurrentScene() const
	{
		return m_current.get();
	}

	// 内部実装
private:
	// シーン変更
	void ChangeScene();

};
