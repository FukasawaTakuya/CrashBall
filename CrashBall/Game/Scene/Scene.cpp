#include "pch.h"
#include "Scene.h"

Scene::Scene(
	ISceneController* pSceneManager,
	IJsonDataManager* jsonDataManager)
	: m_pSceneController{ pSceneManager }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneController->RequestChangeScene(nextSceneID);
}
