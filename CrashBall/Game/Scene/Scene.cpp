/*****************************************************************//**
 * \file   Scene.cpp
 * \brief  基底シーン
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Scene.h"

#include "Game/Engine/Time.h"
#include "Game/Factory/GameObjectFactory.h"
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Component/Default/Skybox/Skybox.h"
#include "Game/Json/IJsonDataManager.h"

#include "Game/IDGenerator/GameObejctIDGenerator.h"

/**
 * \brief コンストラクタ
 * 
 * \param jsonDataManager
 */
Scene::Scene(IJsonDataManager* jsonDataManager)
	: m_jsonManager{ jsonDataManager }
	, m_collisionManager(std::make_unique<CollisionManager>())
{
	// ID検索用マップ
	std::unordered_map<int, GameObject*> objects;
	std::unordered_map<int, Component*> components;

	// タイムスケールをデフォルト値に
	Time::SetTimeScale(1.0f);

	// ワールドオブジェクトの作成
	m_worldObject = std::make_unique<GameObject>();
	m_worldObject->SetName("WorldObject");

	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		// オブジェクトの生成
		auto obj = GameObjectFactory::CreateObjectFromJson(data.second, components);

		// カメラの場合
		if (obj->GetTag() == ObjectTag::Camera)
		{
			m_camera = obj->GetComponent<Camera>();
		}

		// 衝突判定登録
		Collider* col = obj->GetComponent<Collider>();
		if (col != nullptr)
		{
			m_collisionManager->RegistCollider(col);
		}

		// ID検索用マップに登録
		objects.emplace(obj->GetID(), obj.get());

		// 検索用マップに登録
		AddMap(obj.get());

		// ワールドオブジェクトの子に設定
		m_worldObject->AddChildrenInBuildTime(std::move(obj));
	}

	// ゲームオブジェクトとコンポーネントの設定
	for (auto& comp : components)
	{
		for (auto& prop : comp.second->GetProperties())
		{
			// データが0の時は無視
			if (*static_cast<int*>(prop.data) == 0) continue;

			if (prop.propType == PropertyType::GameObject)
			{
				// ID検索
				auto it = objects.find(*static_cast<int*>(prop.data));

				// 見つかれば設定
				if (it != objects.end())
				{
					*static_cast<IGameObject**>(prop.data) = it->second;
				}
				else
				{
					*static_cast<IGameObject**>(prop.data) = nullptr;
				}
			}
			else if (prop.propType == PropertyType::Component)
			{
				// ID検索
				auto it = components.find(*static_cast<int*>(prop.data));
				// 見つかれば設定
				if (it != components.end())
				{
					*static_cast<Component**>(prop.data) = it->second;
				}
				else
				{
					*static_cast<Component**>(prop.data) = nullptr;
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
			// ID検索
			auto find = objects.find(child.get<int>());
			// 見つかれば設定
			if (find != objects.end())
			{
				auto temp = m_worldObject->RemoveChild(find->second->GetName());
				obj.second->AddChildrenInBuildTime(std::move(temp));
			}
		}
	}

	if (m_camera == nullptr)
	{
		auto camera = CreateNewGameObject("MainCamera");
		camera->AddComponent<Transform>();
		camera->AddComponent<Skybox>();
		camera->SetTag(ObjectTag::Camera);
		m_camera = camera->AddComponent<Camera>();

		camera->Awake();
	}
}

/**
 * \brief 遷移時の処理
 * 
 */
void Scene::Awake()
{
	m_worldObject->Awake();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Scene::Start(const GameContext& gameContext)
{
	m_worldObject->Start(gameContext);
}


/**
 * \brief 更新
 * \param gameContext ゲーム用のコンテキスト
 */
void Scene::Update(const GameContext& gameContext)
{
	m_worldObject->Update(gameContext);
	m_collisionManager->Update();
}


/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Scene::Render(const RenderContext& renderContext)
{
	m_worldObject->Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void Scene::Finalize()
{
	m_worldObject->Finalize();
}

/**
 * \brief デバイス依存のリソース作成
 * 
 * \param resourceContext リソース用のコンテキスト
 */
void Scene::CreateDeviceResources(const ResourceContext& resourceContext)
{
	m_worldObject->SetDeviceResource(resourceContext);
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 * 
 * \param proj プロジェクション行列
 */
void Scene::CreateWindowSizeResources()
{
	m_worldObject->SetWindowSizeResource();
}

/**
 * \brief データの保存
 * 
 */
void Scene::SaveData()
{
	m_worldObject->SaveData();
	m_jsonManager->SaveGameObjectData();
}

/**
 * \brief データの再読み込み
 * 
 */
void Scene::ReloadData()
{
	m_worldObject->ReloadData();
}

GameObject* Scene::CreateNewGameObject(const std::string& objName)
{
	// ゲームオブジェクトの生成
	auto newGameObject = std::make_unique<GameObject>();
	// ポインタを取得
	GameObject* ptr = newGameObject.get();
	// ワールドオブジェクトの子に設定
	m_worldObject->AddChildrenInRunTime(std::move(newGameObject));
	// マップに追加
	AddMap(ptr);

	// ゲームオブジェクト名を設定
	ptr->SetName(objName);
	// ゲームオブジェクトデータの追加
	ordered_json* data = m_jsonManager->AddGameObjectData(ptr->GetName());
	// ゲームオブジェクトにデータを設定
	ptr->SetData(data);
	// IDを設定
	ptr->SetID(GameObejctIDGenerator::GetID());

	return ptr;
}

/**
 * \brief ゲームオブジェクトの追加
 * 
 * \param obj ゲームオブジェクト
 */
void Scene::AddGameObject(std::unique_ptr<GameObject>&& obj)
{
	m_worldObject->AddChildrenInRunTime(std::move(obj));
}

/**
 * \brief ゲームオブジェクトの削除
 * 
 * \param obj ゲームオブジェクト
 */
void Scene::RemoveGameObject(GameObject* obj)
{
	GameObject* parent = obj->GetParent();
	// 親がいないならリターン
	if (parent == nullptr)
	{
		return;
	}

	// マップから削除
	RemoveMap(obj);

	// 子オブジェクトをマップから削除
	for (auto& child : obj->GetChildren())
	{
		RemoveMap(child.get());
	}

	// 親から子を削除
	parent->RemoveChild(obj->GetName());

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

/**
 * \brief マップから削除
 *
 * \param obj ゲームオブジェクトのポインタ
 */
void Scene::RemoveMap(GameObject* obj)
{
	// オブジェクト名マップから削除
	if (FindGameObject(obj->GetName()) != nullptr)
	{
		m_objNameMap.erase(obj->GetName());
	}

	// オブジェクトタグマップから削除
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
