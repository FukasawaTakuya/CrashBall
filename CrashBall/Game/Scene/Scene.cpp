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
	std::unordered_map<int, GameObject*> objects;
	std::unordered_map<int, Component*> components;

	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		// オブジェクトの生成(プロパティの読み込みは行わない)
		auto obj = GameObjectFactory::CreateObjectFromJson(data.second, components);

		// カメラの場合
		if (obj->GetTag() == ObjectTag::Camera)
		{
			m_camera = obj->GetComponent<TargetCameraController>();
		}

		objects.emplace(obj->GetID(), obj.get());

		AddObject(std::move(obj));
	}

	// プロパティの読み込み
	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		// コンポーネントの追加
		for (auto& jsonComp : data.second["components"])
		{
			// idからコンポーネントを検索
			auto comp = components.find(jsonComp["id"])->second;

			// jsonデータを読み込む
			jsonComp.get_to<Component>(*comp);

			for (auto& prop : comp->GetProperties())
			{
				if (prop.propType == PropertyType::GameObject)
				{
					auto it = objects.find(*static_cast<int*>(prop.data));
					if (it != objects.end())
					{
						*static_cast<IGameObject**>(prop.data) = it->second;
					}
				}
				else if (prop.propType == PropertyType::Component)
				{
					auto it = components.find(*static_cast<int*>(prop.data));
					if (it != components.end())
					{
						*static_cast<Component**>(prop.data) = it->second;
					}
				}
			}
		}

		// 親子関係の生成
		for (auto& obj : objects)
		{
			// 該当データを持ってくる
			auto& jsonObj = m_jsonManager->GetGameObjectData().find(obj.second->GetName())->second;

			for (auto& child : jsonObj["children"])
			{
				auto it = std::ranges::find_if(m_objects, [&](std::unique_ptr<GameObject>& g)
					{
						return child == g->GetID();
					});

				if (it != m_objects.end())
				{
					obj.second->AddChildren(std::move(*it));
					// オブジェクトリストから削除
					m_objects.erase(it);
				}
			}
		}
	}

	for (auto& obj : objects)
	{
		obj.second->Awake();
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
