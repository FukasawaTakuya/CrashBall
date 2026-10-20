/*****************************************************************//**
 * \file   InputSystem.h
 * \brief  入力システム
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/IInputService.h"
#include "Game/Common/Screen.h"

/**
 * \brief 入力システム
 */
class InputSystem : public IInputService {

	// メンバ変数の宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseTracker;			// マウスのトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardTracker;		// キーボードのトラッカー

	std::unique_ptr<DirectX::GamePad> m_gamePad;							// ゲームパッド
	std::unique_ptr<DirectX::GamePad::ButtonStateTracker> m_gamePadTracker;	// ゲームパッドのトラッカー

	DirectX::SimpleMath::Vector2 m_mousePos;		// マウス座標
	DirectX::SimpleMath::Vector2 m_prevMousePos;	// 前フレームのマウス座標


	std::array<InputActionState, static_cast<int>(InputAction::ActionConut)> m_inputStates;	// 入力状態
	std::vector<InputBinding> m_bindings;	// 入力評価用

		// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	InputSystem();

public:

	// 操作
public:

	// 更新
	void Update();

	// エディタ上の座標をスクリーン座標に直す
	void EditToScreenPosition(const RECT& EditPos);

	// スクリーン上にマウスが存在するかチェック
	bool CheckHoverScreen() const;

	void ResetWheelValue()
	{
		DirectX::Mouse::Get().ResetScrollWheelValue();
	}

public:

	// キーの状態を取得
	bool GetKeyDown(DirectX::Keyboard::Keys key) override
	{
		return DirectX::Keyboard::Get().GetState().IsKeyDown(key);
	}

	// キートリガーの取得
	bool GetKeyTrigger(DirectX::Keyboard::Keys key) override
	{
		return m_keyboardTracker->IsKeyPressed(key);
	}
	// キーリリースの取得
	bool GetKeyRelease(DirectX::Keyboard::Keys key) override
	{
		return m_keyboardTracker->IsKeyReleased(key);
	}

	// キー入力方向の取得
	float GetKeyAxis(KeyboadAxis axis)
	{
		if (GetKeyDown(axis.plusKey) && !GetKeyDown(axis.minusKey))
		{
			return 1.0f;
		}
		else if (!GetKeyDown(axis.plusKey) && GetKeyDown(axis.minusKey))
		{
			return -1.0f;
		}
		else
		{
			return 0.0f;
		}
	}

	// マウスボタンの状態を取得
	bool GetMouseDown(MouseButton mouseButton) override
	{
		switch (mouseButton)
		{
		case MouseButton::Right:
			return DirectX::Mouse::Get().GetState().rightButton;
			break;
		case MouseButton::Middle:
			return DirectX::Mouse::Get().GetState().middleButton;
			break;
		case MouseButton::Left:
			return DirectX::Mouse::Get().GetState().leftButton;
			break;
		default:
			return false;
			break;
		}
	}

	// マウスボタンのトリガーを取得
	bool GetMouseTrigger(MouseButton mouseButton) override
	{
		switch (mouseButton)
		{
		case MouseButton::Right:
			return m_mouseTracker->rightButton == DirectX::Mouse::ButtonStateTracker::PRESSED;
			break;
		case MouseButton::Middle:
			return m_mouseTracker->middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED;
			break;
		case MouseButton::Left:
			return m_mouseTracker->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED;
			break;
		default:
			return false;
			break;
		}
	}

	// マウスボタンのリリースを取得
	bool GetMouseRelease(MouseButton mouseButton) override
	{
		switch (mouseButton)
		{
		case MouseButton::Right:
			return m_mouseTracker->rightButton == DirectX::Mouse::ButtonStateTracker::RELEASED;
			break;
		case MouseButton::Middle:
			return m_mouseTracker->middleButton == DirectX::Mouse::ButtonStateTracker::RELEASED;
			break;
		case MouseButton::Left:
			return m_mouseTracker->leftButton == DirectX::Mouse::ButtonStateTracker::RELEASED;
			break;
		default:
			return false;
			break;
		}
	}

	// マウス座標の取得
	DirectX::SimpleMath::Vector2 GetMousePos() override
	{
		return m_mousePos;
	}

	// 前フレームのマウス座標の取得
	DirectX::SimpleMath::Vector2 GetPrevMousePos() override
	{
		return m_prevMousePos;
	}

	// ホイール値の取得
	int GetWheelValue() override
	{
		return DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	// ゲームパッドのトリガーを取得
	bool GetGamePadTrigger(PadButton padButton) override;

	// ゲームパッドのリリースを取得
	bool GetGamePadRelease(PadButton padButton) override;

	// ゲームパッドの状態を取得
	bool GetGamePadDown(PadButton padButton) override;

	// ゲームパッドの押し込み量を取得
	float GetGamePadValue(PadButton padButton) override;

	// 入力の取得
	InputActionState GetInputState(InputAction action) override
	{
		return m_inputStates[static_cast<int>(action)];
	}

private:

	// キーボードの入力評価
	void EvaluteBinding(DirectX::Keyboard::Keys key, InputActionState& state);

	// キー入力方向の評価
	void EvaluteBinding(KeyboadAxis axis, InputActionState& state);

	// マウス入力の評価
	void EvaluteBinding(MouseButton mouse, InputActionState& state);

	// ゲームパッド入力の評価
	void EvaluteBinding(PadButton pad, InputActionState& state);
};
