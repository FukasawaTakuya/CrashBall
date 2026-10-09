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
	case PadButton::RightStickX:
		return state.buttons.rightStick;
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
 * \brief スティックの状態を取得
 * 
 * \param padButton
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
 * \brief トリガーの押し込み量の取得
 * 
 * \param padButton
 * \return 
 */
float InputSystem::GetTriggerValue(PadButton padButton)
{
	switch (padButton)
	{
	default:
		return 0.0f;
		break;
	}

}