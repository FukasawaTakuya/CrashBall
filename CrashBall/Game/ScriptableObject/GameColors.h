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
		m_scriptable->AddValue("PlayerColor",			ValueType::Color, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::LightSkyBlue));
		m_scriptable->AddValue("EnemyColor",			ValueType::Color, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::LightPink));
		m_scriptable->AddValue("DefaultFaceColor",		ValueType::Color, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::White));
		m_scriptable->AddValue("AttackGaugeColor",		ValueType::Color, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::Yellow));
		m_scriptable->AddValue("AttackGaugeTrackColor", ValueType::Color, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::Gray));
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
		//instance.m_scriptable = (*instance.m_data)["scriptable"];
	}

	// 初期化用のパラメータの書き込み
	static void SaveInitParam()
	{
		auto& instance = CreateInstance();
		instance.GameObject::SaveInitParam();
		//instance.m_scriptable = (*instance.m_data)["scriptable"];
	}

	// データの再読み込み
	static void ReloadParam()
	{
		auto& instance = CreateInstance();
		instance.GameObject::ReloadParam();
		// (*instance.m_data)["scriptable"] = instance.m_scriptable;
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
