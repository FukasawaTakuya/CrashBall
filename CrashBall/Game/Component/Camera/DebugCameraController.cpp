/*****************************************************************//**
 * \file   DebugCameraController.cpp
 * \brief  デバッグ用カメラ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "DebugCameraController.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(DebugCameraController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
DebugCameraController::DebugCameraController(IGameObject* gameObject)
	: Component(gameObject)
{
	m_camera	= GetGameObject()->GetComponent<Camera>();
	m_transform = GetGameObject()->GetComponent<Transform>();
}


/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void DebugCameraController::Update(const GameContext& gameContext)
{
	// 前フレームのマウス座標との差
	SimpleMath::Vector2 deltaMousePos
		= Input::GetPrevMousePos() - Input::GetMousePos();
	// 左ボタンが押されているとき
	if (Input::GetMouseDown(MouseButton::Left))
	{
		m_transform->Rotate(
			SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::Down, -deltaMousePos.x / 1000.0f));
		m_transform->Rotate(
			SimpleMath::Quaternion::CreateFromAxisAngle(m_camera->GetHorizontalRight(), deltaMousePos.y / 1000.0f));
	}
	// 中央ボタンが押されているとき
	else if (Input::GetMouseDown(MouseButton::Middle))
	{
		// カメラ移動
		m_transform->Translate(
			m_camera->GetHorizontalRight()	*  deltaMousePos.x / 20.0f +
			SimpleMath::Vector3::Up	* -deltaMousePos.y / 20.0f
		);
	}

	m_camera->Update(gameContext);
}
