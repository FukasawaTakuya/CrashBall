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

using namespace DirectX;

RegisterComponent(DebugCameraController)


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
DebugCameraController::DebugCameraController(IGameObject* gameObject)
	: TargetCameraController(gameObject)
{
	m_targetTransform = std::make_unique<Transform>();
	SetTargetTransform(m_targetTransform.get());
	SetBaseOffset({ 0.0f, 10.0f, 10.0f });
}

/**
 * \brief デストラクタ
 * 
 */
DebugCameraController::~DebugCameraController()
{
}

/**
 * \brief 更新
 * 
 */
void DebugCameraController::Update(const GameContext& gameContext)
{
	// 前フレームのマウス座標との差
	SimpleMath::Vector2 deltaMousePos
		= Input::GetPrevMousePos() - Input::GetMousePos();

	// 左ボタンが押されているとき
	if (Input::GetMouseDown(MouseButton::Left))
	{
		// カメラを回転
		TargetCameraController::RotateX(-deltaMousePos.x / 1000.0f);
		TargetCameraController::RotateY( deltaMousePos.y / 1000.0f);
	}
	// 中央ボタンが押されているとき
	else if (Input::GetMouseDown(MouseButton::Middle))
	{
		// カメラ移動
		m_targetTransform->Translate(
			GetRight()				*  deltaMousePos.x / 20.0f +
			SimpleMath::Vector3::Up	* -deltaMousePos.y / 20.0f
		);
	}

	// ホイール値分カメラを前方向に移動
	m_targetTransform->Translate(
		GetForward() * Input::GetWheelValue()
	);

	// ターゲットの追尾
	TargetingTransform();
}
