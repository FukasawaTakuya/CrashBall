/*****************************************************************//**
 * \file   ISceneEditer.h
 * \brief  シーン編集機能のインタフェース
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include <vector>
#include <memory>

class GameObject;

/**
 * \brief シーン編集機能のインタフェース
 */
class  ISceneEditer {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISceneEditer() = default;

	// デストラクタ
	virtual ~ISceneEditer() = default;

	// 操作
public:

	// 開始処理
	virtual void Start() = 0;

	// パラメータの書き込み
	virtual void SaveData() = 0;

	// 新しいゲームオブジェクトの生成
	virtual void CreateNewGameObject() = 0;

	// ゲームオブジェクトの削除
	virtual void DeleteGameObject(GameObject* obj) = 0;

	// 取得/設定
public:

	// ゲームオブジェクトの取得
	virtual std::vector<std::unique_ptr<GameObject>>& GetGameObjects() = 0;

	// 内部実装
private:

};
