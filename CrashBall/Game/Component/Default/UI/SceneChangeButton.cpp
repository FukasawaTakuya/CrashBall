#include "pch.h"
#include "SceneChangeButton.h"

#include "Game/Engine/SceneManegement.h"

RegisterComponent(SceneChangeButton)

SceneChangeButton::SceneChangeButton(IGameObject* gameObject)
	: ButtonController(gameObject)
{
	m_baseTypeid = typeid(ButtonController);
}


SceneChangeButton::~SceneChangeButton()
{
}

void SceneChangeButton::Awake()
{
	ButtonController::Awake();

	SetOnPushCommand([&]()
		{
			SceneMamegement::RequestChangeScene(m_nextSceneName);
		});
}

void SceneChangeButton::Update(const GameContext& gameContext)
{
	ButtonController::Update(gameContext);
}
