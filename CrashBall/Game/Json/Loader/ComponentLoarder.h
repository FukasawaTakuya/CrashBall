/*****************************************************************//**
 * \file   ComponentLoarder.h
 * \brief  コンポーネント読み込み
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/Component/Default/Component.h"

class GameObject;

/**
 * \brief 
 */
class  ComponentLoader {
	// データメンバの宣言 -----------------------------------------------
private:

	using CreataFunc = Component* (*)(json);

	std::unordered_map<std::string, CreataFunc> m_createComp;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ComponentLoader();

	// デストラクタ
	~ComponentLoader();

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

	Component* CreataTransform(GameObject* gameObject, json data);

};
