#pragma once
#include "ISceneController.h"
#include "Game/Common/GameContext.h"

class Scene;
class Camera;

class SceneManager : public ISceneController{
private:

	std::unordered_map<SceneID, std::unique_ptr<Scene>> m_scenes;

	Scene* m_pCurrentScene;

	Scene* m_pRequestScene;

public:

	SceneManager();

	~SceneManager();

	// シーンの登録
	void RegisterScene(SceneID sceneID, std::unique_ptr<Scene> scene);

	// 最初のシーンのセット
	void SetStartScene();

	// 更新
	void Update(const GameContext& gameCotext);

	// 描画
	void Render(const GameContext& gameCotext);

	// リソース作成
	void CreateDeviceResources(const GameContext& gameCotext);

	void CreateWindowSizeResources(DirectX::SimpleMath::Matrix proj);

	// シーン変更のリクエスト
	void RequestChangeScene(SceneID nextSceneID) override;

	Camera* GetCamera();


private:
	// シーン変更
	void ChangeScene();

};
