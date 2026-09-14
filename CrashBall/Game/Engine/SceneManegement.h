/*****************************************************************//**
 * \file   Scene.h
 * \brief  シーン情報を取得するためのグローバル関数一覧
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/
#pragma once

#include <string>
#include "Game/Scene/Scene.h"
#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/Scene/Interface/ISceneManager.h"

namespace SceneMamegement
{
	// シーンの変更
	inline void RequestChangeScene(const std::string& sceneName)
	{
		static ISceneManager* sceneManager = ServiceLocator::Get<ISceneManager>();
		if (sceneManager != nullptr)
		{
			sceneManager->RequestChangeScene(sceneName);
		}
	}

	// ゲームオブジェクトの検索
	inline GameObject* FindGameObject(const std::string& objectName)
	{
		static ISceneManager* sceneManager = ServiceLocator::Get<ISceneManager>();
		if (sceneManager != nullptr)
		{
			return sceneManager->FindGameObject(objectName);
		}
		else
		{
			return nullptr;
		}
	}

	// ゲームオブジェクトのタグでの検索
	inline GameObject* FindGameObjectWithTag(ObjectTag tag)
	{
		static ISceneManager* sceneManager = ServiceLocator::Get<ISceneManager>();
		if (sceneManager != nullptr)
		{
			return sceneManager->FindGameObjectWithTag(tag);
		}
		else
		{
			return nullptr;
		}

	}

	// ゲームオブジェクトのタグでの検索
	inline std::pair<TagMapIt, TagMapIt> FindGameObjectsWithTag(ObjectTag tag)
	{
		static ISceneManager* sceneManager = ServiceLocator::Get<ISceneManager>();
		if (sceneManager != nullptr)
		{
			return sceneManager->FindGameObjectsWithTag(tag);
		}
		else
		{
			return std::pair<TagMapIt, TagMapIt>();
		}
	}
}
