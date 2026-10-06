/*****************************************************************//**
 * \file   EditButton.h
 * \brief  編集ボタン
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/Scene/Interface/ISceneEditer.h"
#include "Game/Json/IJsonDataManager.h"
#include "Game/GameObject/GameObject.h"
#include "Interface/IEditModeChanger.h"

/**
 * \brief 編集ボタン
 */
class  EditButton {

	// メンバ関数の宣言 -------------------------------------------------

	IEditModeChanger* m_editModeChanger   = nullptr;	// 編集モード切り替え

	
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EditButton(IEditModeChanger* editModeChanger);

	// デストラクタ
	~EditButton();

	// 操作
public:

	// 更新
	void Update(ISceneEditer* sceneEditer);

	// 取得/設定
public:

	// 内部実装
private:

};
