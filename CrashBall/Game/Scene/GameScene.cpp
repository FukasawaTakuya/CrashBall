/*****************************************************************//**
 * \file   GameScene.cpp
 * \brief  ゲームシーンに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "GameScene.h"
#include "Game/CollisionManager/Collision.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/Renderer/PrimitiveRendererManager.h"
#include "Game/ServiceLocator/InputService.h"

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 * \param pSceneManager シーンマネージャー
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene(pSceneManager)
    , m_Stage       (std::make_unique<Stage>())
    , m_player          (std::make_unique<Player>(0.5f))
    , m_collisionManager(std::make_unique<CollisionManager>())
	, m_ball            (std::make_unique<Ball>(0.5f))
	, m_enemy           (std::make_unique<Enemy>(0.5f))
{
}

/**
 * @brief デストラクタ
 * 
 */
GameScene::~GameScene()
{
}

/**
 * @brief 初期化
 * 
 * \param projMat 射影行列
 */
void GameScene::Initialize()
{
    m_player->SetPosition(SimpleMath::Vector3::Up * 24.0f);
    m_player->SetEnemyTransform(m_enemy->GetComponent<Transform>());
    m_player->SetCamera(m_camera.get());

	m_ball->SetPosition(SimpleMath::Vector3::Up * 24.0f);

	m_enemy->SetPosition(SimpleMath::Vector3{ 0.0f, 10.0f, 10.0f });
	m_enemy->SetFloor(m_Stage.get());

    m_camera->SetCamera(SimpleMath::Vector3{ 0.0f, 18.0f, 25.0f }, SimpleMath::Vector3::Zero);

    m_collisionManager->RegistCollider(m_player->GetComponent<Sphere>());
    m_collisionManager->RegistCollider(m_Stage->GetComponent<Mesh>());
	m_collisionManager->RegistCollider(m_ball->GetComponent<Sphere>());
	m_collisionManager->RegistCollider(m_enemy->GetComponent<Sphere>());
}


bool playerFollow = true;
/**
 * @brief 更新.
 * 
 * \param elapsedTime 経過時間
 */
void GameScene::Update(const GameContext& gameContext)
{
    auto key = Keyboard::Get().GetState();
    auto input = InputService::Instance().GetInput();
    float elapsedTime = gameContext.m_pTimeManager->GetElapsedTime();

    if (input->GetKeyTrigger(Keyboard::R)) {
        m_player->SetPosition(SimpleMath::Vector3::Up * 24.0f);
        m_ball->SetPosition(SimpleMath::Vector3::Up * 24.0f);
        m_enemy->SetPosition(SimpleMath::Vector3{ 0.0f, 10.0f, 10.0f });
    }
    if (input->GetKeyTrigger(Keyboard::F)) {
        playerFollow = !playerFollow;
    }

    m_player->Update(gameContext);
    m_ball->Move();
    m_ball->Rotate();
	m_enemy->Update(gameContext);

    m_collisionManager->Update();

    // TODO:カメラ内部に書く
    if (input->GetKeyDown(Keyboard::Right)) {
        m_camera->RotateX(XMConvertToRadians(45.0f * elapsedTime));
    }
    if (input->GetKeyDown(Keyboard::Left)) {
        m_camera->RotateX(XMConvertToRadians(-45.0f * elapsedTime));
    }
    if (input->GetKeyDown(Keyboard::Up)) {
        m_camera->RotateY(XMConvertToRadians(45.0f * elapsedTime));
    }
    if (input->GetKeyDown(Keyboard::Down)) {
        m_camera->RotateY(XMConvertToRadians(-45.0f * elapsedTime));
    }

    auto mouse = Mouse::Get().GetState();
    Mouse::Get().ResetScrollWheelValue();
    m_camera->Zoom(-mouse.scrollWheelValue / 500.0f);

    if (playerFollow) {
        m_camera->FollowCamera(m_player->GetComponent<Transform>()->GetPosition());
    }
    else {
		m_camera->FollowCamera(m_enemy->GetComponent<Transform>()->GetPosition());
    }
}


/**
 * \brief 描画.
 * 
 */
void GameScene::Draw(const GameContext& gameContext)
{
    m_Stage->Render(gameContext);
    m_player->Render(gameContext);
	m_ball->Render(gameContext);
	m_enemy->Render(gameContext);
}


/**
 * @brief 終了処理.
 * 
 */
void GameScene::Finalize()
{
}

/**
 * \brief リソースの作成.
 * 
 * \param projMat 射影行列
 */
void GameScene::CreateDeviceResources(const GameContext& gameContext)
{
    auto modelManager = gameContext.m_pModelManager;

    m_player->SetModel(modelManager->GetModel("ball"));

    m_Stage->SetModel(modelManager->GetModel("Stage"));

	m_ball->SetModel(modelManager->GetModel("ball"));

	m_enemy->SetModel(modelManager->GetModel("ball"));

    DirectX::SimpleMath::Vector3 v1{ -10.0f, 0.0f, -10.0f };
    DirectX::SimpleMath::Vector3 v2{ 0.0f, 0.0f, 10.0f };
    DirectX::SimpleMath::Vector3 v3{ 10.0f, 0.0f, -10.0f };
}

void GameScene::CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj)
{
    m_camera->Initialize(proj);
}

void GameScene::SetModel()
{
}
