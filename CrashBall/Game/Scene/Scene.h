#pragma once
#include <string>

#include "ISceneController.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Common/Camera.h"

class Scene {

protected:

	ISceneController* m_pSceneController;

	std::unique_ptr<Camera> m_camera;	// カメラ


public:

	Scene(ISceneController* pSceneManager);

	virtual ~Scene() = default;

	virtual void Initialize() = 0;

	virtual void Update(const GameContext& gameContext) = 0;

	virtual void Draw(const RenderContext& renderContext) = 0;

	virtual void Finalize() = 0;

	virtual void CreateDeviceResources(const ResourceContext& resourceContext) = 0;

	virtual void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj) = 0;

	virtual void SetModel() = 0;

	Camera* GetCamera() { return m_camera.get(); }


protected:
	void ChangeScene(SceneID nextSceneID);
};
