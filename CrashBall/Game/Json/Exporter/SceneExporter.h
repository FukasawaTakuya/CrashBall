/*****************************************************************//**
 * \file   SceneExporter.h
 * \brief  シーンエクスポーター
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/
#pragma once

#include "Game/Scene/Scene.h"
#include "GameObjectExporter.h"

/**
 * \brief シーンエクスポーター
 */
class  SceneExporter {

	// データメンバの宣言 -----------------------------------------------
private:

	// ゲームオブジェクトエクスポーター
	std::unique_ptr<GameObjectExporter> m_gameObjectExporter;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneExporter();
	// デストラクタ
	~SceneExporter();

	// 操作
public:

	// シーンの書き込み
	void ExportScene(Scene* scene);

	// 取得/設定
public:

	// 内部実装
private:

};
