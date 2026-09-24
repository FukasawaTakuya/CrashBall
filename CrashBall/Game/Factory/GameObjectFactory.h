/*****************************************************************//**
 * \file   GameObjectFactory.h
 * \brief  ゲームオブジェクトのファクトリー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/GameObject/GameObject.h"
#include "Game/ScriptableObject/ScriptableObject.h"

namespace  GameObjectFactory {

	// ゲームオブジェクトの作成
	template<typename ObjectType, typename... Args>
	requires std::derived_from<ObjectType, GameObject>
	std::unique_ptr<ObjectType> Create(Args&&... args)
	{
		return std::make_unique<ObjectType>(std::forward<Args>(args)...);
	}

	// データからのスクリプタブルオブジェクトの作成
	std::unique_ptr<ScriptableObject> CreateScriptableObjectFromJson(ordered_json& data);

	// データからのゲームオブジェクトの作成
	std::unique_ptr<GameObject> CreateObjectFromJson(
		ordered_json& data,
		std::unordered_map<int, Component*>& components);
};
