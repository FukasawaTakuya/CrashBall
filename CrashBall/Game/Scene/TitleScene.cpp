#include "pch.h"

#include "TitleScene.h"
#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"

using namespace DirectX;

TitleScene::TitleScene(ISceneController* pSceneController)
	: Scene(pSceneController)
	, m_camera(std::make_unique<TitleCamera>())
	, m_player(std::make_unique<Player>())
	, m_stage(std::make_unique<Stage>())
	, m_titleSprite(std::make_unique<Object2D>())
{

	m_camera->GetComponent<TargetCamera>()->SetTargetTransform(
		m_player->GetComponent<Transform>()
	);

	m_player->GetComponent<Transform>()->SetPosition({ 0.0f, 10.25f, 0.0f });

	m_titleSprite->GetComponent<RectTransform>()->SetPosition(
		TITLE_INIT_POS
	);


	m_titleSpriteTransform = m_titleSprite->GetComponent<RectTransform>();
	m_titleSpriteTransform->SetScale(1.3f);

}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	m_camera->Initialize();
	m_stage->Initialize();
}

void TitleScene::Update(const GameContext& gameContext)
{
	if (Input::GetKeyDown(Keyboard::Space))
	{
		m_pSceneController->RequestChangeScene(SceneID::Game);
	}

	if (m_radian >= 360.0f)
	{
		m_radian = 0.0f;
	}

	m_radian += Time::GetElapsedTime();

	m_titleSpriteTransform->SetPosition(
		TITLE_INIT_POS + SimpleMath::Vector2(0.0f, std::sin(m_radian) * 20.0f)
	);

	m_camera->Update(gameContext);


}

void TitleScene::Draw(const RenderContext& renderContext)
{
	m_player->Render(renderContext);
	m_stage->Render(renderContext);
	m_titleSprite->Render(renderContext);
}

void TitleScene::Finalize()
{
}

void TitleScene::CreateDeviceResources(const ResourceContext& resourceContext)
{
	ModelRenderer* playerRenderer = m_player->GetComponent<ModelRenderer>();

	playerRenderer->SetModel(resourceContext.modelManager->GetModel("player"));
	playerRenderer->SetDiffuseColor(GameColor::PLAYER);

	m_titleSprite->GetComponent<SpriteRenderer>()->SetSprite(
		resourceContext.spriteManager->GetSprite("Title")
	);

}

void TitleScene::CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj)
{
}
