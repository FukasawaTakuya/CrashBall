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
	, m_jsonManager{ m_jsonManager }
{
	for (auto& data : m_jsonManager->GetJsonData())
	{
		auto obj = std::make_unique<GameObject>(data);

		obj->Awake();

		m_objects.push_back(std::move(obj));
	}
	m_playManager = std::make_unique<GameObject>(m_jsonManager->GetPlayManagerData());
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneChanger->RequestChangeScene(nextSceneID);
}
