#pragma once

class Scene;

class SceneManager{
private:

	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<Scene>>;

	SceneCollection m_scenes;

	Scene* m_pCurrentScene;

	Scene* m_pRequestScene;

	int m_alpha;

public:

	SceneManager();

	~SceneManager();

	// シーンの登録
	void RegisterScene(std::string sceneName, std::unique_ptr<Scene> scene);

	// 最初のシーンのセット
	void SetStartScene();

	// 更新
	void Update(float elapsedTime);

	// 描画
	void Draw();

	// リソース作成
	void CreateResources(DirectX::SimpleMath::Matrix projMat);

	// シーン変更のリクエスト
	void RequestScene(std::string nextScene);


private:
	// シーン変更
	void ChangeScene();

};
