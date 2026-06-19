/*****************************************************************//**
 * \file   GameColor.h
 * \brief  ゲームで使う色
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include<DirectXColors.h>

namespace GameColor
{
	const DirectX::XMVECTORF32 PLAYER					= DirectX::Colors::LightSkyBlue;	// プレイヤー
	const DirectX::XMVECTORF32 ENEMY					= DirectX::Colors::LightPink;		// 敵
	const DirectX::XMVECTORF32 DEFAULT_FACE				= DirectX::Colors::White;			// デフォルトの面
	const DirectX::XMVECTORF32 ATTACKGAUGE				= DirectX::Colors::Yellow;			// 攻撃ゲージ
	const DirectX::XMVECTORF32 ATTACKGAUGE_TRACK		= DirectX::Colors::Gray;			// 攻撃ゲージの土台
	const DirectX::XMVECTORF32 MESH_GAUGE_BACKGROUND	= { 0.0f, 0.0f, 0.0f, 0.4f };		// メッシュゲージの背景
}
