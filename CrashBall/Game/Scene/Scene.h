/*****************************************************************//**
 * \file   Scene.h
 * \brief  基底シーン
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Json/IJsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Component/Camera/Camera.h"

#include "Game/GameObject/GameObject.h"
#include "Game/CollisionManager/CollisionManager.h"

using TagMapIt = std::unordered_multimap<ObjectTag, GameObject*>::const_iterator;

/**
 * \brief 基底シーン
 */
class Scene {

	// データメンバの宣言 ----------------------------------------------- 
protected:

	std::string m_sceneName = "scene";

	Camera* m_camera = nullptr;

	IJsonDataManager* m_jsonManager;

	std::vector<std::unique_ptr<GameObject>> m_gameObjects;		// GameObjectのコンテナ
	std::unordered_map<std::string, GameObject*> m_objNameMap;	// GameObjectの名前マップ
	std::unordered_multimap<ObjectTag, GameObject*> m_objTagMap;// GameOBjectのタグマップ

	std::unique_ptr<CollisionManager> m_collisionManager;	// 衝突管理オブジェクト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Scene(IJsonDataManager* jsonDataManager);

	// デストラクタ
	virtual ~Scene() = default;

	// 操作
public:

	// 遷移時の処理
	virtual void OnEnter(
		const ResourceContext& resourceContext,
		const GameContext& gameContext
	) {};

	// 初期化
	virtual void Start(const GameContext& gameContext)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Start(gameContext);
		}
	};

	// 更新
	virtual void Update(const GameContext& gameContext)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(gameContext);
		}

		m_collisionManager->Update();
	};
	
	// 描画
	virtual void Render(const RenderContext& renderContext)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Render(renderContext);
		}
	};

	// 終了処理
	virtual void Finalize(){};

	// デバイス依存のリソース作成
	virtual void CreateDeviceResources(const ResourceContext& resourceContext)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->SetResource(resourceContext);
		}
	};

	// ウインドウサイズ依存のリソース作成
	virtual void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj){};

	// データの保存
	void SaveData()
	{
		for (auto& obj : m_gameObjects)
		{
			obj->SaveData();
		}
		m_jsonManager->SaveGameObjectData();
	}

	void ReloadData()
	{
		for (auto& obj : m_gameObjects)
		{
			obj->ReloadData();
		}
	}

	// 新しいゲームオブジェクトの生成
	GameObject* CreateNewGameObject(const std::string& objName);

	// ゲームオブジェクトの削除
	void DeleteGameObject(GameObject* obj);

	// マップから削除
	void DeleteMap(GameObject* obj);

	// ゲームオブジェクトの検索
	GameObject* FindGameObject(const std::string& objectName) const;

	// ゲームオブジェクトのタグでの検索
	GameObject* FindGameObjectWithTag(const ObjectTag& tag) const;

	// ゲームオブジェクトのタグでの検索
	std::pair<TagMapIt, TagMapIt> FindGameObjectsWithTag(const ObjectTag& tag) const;

	// 取得/設定
public:

	// カメラの取得
	virtual Camera* GetCamera() const { return m_camera; };

	// シーン名の取得
	std::string GetSceneName() const
	{
		return m_sceneName;
	}

	// ゲームオブジェクトのコンテナの取得
	std::vector<std::unique_ptr<GameObject>>& GetObjects()
	{
		return m_gameObjects;
	}

	// シーン名の設定
	void SetSceneName(const std::string& sceneName)
	{
		m_sceneName = sceneName;
	}

	// 内部実装
private:

	// シーンの変更
	//void ChangeScene(SceneID nextSceneID);

	// マップに追加
	void AddMap(GameObject* gameObject);

};
