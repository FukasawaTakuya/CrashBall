#pragma once
#include "SceneManager.h"
#include <string>

class Scene {

protected:

	SceneManager* m_pSceneManager;

public:

	Scene(SceneManager* pSceneManager);

	virtual ~Scene() = default;

	virtual void Initialize() = 0;

	virtual void Update(float elapsedTime) = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual void CreateResources(DirectX::SimpleMath::Matrix projMat) = 0;

	virtual void SetModel() = 0;

protected:
	void ChangeScene(std::string nextScene);
};
