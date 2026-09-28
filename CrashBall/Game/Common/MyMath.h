#pragma once

namespace MyMath
{
	DirectX::SimpleMath::Quaternion NoneRollFromToRotation(
		const DirectX::SimpleMath::Vector3& fromDir,
		const DirectX::SimpleMath::Vector3& toDir);

	DirectX::SimpleMath::Quaternion NoneRollLookAt(const DirectX::SimpleMath::Vector3& direction);
}
