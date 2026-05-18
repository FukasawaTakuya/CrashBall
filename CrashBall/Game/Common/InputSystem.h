#pragma once

#include "Game/Interface/IInputSystem.h"

enum class PlayActionFlag
{
	Up		= 1 << 0,
	Down	= 1 << 1,
	Right	= 1 << 2,
	Left	= 1 << 3,
	Jump	= 1 << 4,
};

class InputSystem : public IInputSystem{

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseTracker;			// マウスのトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardTracker;		// キーボードのトラッカー

	//PlayActionFlag flag;

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

	// マウス座標の取得
	DirectX::SimpleMath::Vector2 GetMousePos() override
	{
		auto mouse = DirectX::Mouse::Get().GetState();
		return DirectX::SimpleMath::Vector2( static_cast<float>(mouse.x), static_cast<float>(mouse.y) );
	}
};
