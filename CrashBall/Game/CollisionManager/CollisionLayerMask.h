/*****************************************************************//**
 * \file   CollisionLayerMask.h
 * \brief  衝突判定のレイヤーとマスクに関するヘッダーファイル
 * 
 * \author it252184
 * \date   May 2026
 *********************************************************************/
#pragma once
#include "pch.h"

namespace {
	// 衝突判定のレイヤー
	enum class ColliderLayer : uint32_t
	{
		None = 0,
		Default = 1 << 32 - 1,
		Ball = 1 << 0,
		Ground = 1 << 1,
	};

	// 衝突判定のマスク
	enum class ColliderMask : uint32_t
	{
		None = 0,
		Default = 1 << 32 - 1,
		Ball = static_cast<uint32_t>(ColliderLayer::Ball) |
		static_cast<uint32_t>(ColliderLayer::Ground),
		Ground = static_cast<uint32_t>(ColliderLayer::Ball),
	};
}


// レイヤーマスク
struct CollisionLayerMask
{
	ColliderLayer layer;
	ColliderMask mask;
};

// レイヤーマスク
namespace LayerMask {
	constexpr CollisionLayerMask None	 { ColliderLayer::None, ColliderMask::None };
	constexpr CollisionLayerMask Default { ColliderLayer::Default, ColliderMask::Default };
	constexpr CollisionLayerMask Ball	 { ColliderLayer::Ball, ColliderMask::Ball };
	constexpr CollisionLayerMask Ground  { ColliderLayer::Ground, ColliderMask::Ground };
}



// OR演算子のオーバーロード
inline uint32_t operator|(ColliderLayer layer, ColliderMask mask)
{
	return static_cast<uint32_t>(
		static_cast<uint32_t>(layer) | static_cast<uint32_t>(mask)
		);
}
inline uint32_t operator|(ColliderMask mask, ColliderMask layer)
{
	return layer | mask;
}

// AND演算子のオーバーロード
inline uint32_t operator&(ColliderLayer layer, ColliderMask mask)
{
	return static_cast<uint32_t>(
		static_cast<uint32_t>(layer) & static_cast<uint32_t>(mask)
		);
}
inline uint32_t operator&(ColliderMask mask, ColliderMask layer)
{
	return layer & mask;
}
