#include "pch.h"
#include "GameCameraController.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"

GameCameraController::GameCameraController(IGameObject* gameObejct)
	: Component(gameObejct)
{
	m_targetCamera = GetGameObject()->GetComponent<TargetCamera>();
}

GameCameraController::~GameCameraController()
{
}

void GameCameraController::Initialize()
{
	m_targetCamera->Initialize();
}

void GameCameraController::Update()
{
	float elapsedTime = Time::GetElapsedTime();

	// 入力に応じて回転
	if (Input::GetKeyDown(Keyboard::Up)) {
		m_targetCamera->RotateY( ROTATE_ANGELRAD * elapsedTime);
	}
	else if (Input::GetKeyDown(Keyboard::Down)) {
		m_targetCamera->RotateY(-ROTATE_ANGELRAD * elapsedTime);
	}
	if (Input::GetKeyDown(Keyboard::Right)) {
		m_targetCamera->RotateX( ROTATE_ANGELRAD * elapsedTime);

	}
	else if (Input::GetKeyDown(Keyboard::Left)) {
		m_targetCamera->RotateX(-ROTATE_ANGELRAD * elapsedTime);
	}

	m_targetCamera->TargetingTransform();
}
