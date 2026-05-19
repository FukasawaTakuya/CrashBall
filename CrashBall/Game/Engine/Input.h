/*****************************************************************//**
 * \file   Input.h
 * \brief  入力状態を取得するためのグローバルAPI 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IInputService.h"

namespace Input
{
	// キーコンディションの取得 
	inline bool GetKeyDown(DirectX::Keyboard::Keys key)
	{
		return ServiceLocator::Get<IInputService>()->GetKeyDown(key);
	}

	// キートリガーの取得 
	inline bool GetKeyTrigger(DirectX::Keyboard::Keys key)
	{
		return ServiceLocator::Get<IInputService>()->GetKeyTrigger(key);
	}

	// キーリリースの取得 
	inline bool GetKeyRelease(DirectX::Keyboard::Keys key)
	{
		return ServiceLocator::Get<IInputService>()->GetKeyRelease(key);
	}

	// マウス座標の取得 
	inline DirectX::SimpleMath::Vector2 GetMousePos()
	{
		return ServiceLocator::Get<IInputService>()->GetMousePos();
	}
}
