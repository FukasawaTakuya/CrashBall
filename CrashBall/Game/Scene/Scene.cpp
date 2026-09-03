#include "pch.h"
#include "Scene.h"

#include "Game/Factory/GameObjectFactory.h"
#include "Game/Component/Camera/TargetCameraController.h"

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
		auto obj = GameObjectFactory::CreateObjectFromJson(data.second);

		if (obj->GetTag() == ObjectTag::Camera)
		{
			m_camera = obj->GetComponent<TargetCameraController>();
		}

		// TODO:親子関係

		//obj->Awake();

		AddObject(std::move(obj));
	}

	//m_playManager = std::make_unique<GameObject>(m_jsonManager->GetPlayManagerData());

	// TODO:コライダー登録
	// TODO:カメラターゲット登録
	// TODO:UI登録
	// TODO:GamePanel修正 PanelController作れば解決　子からオブジェクト取得
}

void Scene::ChangeScene(SceneID nextSceneID)
{
	m_pSceneChanger->RequestChangeScene(nextSceneID);
}
