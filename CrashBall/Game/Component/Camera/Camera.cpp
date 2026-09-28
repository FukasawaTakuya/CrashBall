#include "pch.h"
#include "Camera.h"
#include "Game/Common/MyMath.h"

using namespace DirectX;

RegisterComponent(Camera);

/**
 * \brief 
 * 
 */
void Camera::Awake()
{
	m_transform = GetGameObject()->GetComponent<Transform>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Camera::Start(const GameContext& gameContext)
{
	m_forward	= SimpleMath::Vector3::Forward;
	m_right		= SimpleMath::Vector3::Right;

	UpdateView();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Camera::Update(const GameContext& gameContext)
{
	if (m_transform->GetIsDirty())
	{
		UpdateView();
	}
}

/**
 * \brief 
 * 
 * \param target
 */
void Camera::LookAt(const DirectX::SimpleMath::Vector3& target)
{
	SimpleMath::Vector3 dire = XMVector3Normalize(target - m_transform->GetWorldPosition());

	//SimpleMath::Quaternion rotate = SimpleMath::Quaternion::FromToRotation(m_forward, dire);
	SimpleMath::Quaternion rotation = MyMath::NoneRollLookAt(dire);

	SimpleMath::Quaternion invers = XMQuaternionInverse(m_transform->GetWorldRotate());
	SimpleMath::Quaternion delta = invers * rotation;

	m_transform->Rotate(delta);
	m_transform->Rotate(MyMath::NoneRollFromToRotation(m_forward, dire));

	m_forward = dire;
}

/**
 * \brief ビュー行列の更新
 * 
 */
void Camera::UpdateView()
{
	m_forward = XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetWorldRotate());

	SimpleMath::Vector3 up = XMVector3Rotate(SimpleMath::Vector3::Up, m_transform->GetWorldRotate());

	//float dot = up.Dot(m_forward);
	//if (std::fabs(dot >= 0.99f))
	//{
	//	if (dot < 0.0f)
	//	{
	//		up = SimpleMath::Vector3::Backward;
	//	}
	//	else
	//	{
	//		up = SimpleMath::Vector3::Forward;
	//	}
	//}

	m_right	= XMVector3Cross(m_forward, up);

	//up = XMVector3Cross(m_right, m_forward);

	m_view =
		SimpleMath::Matrix::CreateLookAt(
			m_transform->GetWorldPosition(), 
			m_transform->GetWorldPosition() + m_forward, 
			up);
}
