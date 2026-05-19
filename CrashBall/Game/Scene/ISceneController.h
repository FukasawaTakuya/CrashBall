/*****************************************************************//**
 * \file   ISceneController.h
 * \brief  シーン変更機能を持ったインターフェース 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

enum class SceneID {
	None,
	Title,
	Game,
	Result,
};


/**
 * @brief シーン変更機能を持ったインターフェース
 */
class  ISceneController {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISceneController() = default;

	// デストラクタ
	virtual ~ISceneController() = default;

	// 操作
public:

	virtual void RequestChangeScene(SceneID sceneID) = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
