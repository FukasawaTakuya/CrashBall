#include "pch.h"
#include "TitleManager.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/SceneManegement.h"

using namespace DirectX;

RegisterComponent(TitleManager);

TitleManager::TitleManager(IGameObject* gameObject)
	: Component(gameObject)
{
}


void TitleManager::Start(const GameContext& gameContext)
{
	gameContext.soundManager->RegisterPlayBgmCommand("title");
}

void TitleManager::Update(const GameContext& gameContext)
{
	if (Input::GetGamePadTracker()->a == GamePad::ButtonStateTracker::ButtonState::PRESSED)
	{
		SceneMamegement::RequestChangeScene("GameScene");
	}
}
