/*****************************************************************//**
 * \file   IScriptableObjectManager.h
 * \brief  ScriptableObject管理インターフェース
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Service.h"

#include <unordered_map>
#include <string>
#include <memory>

#include "Game/GameObject/IGameObject.h"
#include "Game/ScriptableObject/ScriptableObject.h"

 // ScriptableObjectのコンテナのエイリアス宣言
using ScriptableObjectContainer
	= std::unordered_map<std::type_index, std::unique_ptr<ScriptableObject>>;

/**
 * \brief ScriptableObject管理インターフェース
 */
class  IScriptableObjectManager : public Service {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IScriptableObjectManager() = default;

	// デストラクタ
	virtual ~IScriptableObjectManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// ScriptableObjectの取得
	template<typename Scriptable>
	Scriptable* GetScriptableObject()
	{
		ScriptableComponent* ptr = GetScriptableObject(typeid(Scriptable));

		if (ptr != nullptr)
		{
			return static_cast<Scriptable*>(ptr);
		}
		else
		{
			return nullptr;
		}
	}


	// ScriptableObjectのコンテナの取得
	virtual const ScriptableObjectContainer* GetScriptableObejctList() = 0;

	// 内部実装
protected:
	// 関数テンプレート無しでScriptableObjectを取得する
	virtual ScriptableComponent* GetScriptableObject(std::type_index type) = 0;


};
