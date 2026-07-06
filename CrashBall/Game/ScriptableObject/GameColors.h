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
		m_scriptable->AddValue("PlayerColor", ValueType::Vector4, DirectX::Colors::LightSkyBlue);
		m_scriptable->AddValue("EnemyColor", ValueType::Vector4, DirectX::Colors::LightPink);
		m_scriptable->AddValue("DefaultFaceColor", ValueType::Vector4, DirectX::Colors::White);
		m_scriptable->AddValue("AttackGaugeColor", ValueType::Vector4, DirectX::Colors::Yellow);
		m_scriptable->AddValue("AttackGaugeTrackColor", ValueType::Vector4, DirectX::Colors::Gray);
	};

	// デストラクタ
	~GameColors() = default;

	// 操作
public:

	// 取得/設定
public:

	// 要素の取得
	template<typename T>
	static T GetValue(const std::string& key)
	{
		static GameColors instance;
		return std::get<T>(instance.m_scriptable->GetValue(key));
	}


	// 内部実装
private:

};
