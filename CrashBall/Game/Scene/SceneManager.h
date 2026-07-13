#pragma once
#include "ISceneManager.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"

#include "Game/Scene/SceneChangeScreen/FadeChangeScreen.h"

#include "Scene.h"

class Camera;

class SceneManager : public ISceneManager
{

private:

	// シーンのキャッシュ
	std::unordered_map<SceneID, std::unique_ptr<Scene>> m_scenes;

	// 現在のシーン
	Scene* m_pCurrentScene;

	// シーン変更リクエスト
	Scene* m_pRequestScene;

	// シーン遷移スクリーン
	std::unique_ptr<FadeChangeScreen> m_changeScreen;

	const GameContext* m_gameContext;
	const RenderContext* m_renderContext;
	const ResourceContext* m_resourceContext;

	IJsonDataManager* m_jsonDataManager;

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
	void Initialize();

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
	void SaveParam();

	// パラメータの再読み込み
	void ReloadParam();


	// カメラの取得
	ICamera* GetCamera() const
	{
		return m_pCurrentScene->GetCamera();
	}

	std::vector<GameObject*>* GetGameObjects()
	{
		return m_pCurrentScene->GetGameObjects();
	}

private:
	// シーン変更
	void ChangeScene();

};
