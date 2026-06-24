#pragma once
#include "ISceneController.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"

#include "Game/Scene/SceneChangeScreen/FadeChangeScreen.h"

#include "Scene.h"

class Camera;

class SceneManager : public ISceneController
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

public:

	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();

	// シーンの登録
	template<typename SceneType>
	requires std::derived_from<SceneType, Scene>
	void CreateScene(SceneID sceneID, IJsonDataManager* jsonDataManager)
	{
		// シーンの作成
		std::unique_ptr<SceneType> scene
			= std::make_unique<SceneType>(this, jsonDataManager);
		// コンテナに追加
		m_scenes.emplace(sceneID, std::move(scene));
	}

	// 最初のシーンのセット
	void SetStartScene();

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameCotext);

	// 描画
	void Render(const RenderContext& renderCotext);

	// デバイス依存のリソース作成
	void CreateDeviceResources(const ResourceContext& resourceCotext);

	// ウインドウサイズ依存のリソース作成
	void CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj);

	// シーン変更のリクエスト
	void RequestChangeScene(SceneID nextSceneID) override;

	// カメラの取得
	ICamera* GetCamera() const
	{
		return m_pCurrentScene->GetCamera();
	}



private:
	// シーン変更
	void ChangeScene();

};
