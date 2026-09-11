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
	ScriptableObject();

	// デストラクタ
	virtual ~ScriptableObject() = default;

	// 取得/設定
public:

	// スクリプタブルオブジェクトの取得
	ScriptableComponent* Get() const
	{
		return m_scriptable;
	}

	// スクリプタブルオブジェクトの設定
	Component* Set(std::unique_ptr<Component>&& comp)
	{
		ScriptableComponent* ptr = dynamic_cast<ScriptableComponent*>(comp.get());
		if (ptr != nullptr)
		{
			m_scriptable = ptr;
		}
		GameObject::AddComponent(std::move(comp));

		return ptr;
	}

	// 内部実装
private:

};
