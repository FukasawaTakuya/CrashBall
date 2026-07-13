/*****************************************************************//**
 * \file   TitleCameraController.h
 * \brief  タイトルカメラ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "TitleCameraController.h"

#include "Game/Engine/Time.h"


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
TitleCameraController::TitleCameraController(IGameObject* gameObject)
	: TargetCameraController(gameObject)
{
	m_targetCamera = GetGameObject()->GetComponent<TargetCameraController>();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
TitleCameraController::TitleCameraController(
	IGameObject* gameObject, 
	const TitleCameraController& other)
	: TargetCameraController(gameObject, other.m_baseOffset)
	, m_rotateAngeleRad(other.m_rotateAngeleRad)
{
	m_targetCamera = GetGameObject()->GetComponent<TargetCameraController>();
}

/**
 * \brief デストラクタ
 * 
 */
TitleCameraController::~TitleCameraController()
{
}

/**
 * \brief 初期化
 * 
 */
void TitleCameraController::Initialize()
{
	TargetCameraController::Initialize();
}

/**
 * \brief 更新
 * 
 */
void TitleCameraController::Update()
{
	RotateX(XMConvertToRadians(m_rotateAngeleRad) * Time::GetElapsedTime());

	TargetingTransform();
}
