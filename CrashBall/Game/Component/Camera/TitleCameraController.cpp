#include "pch.h"
#include "TitleCameraController.h"

#include "Game/Engine/Time.h"

TitleCameraController::TitleCameraController(IGameObject* gameObject)
	: Component(gameObject)
{
	m_targetCamera = GetGameObject()->GetComponent<TargetCamera>();
}

TitleCameraController::~TitleCameraController()
{
}

void TitleCameraController::Initialize()
{
	m_targetCamera->Initialize();
}

void TitleCameraController::Update()
{
	m_targetCamera->RotateX(ROTATE_ANGLERAD * Time::GetElapsedTime());

	// ターゲットを追尾
	m_targetCamera->TargetingTransform();

}
