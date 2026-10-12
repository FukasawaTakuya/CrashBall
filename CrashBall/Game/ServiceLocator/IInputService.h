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

	// ゲームパッドのトリガーを取得
	virtual bool GetGamePadTrigger(PadButton padButton) = 0;

	// ゲームパッドのリリースを取得
	virtual bool GetGamePadRelease(PadButton padButton) = 0;

	// ゲームパッドの状態をの取得
	virtual bool GetGamePadDown(PadButton padButton) = 0;

	// ゲームパッドの押し込み量を取得
	virtual float GetGamePadValue(PadButton padButton) = 0;

	// 入力の取得
	virtual InputActionState GetInputState(InputAction action) = 0;

	// 内部実装
private:


};
