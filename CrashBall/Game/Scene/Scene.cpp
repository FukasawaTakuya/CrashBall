#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneManager* pSceneManager)
	: m_pSceneController{ pSceneManager }
	, m_camera{ std::make_unique<Camera>() }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneController->RequestChangeScene(nextSceneID);
}
