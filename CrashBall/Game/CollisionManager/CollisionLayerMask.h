#pragma once
#include "pch.h"

enum class ColliderLayer : uint32_t
{
	None = 0,
	Ball = 1 << 0,
	Ground = 1 << 1,
};

enum class ColliderMask : uint32_t
{
	Default = 32,
	Ball	= static_cast<uint32_t>(ColliderLayer::Ball) | 
			  static_cast<uint32_t>(ColliderLayer::Ground),
	Ground	= static_cast<uint32_t>(ColliderLayer::Ball),
};

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
