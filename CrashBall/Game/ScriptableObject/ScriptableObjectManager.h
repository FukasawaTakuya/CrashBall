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
#include "Game/Json/JsonDataManager.h"

/**
 * \brief ScriptableObject管理
 */
class  ScriptableObjectManager : public IScriptableObjectManager
{

	// データメンバの宣言 -----------------------------------------------
private:

	// Jsonデータ管理
	std::unique_ptr<JsonDataManager> m_jsonManager;

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

	// ScriptableObjectの読み込み
	void LoadScriptableObject();

	// ScriptableObjectの登録
	void RegisterObject(
		const std::string& key,
		std::unique_ptr<ScriptableObject> object);

	// パラメータの保存
	void SaveData();

	// 取得/設定
public:

	// ScriptableObjectの取得
	using IScriptableObjectManager::GetScriptableObject;

	// ScriptableObjectのコンテナの取得
	const ScriptableObjectContainer* GetScriptableObejctList() override
	{
		return &m_scriptableObjectList;
	}

	// 内部実装
private:

	// 関数テンプレート無しでScriptableObjectを取得する
	ScriptableComponent* GetScriptableObject(std::type_index type) override
	{
		auto it = m_scriptableObjectList.find(type);
		// イテレータが終端でなければコンポーネントを返す
		if (it != m_scriptableObjectList.end()) {
			return it->second->Get();
		}
		// イテレータが終端ならnullptrを返す
		else return nullptr;
	}
};
