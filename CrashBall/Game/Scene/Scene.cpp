#include "pch.h"
#include "Scene.h"

Scene::Scene(
	ISceneManager* pSceneManager,
	IJsonDataManager* jsonDataManager)
	: m_pSceneManager{ pSceneManager }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneManager->RequestChangeScene(nextSceneID);
}
