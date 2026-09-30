#include "pch.h"
#include "Camera.h"
#include "Game/Common/MyMath.h"

using namespace DirectX;

RegisterComponent(Camera);

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
Camera::Camera(IGameObject* gameObject)
	: Component(gameObject)
{
}


/**
 * \brief アタッチ時の処理
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
 * \brief ターゲットの方に向ける
 * 
 * \param target
 */
void Camera::LookAt(const DirectX::SimpleMath::Vector3& target)
{
	SimpleMath::Vector3 dire = XMVector3Normalize(target - m_transform->GetWorldPosition());
	SimpleMath::Quaternion rotation = MyMath::NoneRollLookAt(dire);
	m_transform->SetRotate(rotation);

	m_forward = dire;
}

/**
 * \brief ビュー行列の更新
 * 
 */
void Camera::UpdateView()
{
	m_forward	= XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetWorldRotate());
	m_up		= XMVector3Rotate(SimpleMath::Vector3::Up,		m_transform->GetWorldRotate());
	m_right		= XMVector3Rotate(SimpleMath::Vector3::Right,	m_transform->GetWorldRotate());

	m_view =
		SimpleMath::Matrix::CreateLookAt(
			m_transform->GetWorldPosition(), 
			m_transform->GetWorldPosition() + m_forward, 
			m_up);
}
