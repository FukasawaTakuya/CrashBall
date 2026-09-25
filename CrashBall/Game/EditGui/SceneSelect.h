#pragma once

#include "Game/Scene/Interface/ISceneEditer.h"

/**
 * @brief シーン選択
 */
class  SceneSelect {


	// データメンバの宣言 -----------------------------------------------
private:
	


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneSelect();

	// デストラクタ
	~SceneSelect();

	// 操作
public:

	// 更新
	void Update(ISceneEditer* sceneEditer);

	// 取得/設定
public:

	// 内部実装
private:

};
