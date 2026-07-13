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

#include "Game/ScriptableObject/ScriptableObject.h"

/**
 * \brief ScriptableObject管理インターフェース
 */
class  IScriptableObjectManager : public Service {

public:
	// ScriptableObjectのコンテナのエイリアス宣言
	using ScriptableObjectContainer
		= std::unordered_map<std::string, std::unique_ptr<ScriptableObject>>;

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

	// スクリプタブルオブジェクトの取得
	virtual ScriptableObject* GetScriptableObject(const std::string& key) = 0;;

	// 内部実装
private:

};
