#include "pch.h"
#include "Scene.h"

/**
 * \brief コンストラクタ
 * 
 * \param pSceneManager
 * \param jsonDataManager
 */
Scene::Scene(
	ISceneChanger* pSceneManager,
	IJsonDataManager* jsonDataManager)
	: m_pSceneChanger{ pSceneManager }
{
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneChanger->RequestChangeScene(nextSceneID);
}
