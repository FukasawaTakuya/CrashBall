#include "pch.h"
#include "Scene.h"

#include "Game/Factory/GameObjectFactory.h"

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
	, m_jsonManager{ jsonDataManager }
{
	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		auto obj = GameObjectFactory::CreateObjectFromJson(data);

		if (obj->GetTag() == ObjectTag::Camera)
		{
			//m_camera = obj->GetComponent
		}

		obj->Awake();

		m_objects.push_back(std::move(obj));
	}
	m_playManager = std::make_unique<GameObject>(m_jsonManager->GetPlayManagerData());
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneChanger->RequestChangeScene(nextSceneID);
}
