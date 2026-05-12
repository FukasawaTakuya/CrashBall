#pragma once
#include "pch.h"

inline DirectX::SimpleMath::Vector3 Slerp(
    const DirectX::SimpleMath::Vector3& start, 
    const DirectX::SimpleMath::Vector3& end, float t)
{
    float dot = start.Dot(end);
    dot = std::clamp(dot, -1.0f, 1.0f);
    float theta = std::acos(dot) * t;
    DirectX::SimpleMath::Vector3 relative = end - start * dot;
    relative.Normalize();
    return ((start * std::cos(theta)) + (relative * std::sin(theta)));
}