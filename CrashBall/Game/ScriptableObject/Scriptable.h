/*****************************************************************//**
 * \file   Scriptable.h
 * \brief  Sriptableオブジェクトをグローバルで取得するためのグローバル関数
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IScriptableObjectManager.h"

namespace Scriptable
{
	// ScriptableObjectの取得
	template<typename T>
	inline const T* GetScriptableObject()
	{
		// ScriptableObjectマネージャ 
		static IScriptableObjectManager* scriptableManager
			= ServiceLocator::Get<IScriptableObjectManager>();
		// マネージャが存在すれば取得する 
		if (scriptableManager != nullptr)
		{
			return scriptableManager->GetScriptableObject<T>();
		}
		// 存在しなければnullptr 
		else return nullptr;
	}

	// ScriptableObjectのコンテナの取得 
	inline const ScriptableObjectContainer* GetScriptableObejctList()
	{
		// ScriptableObjectマネージャ 
		static IScriptableObjectManager* scriptableManager
			= ServiceLocator::Get<IScriptableObjectManager>();
		// マネージャが存在すれば取得する 
		if (scriptableManager != nullptr)
		{
			return scriptableManager->GetScriptableObejctList();
		}
		// 存在しなければnullptr 
		else return nullptr;
	}
}
