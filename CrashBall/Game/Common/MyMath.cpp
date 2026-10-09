#include "pch.h"
#include "MyMath.h"

using namespace DirectX;

DirectX::SimpleMath::Quaternion MyMath::NoneRollLookAt(const DirectX::SimpleMath::Vector3& direction)
{
	float yaw = std::atan2f(-direction.x, -direction.z);

	// 水平方向の長さ
	float horizontalLen = std::sqrtf((direction.x * direction.x + direction.z * direction.z));

	float pitch = std::atan2f(direction.y, horizontalLen);

	return SimpleMath::Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
}
