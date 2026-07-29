/*****************************************************************//**
 * \file   ComponentFactory.h
 * \brief  コンポーネントのファクトリー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include <concepts>

class GameObject;

namespace ComponentFactory 
{
	// コンポーネントの生成
	template<typename CompType, typename... Args>
	requires std::derived_from<CompType, Component>
	static std::unique_ptr<CompType> Create(GameObject* gameObject, Args&&... args)
	{
		return std::make_unique<CompType>(gameObject, std::forward<Args>(args)...);
	}

	using CreataFunc = std::unique_ptr<Component>(*)();

	// コンポーネント生成関数の登録
	void RegistComponentFunc(const std::string& compName, CreataFunc func);
};
