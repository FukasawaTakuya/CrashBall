/*****************************************************************//**
 * \file   Input.h
 * \brief  入力状態を取得するためのグローバル関数一覧
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IInputService.h"

namespace Input
{
	// キーの状態を取得
	inline bool GetKeyDown(DirectX::Keyboard::Keys key)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetKeyDown(key);
		}
		// なければfalse
		else return false;
	}

	// キートリガーの取得
	inline bool GetKeyTrigger(DirectX::Keyboard::Keys key)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetKeyTrigger(key);
		}
		// なければfalse
		else return false;
	}

	// キーリリースの取得 
	inline bool GetKeyRelease(DirectX::Keyboard::Keys key)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetKeyRelease(key);
		}
		// なければfalse
		else return false;

	}

	// マウスボタンの状態を取得
	inline bool GetMouseDown(MouseButton mouseButton)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetMouseDown(mouseButton);
		}
		// なければfalse
		else return false;
	}

	// マウスボタンのトリガーを取得
	inline bool GetMouseTrigger(MouseButton mouseButton)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetMouseTrigger(mouseButton);
		}
		// なければfalse
		else return false;

	}

	// マウスボタンのリリースを取得
	inline bool GetMouseRelease(MouseButton mouseButton)
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetMouseRelease(mouseButton);
		}
		// なければfalse
		else return false;
	}

	// マウス座標の取得
	inline DirectX::SimpleMath::Vector2 GetMousePos()
	{
		// 入力システム
		static IInputService* input = ServiceLocator::Get<IInputService>();
		// 入力システムが存在すれば結果を返す
		if (input != nullptr)
		{
			return input->GetMousePos();
		}
		// なければ(0.0f, 0.0f)
		else return DirectX::SimpleMath::Vector2::Zero;
	}
}
