#pragma once
#include "Keyboard.h"

enum class MouseButton
{
	Right,
	Middle,
	Left,
};

struct KeyboadAxis
{
	DirectX::Keyboard::Keys plusKey;
	DirectX::Keyboard::Keys minusKey;

	KeyboadAxis(
		DirectX::Keyboard::Keys plusKey,
		DirectX::Keyboard::Keys minusKey)
		: plusKey(plusKey)
		, minusKey(minusKey) {
	}
};

enum class PadButton
{
	A,
	B,
	X,
	Y,
	LeftStick,
	LeftStickX,
	LeftStickY,
	RightStick,
	RightStickX,
	RightStickY,
	LeftShoulder,
	RightShoulder,
	LeftTrigger,
	RightTrigger,
	Up,
	Down,
	Right,
	Left,
	Back,
	View,
	Start,
	Menu,
};

using BindingVariant
= std::variant<
	DirectX::Keyboard::Keys,
	KeyboadAxis,
	MouseButton,
	PadButton>;

struct InputActionState
{
	bool isPresed = false;
	bool isTrigger = false;
	bool isRelease = false;

	float value = 0.0f;
};
