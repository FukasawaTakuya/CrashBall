/*****************************************************************//**
 * \file   ScriptableObjectManager.h
 * \brief  ScriptableObject管理
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "ScriptableObject.h"

#include "Game/ServiceLocator/IScriptableObjectManager.h"

/**
 * \brief ScriptableObject管理
 */
class  ScriptableObjectManager : public IScriptableObjectManager
{

	// データメンバの宣言 -----------------------------------------------
private:

	// ScriptableObjectのコンテナ
	ScriptableObjectContainer m_scriptableObjectList;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ScriptableObjectManager();

	// デストラクタ
	~ScriptableObjectManager();

	// 操作
public:

	// ScriptableObjectの登録
	void RegisterObject(
		const std::string& key,
		std::unique_ptr<ScriptableObject> object);

	// パラメータの保存
	void SaveParam();

	// パラメータの再読み込み
	void ReloadParam();

	// 取得/設定
public:

	// ScriptableObjectの取得
	const ScriptableObject* GetScriptableObject(const std::string& key) override;

	// ScriptableObjectのコンテナの取得
	const ScriptableObjectContainer* GetScriptableObejctList()
	{
		return &m_scriptableObjectList;
	}

	// 内部実装
private:
};
