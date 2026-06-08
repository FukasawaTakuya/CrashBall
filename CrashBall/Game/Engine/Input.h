/*****************************************************************//**
 * \file   Input.h
 * \brief  入力状態を取得するためのグローバル関数
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IInputService.h"

namespace Input
{
	/**
	 * \brief キーコンディションの取得 
	 * 
	 * \param key キー
	 * \return true キーが押されている
	 */
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

	
	/**
	 * \brief キートリガーの取得
	 * 
	 * \param key キー
	 * \return true キーが押された
	 */
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

	
	/**
	 * \brief キーリリースの取得 
	 * 
	 * \param key　キー
	 * \return true キーが離された
	 */
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

	/**
	 * \brief マウス座標の取得
	 * 
	 * \return マウス座標
	 */
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
