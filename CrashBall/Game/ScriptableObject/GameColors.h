#pragma once

#include "Game/GameObject/ScriptableObject.h"

/**
 * @brief 
 */
class  GameColors : public ScriptableObject<GameColors> {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameColors()
		: ScriptableObject()
	{
	};

	// デストラクタ
	~GameColors() = default;

	// 操作
public:

	// パラメータの書き込み
	static void SaveParam()
	{
		auto& instance = CreateInstance();
		instance.GameObject::SaveParam();
		(*instance.m_data)["scriptable"] = *instance.m_scriptable;
	}

	// 初期化用のパラメータの書き込み
	static void SaveInitParam()
	{
		auto& instance = CreateInstance();
		instance.GameObject::SaveInitParam();
	}

	// データの再読み込み
	static void ReloadParam()
	{
		auto& instance = CreateInstance();
		instance.GameObject::ReloadParam();

		*instance.m_scriptable = (*instance.m_data)["scriptable"];
	}

	// 取得/設定
public:

	// 要素の取得
	template<typename T>
	static T GetValue(const std::string& key)
	{
		return std::get<T>(GetInstance().m_scriptable->GetValue(key));
	}

	// データの設定
	static void SetData(json* data)
	{
		CreateInstance().GameObject::SetData(data);
		ReloadParam();
	}

	// インスタンスの取得
	static const GameColors& GetInstance()
	{
		return CreateInstance();
	}

	// 内部実装
private:

	// インスタンスの生成
	static GameColors& CreateInstance()
	{
		static GameColors instance;
		return instance;
	}
};
