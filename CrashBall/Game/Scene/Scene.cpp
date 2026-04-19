#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneManager* pSceneManager)
	: m_pSceneManager{ pSceneManager }
{
}

void Scene::ChangeScene(std::string nextScene)
{
	m_pSceneManager->RequestScene(nextScene);
}
