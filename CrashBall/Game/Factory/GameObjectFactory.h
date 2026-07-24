/*****************************************************************//**
 * \file   GameObjectFactory.h
 * \brief  ゲームオブジェクトのファクトリー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/GameObject/GameObject.h"

namespace  GameObjectFactory {

	// ゲームオブジェクトの作成
	template<typename ObjectType, typename... Args>
	requires std::derived_from<ObjectType, GameObject>
	static std::unique_ptr<ObjectType> Create(Args&&... args)
	{
		return std::make_unique<ObjectType>(std::forward<Args>(args)...);
	}

	// データからのゲームオブジェクトの作成
	static std::unique_ptr<GameObject> CreataFromJson(ordered_json data);
};
