/*****************************************************************//**
 * \file   Scene.h
 * \brief  基底シーン
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once
#include <string>

#include "Interface/ISceneChanger.h"
#include "Game/Json/IJsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Component/Camera/ICamera.h"

#include "Game/GameObject/GameObject.h"

/**
 * \brief 基底シーン
 */
class Scene {

	// データメンバの宣言 -----------------------------------------------
protected:

	ISceneChanger* m_pSceneChanger;

	IJsonDataManager* m_jsonManager;

	std::vector<GameObject*> m_gameObjects;


	// ========================================= //
	std::string m_sceneName = "scene";

	ICamera* m_camera = nullptr;

	std::vector<std::unique_ptr<GameObject>> m_objects;
	std::unique_ptr<GameObject> m_playManager;

	std::vector<GameObject*> m_objectsList;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Scene(
		ISceneChanger* pSceneManager,
		IJsonDataManager* jsonDataManager);

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
		for (auto& obj : m_objects)
		{
			obj->Start(gameContext);
		}
	};

	// 更新
	virtual void Update(const GameContext& gameContext){};
	
	// 描画
	virtual void Render(const RenderContext& renderContext){};

	// 終了処理
	virtual void Finalize(){};

	// デバイス依存のリソース作成
	virtual void CreateDeviceResources(const ResourceContext& resourceContext){};

	// ウインドウサイズ依存のリソース作成
	virtual void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj){};

	// パラメータの書き込み
	virtual void SaveParam(){};

	// パラメータの再読み込み
	virtual void ReloadParam(){};

	// 取得/設定
public:

	// カメラの取得
	virtual ICamera* GetCamera() const { return m_camera; };

	// ゲームオブジェクトの取得
	std::vector<GameObject*>* GetGameObjects()
	{
		return &m_gameObjects;
	}

	// シーン名の取得
	std::string GetSceneName() const
	{
		return m_sceneName;
	}

	std::vector<std::unique_ptr<GameObject>>& GetObjects()
	{
		return m_objects;
	}

	void AddObject(std::unique_ptr<GameObject>&& object)
	{
		m_objectsList.push_back(object.get());
		m_objects.push_back(std::move(object));
	}

	// 内部実装
protected:
	void ChangeScene(SceneID nextSceneID);
};
