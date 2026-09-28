#include "pch.h"
#include "MyMath.h"

using namespace DirectX;

DirectX::SimpleMath::Quaternion MyMath::NoneRollFromToRotation(
	const DirectX::SimpleMath::Vector3& fromDir,
	const DirectX::SimpleMath::Vector3& toDir)
{
	// XZ平面のベクトル
	SimpleMath::Vector3 xzFromVec	= XMVector3Normalize({fromDir.x, 0.0f, fromDir.z});
	SimpleMath::Vector3 xzToVec	= XMVector3Normalize({toDir.x, 0.0f, toDir.z});

	float yaw = xzFromVec.Dot(xzToVec);

	//SimpleMath::Vector3 delta = XMVector3Normalize(toDir - fromDir);
	//SimpleMath::Vector3 horizonFromVec	= fromDir - delta.Dot(fromDir) * delta;
	//SimpleMath::Vector3 horizonToVec	= toDir	  - delta.Dot(toDir)   * delta;
	//float pitch = horizonFromVec.Dot(horizonToVec);

	float pitch = asinf(toDir.y) - asinf(fromDir.y);

	return SimpleMath::Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
}

DirectX::SimpleMath::Quaternion MyMath::NoneRollLookAt(const DirectX::SimpleMath::Vector3& direction)
{
	float yaw = std::atan2f(direction.x, direction.z);

	// 水平方向の長さ
	float horizontalLen = std::sqrtf((direction.x * direction.x + direction.z * direction.z));

	float pitch = std::atan2f(direction.y, horizontalLen);

	pitch = std::clamp(
		pitch,
		-XM_PIDIV2 + 0.001f,
		XM_PIDIV2 - 0.001f
	);

	return SimpleMath::Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
}
