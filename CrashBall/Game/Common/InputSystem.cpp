#include "pch.h"
#include "InputSystem.h"

void InputSystem::Update() {

	auto mouse		= DirectX::Mouse::Get().GetState();
	auto keyboard	= DirectX::Keyboard::Get().GetState();

	m_mouseTracker->Update(mouse);
	m_keyboardTracker->Update(keyboard);

	//OutputDebugString(L"%d\n", sizeof(mouse));
}