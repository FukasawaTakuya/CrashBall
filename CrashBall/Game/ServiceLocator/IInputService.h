/*****************************************************************//**
 * \file   IInputService.h
 * \brief  入力システムクラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>
#include <GamePad.h>

#include "Game/ServiceLocator/Service.h"
#include <variant>

#include "Game/Common/InputCommon.h"

/**
 * @brief 入力システムクラスのインターフェース
 */
class  IInputService : public Service{

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IInputService() = default;

	// デストラクタ
	virtual ~IInputService() = default;

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


	virtual bool GetMouseDown(MouseButton mouseButton) = 0;
	// マウスボタンのトリガーを取得
	virtual bool GetMouseTrigger(MouseButton mouseButton) = 0;
	// マウスボタンのリリースを取得
	virtual bool GetMouseRelease(MouseButton mouseButton) = 0;

	// マウス座標の取得
	virtual DirectX::SimpleMath::Vector2 GetMousePos() = 0;

	// 前フレームのマウス座標の取得
	virtual DirectX::SimpleMath::Vector2 GetPrevMousePos() = 0;

	// ホイール値の取得
	virtual int GetWheelValue() = 0;

	virtual DirectX::GamePad::State GetGamePad() = 0;

	virtual DirectX::GamePad::ButtonStateTracker* GetGamePadTracker() = 0;

	// パッドのボタンの状態を取得
	virtual bool GetGamePadState(PadButton padButton) = 0;

	//// ボタンの値の取得
	//template<typename T>
	//T GetGamePadValue(PadButton padButton) { return T{}; }

	//template<>
	//DirectX::SimpleMath::Vector2 GetGamePadValue(PadButton padButton)
	//{
	//	return GetGamePadValue(padButton);
	//}

	//template<>
	//float GetGamePadValue(PadButton padButton)
	//{
	//	return GetTriggerValue(padButton);
	//}

	// スティックの状態を取得
	virtual float GetGamePadValue(PadButton padButton) = 0;

	// トリガーの押し込み量を取得
	virtual float GetTriggerValue(PadButton padButton) = 0;


	// 内部実装
private:


};
