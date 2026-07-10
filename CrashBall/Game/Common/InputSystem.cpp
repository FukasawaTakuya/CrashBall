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

	m_mousePos = SimpleMath::Vector2(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
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
