/*****************************************************************//**
 * \file   ISceneEditer.h
 * \brief  シーン編集機能のインタフェース
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once


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

	// 初期化
	virtual void Initialize() = 0;

	// パラメータの書き込み
	virtual void SaveParam() = 0;

	// パラメータの再読み込み
	virtual void ReloadParam() = 0;


	// 取得/設定
public:

	// 内部実装
private:

};
