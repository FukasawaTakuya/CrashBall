#include "pch.h"
#include "Scene.h"

Scene::Scene(ISceneController* pSceneManager)
	: m_pSceneController{ pSceneManager }
	, m_camera{ std::make_unique<CameraObject>() }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneController->RequestChangeScene(nextSceneID);
}
