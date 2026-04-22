#pragma once
#include <string>

#include "SceneManager.h"
#include "Game/Common/Camera.h"

class Scene {

protected:

	SceneManager* m_pSceneManager;

	std::unique_ptr<Camera> m_camera;	// カメラ


public:

	Scene(SceneManager* pSceneManager);

	virtual ~Scene() = default;

	virtual void Initialize() = 0;

	virtual void Update(float elapsedTime) = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual void CreateResources(DirectX::SimpleMath::Matrix projMat) = 0;

	virtual void SetModel() = 0;

	Camera* GetCamera() { return m_camera.get(); }


protected:
	void ChangeScene(std::string nextScene);
};
