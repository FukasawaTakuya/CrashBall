/*****************************************************************//**
 * \file   GameObjectExporter.h
 * \brief  ゲームオブジェクトエクスポーター
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "Game/GameObject/GameObject.h"

#include "Game/Common/Utility.h"


/**
 * \brief ゲームオブジェクトエクスポーター
 */
class  GameObjectExporter {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObjectExporter();

	// デストラクタ
	~GameObjectExporter();

	// 操作
public:

	// エクスポート
	void ExporterGameObject(GameObject* gameObject, const std::string& exportPath);

	// 取得/設定
public:

	// 内部実装
private:

};
