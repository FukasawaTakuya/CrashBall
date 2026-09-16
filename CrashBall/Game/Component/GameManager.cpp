#include "pch.h"
#include "GameManager.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/SceneManegement.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(GameManager);

GameManager::GameManager(IGameObject* gameObject)
	: Component(gameObject)
{
}


void GameManager::Start(const GameContext& gameContext)
{
	gameContext.soundManager->RegisterPlayBgmCommand("game");
}

void GameManager::Update(const GameContext& gameContext)
{
	if (Input::GetGamePadTracker()->start == GamePad::ButtonStateTracker::ButtonState::PRESSED)
	{
		SceneMamegement::RequestChangeScene("TitleScene");
	}

	if (m_pEnemyController->GetHp() <= 0.0f)
	{
		Time::GeratoTimeScale(-Time::GetUnscaleElapsedTime());

		if (Time::GetTimeScale() == 0.0f)
		{
			SceneMamegement::RequestChangeScene("TitleScene");
		}
	}

	if (m_pGameTimer->GetTimer() <= 0.0f)
	{
		SceneMamegement::RequestChangeScene("TitleScene");
	}
}
