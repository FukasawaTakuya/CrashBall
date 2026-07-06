/*****************************************************************//**
 * \file   ScriptableObject.h
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/ScriptableComponent.h"

/**
 * @brief 
 */
template<typename T>
class  ScriptableObject : private GameObject {

	// データメンバの宣言 -----------------------------------------------
protected:

	ScriptableComponent* m_scriptable = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
protected:

	// コンストラクタ
	ScriptableObject()
	{
		m_scriptable = AddComponent<ScriptableComponent>();
	}

	// 複数生成の禁止
	ScriptableObject(ScriptableObject&) = delete;
	ScriptableObject& operator=(const ScriptableObject&) = delete;

	// デストラクタ
	~ScriptableObject() = default;

public:

	// 操作
public:

	// 初期化
	void Initialize() override {}

	// 更新
	void Update(const GameContext& gameContext) override {}

	// 描画
	void Render(const RenderContext& renderContext) override {}

	// 終了処理
	void Finalize() override {}

	// 取得/設定
public:

	// 内部実装
private:

};
