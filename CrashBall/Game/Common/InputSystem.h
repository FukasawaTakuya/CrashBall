#pragma once

enum class PlayActionFlag
{
	Up		= 1 << 0,
	Down	= 1 << 1,
	Right	= 1 << 2,
	Left	= 1 << 3,
	Jump	= 1 << 4,
};

class InputSystem{

private:

	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseTracker;			// マウスのトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardTracker;		// キーボードのトラッカー

	//PlayActionFlag flag;

private:

	InputSystem() 
		: m_mouseTracker	{ std::make_unique<DirectX::Mouse::ButtonStateTracker>()		}
		, m_keyboardTracker	{ std::make_unique<DirectX::Keyboard::KeyboardStateTracker>()	}
	{}

	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

public:
	static InputSystem& Instance() {
		static InputSystem instance;
		return instance;
	}

public:

	void Update();

public:

	// マウスのトラッカーの取得
	DirectX::Mouse::ButtonStateTracker*			GetMouseTracker()	{ return m_mouseTracker.get(); }
	// キーボードのトラッカーの取得
	DirectX::Keyboard::KeyboardStateTracker*	GetKeyboardTracker(){ return m_keyboardTracker.get(); }

	// マウス座標の取得
	DirectX::SimpleMath::Vector2 GetMousePos() {
		auto mouse = DirectX::Mouse::Get().GetState();
		return DirectX::SimpleMath::Vector2( static_cast<float>(mouse.x), static_cast<float>(mouse.y) );
	}
};
