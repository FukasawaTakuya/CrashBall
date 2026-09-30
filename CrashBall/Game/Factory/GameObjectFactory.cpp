/*****************************************************************//**
 * \file   GameObjectFactory.cpp
 * \brief  ゲームオブジェクトのファクトリー
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "GameObjectFactory.h"
#include "Game/IDGenerator/ComponentIDGenerator.h"

#include "Library/magic_enum.hpp"

#include <fstream>

/**
 * \brief データからのスクリプタブルオブジェクトの作成
 * 
 * \param data スクリプタブルオブジェクトデータ
 * \return スクリプタブルオブジェクト
 */
std::unique_ptr<ScriptableObject> GameObjectFactory::CreateScriptableObjectFromJson(ordered_json& data)
{
	// スクリプタブルオブジェクトの生成
	std::unique_ptr<ScriptableObject> obj = std::make_unique<ScriptableObject>();

	obj->SetName(data["name"]);
	obj->SetData(&data);

	// コンポーネントの追加
	for (auto& jsonComp : data["components"])
	{
		auto compPtr = obj->Set(
			ComponentFactory::CreataFromJson(jsonComp["compName"], obj.get())
		);

		jsonComp.get_to<Component>(*compPtr);
	}

	return std::move(obj);
}

/**
 * \brief データからのゲームオブジェクトの作成
 * 
 * \param data ゲームオブジェクトデータ
 * \param components ID検索用マップ
 * \return ゲームオブジェクト
 */
std::unique_ptr<GameObject> GameObjectFactory::CreateObjectFromJson(
	ordered_json& data, 
	std::unordered_map<int, Component*>& components)
{
	// ゲームオブジェクトの生成
	std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();

	obj->SetName(data["name"]);
	obj->SetTag(magic_enum::enum_cast<ObjectTag>(data["tag"].get<std::string>()).value());
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

		// コンテナに格納
		components.emplace(compPtr->GetID(), compPtr);
	}

	return std::move(obj);
}
