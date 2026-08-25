/*****************************************************************//**
 * \file   ScriptableObject.h
 * \brief  ScriptableObject
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/ScriptableComponent.h"

/**
 * @brief ScriptableObject
 */
class  ScriptableObject : public GameObject {

	// データメンバの宣言 -----------------------------------------------
protected:

	ScriptableComponent* m_scriptable = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ScriptableObject(json* data);

	// デストラクタ
	virtual ~ScriptableObject() = default;

	// 操作
public:

	// 初期化
	void Start() {}

	// 更新
	void Update(const GameContext& gameContext) override {}

	// 描画
	void Render(const RenderContext& renderContext) override {}

	// 終了処理
	void Finalize() override {}

	// パラメータの書き込み
	void SaveParam()
	{
		GameObject::SaveParam();
		(*m_data)["scriptable"] = *m_scriptable;
	}

	// データの再読み込み
	void ReloadParam()
	{
		GameObject::ReloadParam();
		*m_scriptable = (*m_data)["scriptable"];
	}

	// 取得/設定
public:

	// 要素の取得
	template<typename T>
	T GetValue(const std::string& key) const
	{
		return m_scriptable->GetValue<T>(key);
	}

	// 内部実装
private:

};
