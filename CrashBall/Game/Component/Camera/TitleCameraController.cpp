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
	: Component(gameObject)
{
	m_targetCamera = GetGameObject()->GetComponent<TargetCamera>();
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
	m_targetCamera->Initialize();
}

/**
 * \brief 更新
 * 
 */
void TitleCameraController::Update()
{
	m_targetCamera->RotateX(ROTATE_ANGLERAD * Time::GetElapsedTime());

	// ターゲットを追尾
	m_targetCamera->TargetingTransform();

}
