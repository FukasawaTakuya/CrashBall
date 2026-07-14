/*****************************************************************//**
 * \file   IEditModeChanger.h
 * \brief  編集モード切替機能のインターフェース
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

/**
 * \brief 編集モード切替機能のインターフェース
 */
class  IEditModeChanger {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IEditModeChanger() = default;

	// デストラクタ
	~IEditModeChanger() = default;

	// 操作
public:

	// 取得/設定
public:

	// 編集モードフラグの取得
	virtual bool GetEditMode() const = 0;

	// 編集モードフラグの設定
	virtual void SetEditMode(bool flag) = 0;

	// 内部実装
private:

};
