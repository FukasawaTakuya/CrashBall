/*****************************************************************//**
 * \file   InputSystem.h
 * \brief  入力システム
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/IInputService.h"

class InputSystem : public IInputService {

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseTracker;			// マウスのトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardTracker;		// キーボードのトラッカー

		// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	InputSystem() 
		: m_mouseTracker	{ std::make_unique<DirectX::Mouse::ButtonStateTracker>()		}
		, m_keyboardTracker	{ std::make_unique<DirectX::Keyboard::KeyboardStateTracker>()	}
	{}

public:

	// 操作
public:

	// 更新
	void Update();

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
		auto mouse = DirectX::Mouse::Get().GetState();
		return DirectX::SimpleMath::Vector2( static_cast<float>(mouse.x), static_cast<float>(mouse.y) );
	}
};
