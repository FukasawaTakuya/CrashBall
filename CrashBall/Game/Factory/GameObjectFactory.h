/*****************************************************************//**
 * \file   GameObjectFactory.h
 * \brief  ゲームオブジェクトのファクトリー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/GameObject/GameObject.h"
#include "Game/IDGenerator/ComponentIDGenerator.h"

#include <fstream>

namespace  GameObjectFactory {

	// ゲームオブジェクトの作成
	template<typename ObjectType, typename... Args>
	requires std::derived_from<ObjectType, GameObject>
	static std::unique_ptr<ObjectType> Create(Args&&... args)
	{
		return std::make_unique<ObjectType>(std::forward<Args>(args)...);
	}

	// データからのゲームオブジェクトの作成
	static std::unique_ptr<GameObject> CreateObjectFromJson(
		const std::string& objectName,
		const std::string& loadPath)
	{
		// ファイルの読み込み
		std::ifstream ifs(loadPath + objectName + ".json");

		ordered_json data;

		ifs >> data;

		// ========== 以下を残す ============ //

		// ゲームオブジェクトの生成
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();

		obj->SetName(data["name"]);
		obj->SetTag(data["tag"]);
		obj->SetIsActive(data["isActive"]);

		// コンポーネントの追加
		for (auto& comp : data["components"])
		{
			auto compPtr = obj->AddComponent(
				ComponentFactory::CreataFromJson(comp["compName"], obj.get())
			);

			comp.get_to<Component>(*compPtr);
		}

		return std::move(obj);
	}

	// データからのゲームオブジェクトの作成
	static std::unique_ptr<GameObject> CreateObjectFromJson(
		ordered_json& data)
	{
		// ゲームオブジェクトの生成
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();

		obj->SetName(data["name"]);
		obj->SetTag(data["tag"]);
		obj->SetID(data["id"]);
		obj->SetIsActive(data["isActive"]);
		obj->SetData(&data);

		// コンポーネントの追加
		for (auto& jsonComp : data["components"])
		{
			auto compPtr = obj->AddComponent(
				ComponentFactory::CreataFromJson(jsonComp["compName"], obj.get())
			);

			jsonComp.get_to<Component>(*compPtr);

			// 最大IDか調べる
			ComponentIDGenerator::CheckMaxID(compPtr->GetID());
		}

		return std::move(obj);
	}
};
