#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneManager* pSceneManager)
	: m_pSceneManager{ pSceneManager }
	, m_camera{ std::make_unique<Camera>() }
{
}

void Scene::ChangeScene(std::string nextScene)
{
	m_pSceneManager->RequestScene(nextScene);
}
