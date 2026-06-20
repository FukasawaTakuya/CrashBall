#include "pch.h"
#include "Scene.h"

Scene::Scene(ISceneController* pSceneManager)
	: m_pSceneController{ pSceneManager }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneController->RequestChangeScene(nextSceneID);
}
