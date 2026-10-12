/*****************************************************************//**
 * \file   InputSystem.cpp
 * \brief  入力システム
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "InputSystem.h"
#include "ImGui/imgui.h"
#include "Game/Common/Screen.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
InputSystem::InputSystem()
	: m_mouseTracker{ std::make_unique<DirectX::Mouse::ButtonStateTracker>() }
	, m_keyboardTracker{ std::make_unique<DirectX::Keyboard::KeyboardStateTracker>() }
	, m_gamePad{ std::make_unique<DirectX::GamePad>() }
	, m_gamePadTracker{ std::make_unique<DirectX::GamePad::ButtonStateTracker>() }
{
	using Keys = DirectX::Keyboard::Keys;

	m_bindings.emplace_back(InputAction::MoveX, PadButton::LeftStickX);
	m_bindings.emplace_back(InputAction::MoveX, KeyboadAxis(Keys::D, Keys::A));
	m_bindings.emplace_back(InputAction::MoveY, PadButton::LeftStickY);
	m_bindings.emplace_back(InputAction::MoveY, KeyboadAxis(Keys::W, Keys::S));

	m_bindings.emplace_back(InputAction::CameraRotateX, PadButton::RightStickX);
	m_bindings.emplace_back(InputAction::CameraRotateX, KeyboadAxis(Keys::Right, Keys::Left));
	m_bindings.emplace_back(InputAction::CameraRotateY, PadButton::RightStickY);
	m_bindings.emplace_back(InputAction::CameraRotateY, KeyboadAxis(Keys::Up, Keys::Down));

	m_bindings.emplace_back(InputAction::Attack, PadButton::A);
	m_bindings.emplace_back(InputAction::Attack, Keys::Space);

	m_bindings.emplace_back(InputAction::Exit, PadButton::Start);
	m_bindings.emplace_back(InputAction::Exit, Keys::Escape);

	m_bindings.emplace_back(InputAction::Back, PadButton::B);
	m_bindings.emplace_back(InputAction::Back, Keys::Escape);

	m_bindings.emplace_back(InputAction::UIMoveX, PadButton::LeftStickX);
	m_bindings.emplace_back(InputAction::UIMoveX, KeyboadAxis(Keys::A, Keys::D));
	m_bindings.emplace_back(InputAction::UIMoveY, PadButton::LeftStickY);
	m_bindings.emplace_back(InputAction::UIMoveY, KeyboadAxis(Keys::W, Keys::S));

	m_bindings.emplace_back(InputAction::Deside, PadButton::A);
	m_bindings.emplace_back(InputAction::Deside, Keys::Space);
}


/**
 * \brief 更新
 * 
 */
void InputSystem::Update() 
{
	auto mouse		= Mouse::Get().GetState();
	auto keyboard	= Keyboard::Get().GetState();

	m_mouseTracker->Update(mouse);
	m_keyboardTracker->Update(keyboard);
	m_gamePadTracker->Update(m_gamePad.get()->GetState(0));

	m_prevMousePos = m_mousePos;
	m_mousePos = SimpleMath::Vector2(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

	Mouse::Get().ResetScrollWheelValue();

	for (auto& state : m_inputStates)
	{
		state.Reset();
	}


	for (auto& binding : m_bindings)
	{
		int index = static_cast<int>(binding.action);
		InputActionState& state = m_inputStates[index];

		std::visit([&, this](const auto& b)
			{
				EvaluteBinding(b, state);
			}, binding.binding);

		if (state.isTrigger)
		{
			int x = 0;
			m_inputStates[static_cast<int>(InputAction::Deside)];
		}
	}
}

/**
 * \brief エディタ上の座標をスクリーン座標に直す
 * 
 * \param editPos エディタ上のマウス座標
 */
void InputSystem::EditToScreenPosition(const RECT& editPos)
{
	ImVec2 mousePos = ImGui::GetMousePos();

	mousePos.x -= editPos.left;
	mousePos.y -= editPos.top;

	mousePos.x /= (editPos.right - editPos.left);
	mousePos.y /= (editPos.bottom - editPos.top);

	m_mousePos.x = mousePos.x * Screen::FULL_WIDTH * Screen::GetScreenRate();
	m_mousePos.y = mousePos.y * Screen::FULL_HEIGHT * Screen::GetScreenRate();
}

/**
 * \brief スクリーン上にマウスが存在するかチェック
 * 
 * \return 
 */
bool InputSystem::CheckHoverScreen() const
{
	if (m_mousePos.x > 0.0f && m_mousePos.x < Screen::WIDTH &&
		m_mousePos.y > 0.0f && m_mousePos.y < Screen::HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * \brief ゲームパッドのトリガーの取得
 * 
 * \param padButton ボタン
 * \return 
 */
bool InputSystem::GetGamePadTrigger(PadButton padButton)
{
	using ButtonState = GamePad::ButtonStateTracker::ButtonState;

	switch (padButton)
	{
	case PadButton::A:
		return m_gamePadTracker->a == ButtonState::PRESSED;
		break;
	case PadButton::B:
		return m_gamePadTracker->b == ButtonState::PRESSED;
		break;
	case PadButton::X:
		return m_gamePadTracker->x == ButtonState::PRESSED;
		break;
	case PadButton::Y:
		return m_gamePadTracker->y == ButtonState::PRESSED;
		break;
	case PadButton::LeftStick:
		return m_gamePadTracker->leftStickLeft == ButtonState::PRESSED;
	case PadButton::LeftStickX:
		return m_gamePadTracker->leftStickLeft == ButtonState::PRESSED;
	case PadButton::LeftStickY:
		return m_gamePadTracker->leftStickLeft == ButtonState::PRESSED;
		break;
	case PadButton::RightStick:
		return m_gamePadTracker->rightStickLeft == ButtonState::PRESSED;
		break;
	case PadButton::RightStickX:
		return m_gamePadTracker->rightStickLeft == ButtonState::PRESSED;
		break;
	case PadButton::RightStickY:
		return m_gamePadTracker->rightStickLeft == ButtonState::PRESSED;
		break;
	case PadButton::LeftShoulder:
		return m_gamePadTracker->leftShoulder == ButtonState::PRESSED;
		break;
	case PadButton::RightShoulder:
		return m_gamePadTracker->rightShoulder == ButtonState::PRESSED;
		break;
	case PadButton::LeftTrigger:
		return m_gamePadTracker->leftTrigger == ButtonState::PRESSED;
		break;
	case PadButton::RightTrigger:
		return m_gamePadTracker->rightTrigger == ButtonState::PRESSED;
		break;
	case PadButton::Up:
		return m_gamePadTracker->dpadUp == ButtonState::PRESSED;
		break;
	case PadButton::Down:
		return m_gamePadTracker->dpadDown == ButtonState::PRESSED;
		break;
	case PadButton::Left:
		return m_gamePadTracker->dpadLeft == ButtonState::PRESSED;
		break;
	case PadButton::Right:
		return m_gamePadTracker->dpadRight == ButtonState::PRESSED;
		break;
	case PadButton::Back:
		return m_gamePadTracker->back == ButtonState::PRESSED;
		break;
	case PadButton::View:
		return m_gamePadTracker->view == ButtonState::PRESSED;
		break;
	case PadButton::Start:
		return m_gamePadTracker->start == ButtonState::PRESSED;
		break;
	case PadButton::Menu:
		return m_gamePadTracker->menu == ButtonState::PRESSED;
		break;
	default:
		break;
	}

}

/**
 * \brief ゲームパッドのリリースを取得
 * 
 * \param padButton ボタン
 * \return 
 */
bool InputSystem::GetGamePadRelease(PadButton padButton)
{
	using ButtonState = GamePad::ButtonStateTracker::ButtonState;

	switch (padButton)
	{
	case PadButton::A:
		return m_gamePadTracker->a == ButtonState::RELEASED;
		break;
	case PadButton::B:
		return m_gamePadTracker->b == ButtonState::RELEASED;
		break;
	case PadButton::X:
		return m_gamePadTracker->x == ButtonState::RELEASED;
		break;
	case PadButton::Y:
		return m_gamePadTracker->y == ButtonState::RELEASED;
		break;
	case PadButton::LeftStick:
		return m_gamePadTracker->leftStickLeft == ButtonState::RELEASED;
	case PadButton::LeftStickX:
		return m_gamePadTracker->leftStickLeft == ButtonState::RELEASED;
	case PadButton::LeftStickY:
		return m_gamePadTracker->leftStickLeft == ButtonState::RELEASED;
		break;
	case PadButton::RightStick:
		return m_gamePadTracker->rightStickLeft == ButtonState::RELEASED;
		break;
	case PadButton::RightStickX:
		return m_gamePadTracker->rightStickLeft == ButtonState::RELEASED;
		break;
	case PadButton::RightStickY:
		return m_gamePadTracker->rightStickLeft == ButtonState::RELEASED;
		break;
	case PadButton::LeftShoulder:
		return m_gamePadTracker->leftShoulder == ButtonState::RELEASED;
		break;
	case PadButton::RightShoulder:
		return m_gamePadTracker->rightShoulder == ButtonState::RELEASED;
		break;
	case PadButton::LeftTrigger:
		return m_gamePadTracker->leftTrigger == ButtonState::RELEASED;
		break;
	case PadButton::RightTrigger:
		return m_gamePadTracker->rightTrigger == ButtonState::RELEASED;
		break;
	case PadButton::Up:
		return m_gamePadTracker->dpadUp == ButtonState::RELEASED;
		break;
	case PadButton::Down:
		return m_gamePadTracker->dpadDown == ButtonState::RELEASED;
		break;
	case PadButton::Left:
		return m_gamePadTracker->dpadLeft == ButtonState::RELEASED;
		break;
	case PadButton::Right:
		return m_gamePadTracker->dpadRight == ButtonState::RELEASED;
		break;
	case PadButton::Back:
		return m_gamePadTracker->back == ButtonState::RELEASED;
		break;
	case PadButton::View:
		return m_gamePadTracker->view == ButtonState::RELEASED;
		break;
	case PadButton::Start:
		return m_gamePadTracker->start == ButtonState::RELEASED;
		break;
	case PadButton::Menu:
		return m_gamePadTracker->menu == ButtonState::RELEASED;
		break;
	default:
		break;
	}
}

/**
 * \brief ゲームパッドの状態を取得
 * 
 * \param padButton ボタン
 * \return 
 */
bool InputSystem::GetGamePadState(PadButton padButton)
{
	auto state = m_gamePad->GetState(0);
	switch (padButton)
	{
	case PadButton::A:
		return state.buttons.a;
		break;
	case PadButton::B:
		return state.buttons.b;
		break;
	case PadButton::X:
		return state.buttons.x;
		break;
	case PadButton::Y:
		return state.buttons.y;
		break;
	case PadButton::LeftStick:
		return state.buttons.leftStick;
	case PadButton::LeftStickX:
		return state.buttons.leftStick;
	case PadButton::LeftStickY:
		return state.buttons.leftStick;
		break;
	case PadButton::RightStick:
		return state.buttons.rightStick;
		break;
	case PadButton::RightStickX:
		return state.buttons.rightStick;
		break;
	case PadButton::RightStickY:
		return state.buttons.rightStick;
		break;
	case PadButton::LeftShoulder:
		return state.buttons.leftShoulder;
		break;
	case PadButton::RightShoulder:
		return state.buttons.rightShoulder;
		break;
	case PadButton::LeftTrigger:
		return state.IsLeftTriggerPressed();
		break;
	case PadButton::RightTrigger:
		return state.IsRightTriggerPressed();
		break;
	case PadButton::Up:
		return state.buttons.back;
		break;
	case PadButton::Down:
		return state.buttons.view;
		break;
	case PadButton::Left:
		return state.buttons.back;
		break;
	case PadButton::Right:
		return state.buttons.view;
		break;
	case PadButton::Back:
		return state.buttons.back;
		break;
	case PadButton::View:
		return state.buttons.view;
		break;
	case PadButton::Start:
		return state.buttons.start;
		break;
	case PadButton::Menu:
		return state.buttons.menu;
		break;
	default:
		break;
	}
}

/**
 * \brief ボタンの押し込み量を取得
 * 
 * \param padButton ボタン
 * \return 
 */
float InputSystem::GetGamePadValue(PadButton padButton)
{
	switch (padButton)
	{
	case PadButton::LeftStickX:
		m_gamePad->GetState(0).thumbSticks.leftX;
		break;
	case PadButton::LeftStickY:
		m_gamePad->GetState(0).thumbSticks.leftY;
		break;
	case PadButton::RightStickX:
		m_gamePad->GetState(0).thumbSticks.rightX;
		break;
	case PadButton::RightStickY:
		m_gamePad->GetState(0).thumbSticks.rightY;
		break;
	case PadButton::LeftTrigger:
		m_gamePad->GetState(0).triggers.left;
		break;
	case PadButton::RightTrigger:
		m_gamePad->GetState(0).triggers.right;
		break;
	default:
		return GetGamePadState(padButton) ? 1.0f : 0.0f;
		break;
	}
}

/**
 * \brief キーボードの入力評価
 * 
 * \param key キー
 * \param state 入力状態
 */
void InputSystem::EvaluteBinding(DirectX::Keyboard::Keys key, InputActionState& state)
{
	if (GetKeyDown(key))
	{
		state.isPresed = true;
		state.value += 1.0f;
	}
	if (GetKeyTrigger(key))
	{
		state.isTrigger = true;
	}
	if (GetKeyRelease(key))
	{
		state.isRelease = true;
	}
}

/**
 * \brief
 * 
 * \param key
 * \param state
 */
void InputSystem::EvaluteBinding(KeyboadAxis axis, InputActionState& state)
{
	state.value += GetKeyAxis(axis);
}

/**
 * \brief マウス入力の評価
 * 
 * \param mouse
 * \param state
 */
void InputSystem::EvaluteBinding(MouseButton mouse, InputActionState& state)
{
	if (GetMouseDown(mouse))
	{
		state.isPresed = true;
		state.value += 1.0f;
	}
	if (GetMouseTrigger(mouse))
	{
		state.isTrigger = true;
	}
	if (GetMouseRelease(mouse))
	{
		state.isRelease = true;
	}
}

/**
 * \brief ゲームパッド入力の評価
 * 
 * \param pad
 * \param state
 */
void InputSystem::EvaluteBinding(PadButton pad, InputActionState& state)
{
	if (GetGamePadState(pad))
	{
		state.isPresed = true;
	}
	if (GetGamePadTrigger(pad))
	{
		state.isTrigger = true;
	}
	if (GetGamePadRelease(pad))
	{
		state.isRelease = true;
	}

	if (GetGamePadValue(pad) != 0.0f)
	{
		state.value += GetGamePadValue(pad);
	}
}

