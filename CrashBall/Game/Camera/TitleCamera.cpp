#include "pch.h"
#include "TitleCamera.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Camera/TargetCamera.h"

TitleCamera::TitleCamera()
{
	// コンポーネントの追加
	AddComponent<Transform>();
	AddComponent<TargetCamera>(SimpleMath::Vector3(0.0f, 4.0f, 12.0f));
	m_cameraController = AddComponent<TitleCameraController>();
}

TitleCamera::~TitleCamera()
{
}

void TitleCamera::Initialize()
{
	m_cameraController->Initialize();
}

void TitleCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update();
}

void TitleCamera::Render(const RenderContext& renderContext)
{
}

void TitleCamera::Finalize()
{
}
