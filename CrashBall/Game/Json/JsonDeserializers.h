#pragma once

#include "nlohmann/json.hpp"
#include "Game/Geometory/Triangle.h"

using namespace nlohmann;

namespace DirectX::SimpleMath
{
	void from_json(const json& j, Vector3& vec3);
}

// Jsonから三角形への変換
void from_json(const json& j, Triangle& triangle);