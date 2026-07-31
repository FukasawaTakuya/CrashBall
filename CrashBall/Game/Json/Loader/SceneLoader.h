/*****************************************************************//**
 * \file   SceneLoader.h
 * \brief  シーンローダー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Factory/GameObjectFactory.h"
#include "Game/Scene/Scene.h"

/**
 * \brief シーンローダー
 */
class  SceneLoader {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneLoader();

	// デストラクタ
	~SceneLoader();

	// 操作
public:

	void LoadScene(Scene* scene);

	// 内部実装
private:

};
