#pragma once
#include "Keyboard.h"

// マウスボタン
enum class MouseButton
{
	Right,
	Middle,
	Left,
};

// キーボードの入力方向
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

// ゲームパッドボタン
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

// インプットアクション
enum class InputAction
{
	MoveX,
	MoveY,
	Attack,
	Jump,
	CameraRotateX,
	CameraRotateY,

	UIMoveX,
	UIMoveY,
	Deside,
	Exit,
	Back,

	ActionConut,
};

using BindingVariant
= std::variant<
	DirectX::Keyboard::Keys,
	KeyboadAxis,
	MouseButton,
	PadButton>;

// 入力評価
struct InputBinding
{
	InputAction action;
	BindingVariant binding;
};

// 入力状態
struct InputActionState
{
	bool isPresed = false;
	bool isTrigger = false;
	bool isRelease = false;

	float value = 0.0f;

	void Reset()
	{
		isPresed = false;
		isTrigger = false;
		isRelease = false;

		value = 0.0f;
	}
};
