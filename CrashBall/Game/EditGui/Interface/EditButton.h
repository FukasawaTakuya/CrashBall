/*****************************************************************//**
 * \file   EditButton.h
 * \brief  編集ボタン
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/Scene/Interface/ISceneEditer.h"

/**
 * \brief 編集ボタン
 */
class  EditButton {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EditButton();

	// デストラクタ
	~EditButton();

	// 操作
public:

	// 更新
	void Update(ISceneEditer* pSceneEditer);

	// 取得/設定
public:

	// 内部実装
private:

};
