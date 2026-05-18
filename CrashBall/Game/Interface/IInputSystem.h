/*****************************************************************//**
 * \file   IInputSystem.h
 * \brief  入力システムクラスのインターフェースに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>

/**
 * @brief 入力システムクラスのインターフェース
 */
class  IInputSystem {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IInputSystem() = default;

	// デストラクタ
	virtual ~IInputSystem() = default;

	// 操作
public:

	// 取得/設定
public:

	// キーの状態を取得
	virtual bool GetKeyDown(DirectX::Keyboard::Keys key) = 0;
	// キートリガーの取得
	virtual bool GetKeyTrigger(DirectX::Keyboard::Keys key) = 0;
	// キーリリースの取得
	virtual bool GetKeyRelease(DirectX::Keyboard::Keys key) = 0;

	// マウス座標の取得
	virtual DirectX::SimpleMath::Vector2 GetMousePos() = 0;


	// 内部実装
private:

};
