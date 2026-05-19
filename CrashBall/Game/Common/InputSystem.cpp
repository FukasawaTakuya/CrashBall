/*****************************************************************//**
 * \file   InputSystem.cpp
 * \brief  入力システム
 * 
 * \author it252184
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "InputSystem.h"

void InputSystem::Update() 
{

	auto mouse		= DirectX::Mouse::Get().GetState();
	auto keyboard	= DirectX::Keyboard::Get().GetState();

	m_mouseTracker->Update(mouse);
	m_keyboardTracker->Update(keyboard);
}