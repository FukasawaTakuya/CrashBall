#include "pch.h"
#include "Scene.h"

#include "Game/Engine/Time.h"
#include "Game/Factory/GameObjectFactory.h"
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Json/IJsonDataManager.h"

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
	, m_collisionManager(std::make_unique<CollisionManager>())
{
	std::unordered_map<int, GameObject*> objects;
	std::unordered_map<int, Component*> components;

	Time::SetTimeScale(1.0f);

	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		// オブジェクトの生成
		auto obj = GameObjectFactory::CreateObjectFromJson(data.second, components);

		// カメラの場合
		if (obj->GetTag() == ObjectTag::Camera)
		{
			m_camera = obj->GetComponent<TargetCameraController>();
		}

		// 衝突判定登録
		Collider* col = obj->GetComponent<Collider>();
		if (col != nullptr)
		{
			m_collisionManager->RegistCollider(col);
		}

		objects.emplace(obj->GetID(), obj.get());
		AddMap(obj.get());

		m_gameObjects.push_back(std::move(obj));
	}

	// プロパティの読み込み
	for (auto& comp : components)
	{
		for (auto& prop : comp.second->GetProperties())
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
			auto it = std::ranges::find_if(m_gameObjects, [&](std::unique_ptr<GameObject>& g)
				{
					return child == g->GetID();
				});

			if (it != m_gameObjects.end())
			{
				obj.second->AddChildrenInBuildTime(std::move(*it));
				// オブジェクトリストから削除
				m_gameObjects.erase(it);
			}
		}
	}

	for (auto& obj : objects)
	{
		obj.second->Awake();
	}
}

GameObject* Scene::CreateNewGameObject()
{
	// ゲームオブジェクトの生成
	auto newGameObject = std::make_unique<GameObject>();
	// ポインタを取得
	GameObject* ptr = newGameObject.get();
	// コンテナに追加
	m_gameObjects.push_back(std::move(newGameObject));
	// マップに追加
	AddMap(ptr);
	return ptr;
}

void Scene::DeleteGameObject(GameObject* obj)
{
	DeleteMap(obj);

	for (auto& child : obj->GetChildren())
	{
		DeleteMap(child.get());
	}

	auto it = std::ranges::find_if(m_gameObjects, [&](std::unique_ptr<GameObject>& gameObject)
		{
			return gameObject->GetName() == obj->GetName();
		});

	if (it != m_gameObjects.end())
	{
		m_gameObjects.erase(it);
	}
}

void Scene::DeleteMap(GameObject* obj)
{
	if (FindGameObject(obj->GetName()) != nullptr)
	{
		m_objNameMap.erase(obj->GetName());
	} 
	auto range = FindGameObjectsWithTag(obj->GetTag());
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second->GetName() == obj->GetName())
		{
			m_objTagMap.erase(it);
			break;
		}
	}
}

/**
 * \brief ゲームオブジェクトの検索
 * 
 * \param objectName オブジェクト名
 * \return ゲームオブジェクト
 */
GameObject* Scene::FindGameObject(const std::string& objectName) const
{
	auto it = m_objNameMap.find(objectName);
	if (it != m_objNameMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

/**
 * \brief ゲームオブジェクトのタグでの検索
 * 
 * \param tag タグ
 * \return ゲームオブジェクト
 */
GameObject* Scene::FindGameObjectWithTag(const ObjectTag& tag) const
{
	auto it = m_objTagMap.find(tag);
	if (it != m_objTagMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}


/**
 * \brief ゲームオブジェクトのタグでの検索(複数)
 *
 * \param tag タグ
 * \return 見つかったゲームオブジェクトの先頭から終端までのイテレータ
 */
std::pair<TagMapIt, TagMapIt> Scene::FindGameObjectsWithTag(const ObjectTag& tag) const
{
	std::pair<TagMapIt, TagMapIt> range = m_objTagMap.equal_range(tag);
	return range;
}
//
//void Scene::ChangeScene(SceneID nextSceneID)
//{
//	//m_pSceneChanger->RequestChangeScene(nextSceneID);
//}

/**
 * \brief マップに追加
 * 
 * \param gameObject ゲームオブジェクト
 */
void Scene::AddMap(GameObject* gameObject)
{
	m_objNameMap.emplace(gameObject->GetName(), gameObject);
	m_objTagMap.emplace(gameObject->GetTag(), gameObject);
}
