/*****************************************************************//**
 * \file   GameScene.cpp
 * \brief  ゲームシーンに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameScene.h"
#include "Game/Common/InputSystem.h"
#include "Game/CollisionManager/Collision.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/Renderer/PrimitiveRendererManager.h"

// メンバ関数の定義 ===========================================================

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 * \param pSceneManager シーンマネージャー
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene(pSceneManager)
    , m_meshFloor       (std::make_unique<MeshFloor>())
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
    m_player->Initialize(SimpleMath::Vector3::Up * 24.0f, m_enemy->GetComponent<Transform>());
    m_meshFloor->Initialize();
	m_ball->Initialize(SimpleMath::Vector3::Up * 24.0f);
	m_enemy->Inisitialize(SimpleMath::Vector3{ 0.0f, 10.0f, 10.0f });
	m_enemy->SetFloor(m_meshFloor.get());

    m_camera->SetCamera(SimpleMath::Vector3{ 0.0f, 18.0f, 25.0f }, SimpleMath::Vector3::Zero);

    m_player->SetCamera(m_camera.get());

    m_collisionManager->RegistCollider(m_player->GetComponent<Sphere>());
    m_collisionManager->RegistCollider(m_meshFloor->GetComponent<Mesh>());
	m_collisionManager->RegistCollider(m_ball->GetComponent<Sphere>());
	m_collisionManager->RegistCollider(m_enemy->GetComponent<Sphere>());
}


bool playerFollow = true;
/**
 * @brief 更新.
 * 
 * \param elapsedTime 経過時間
 */
void GameScene::Update(float elapsedTime)
{
    auto key = Keyboard::Get().GetState();
    auto mouse = Mouse::Get().GetState();

    Transform* palyerTransform = m_player->GetComponent<Transform>();

    if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::R)) {
        m_player->Initialize(SimpleMath::Vector3::Up * 50.0f, m_enemy->GetComponent<Transform>());
		m_ball->Initialize(SimpleMath::Vector3::Up * 50.0f);
		m_enemy->Inisitialize(SimpleMath::Vector3{ 0.0f, 10.0f, 1.0f });
        m_hitFaces.clear();
    }
    if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::F)) {
        playerFollow = !playerFollow;
    }

    m_player->Update();
    m_ball->Move();
    m_ball->Rotate();
	m_enemy->Update();

    m_collisionManager->Update();

    if (key.Right) {
        m_camera->RotateX(XMConvertToRadians(45.0f * elapsedTime));
    }
    if (key.Left) {
        m_camera->RotateX(XMConvertToRadians(-45.0f * elapsedTime));
    }
    if (key.Up) {
        m_camera->RotateY(XMConvertToRadians(45.0f * elapsedTime));
    }
    if (key.Down) {
        m_camera->RotateY(XMConvertToRadians(-45.0f * elapsedTime));
    }

    Mouse::Get().ResetScrollWheelValue();
    m_camera->Zoom(-mouse.scrollWheelValue / 500.0f);

    if (playerFollow) {
        m_camera->FollowCamera(palyerTransform->GetPosition());
    }
    else {
		m_camera->FollowCamera(m_enemy->GetComponent<Transform>()->GetPosition());
    }
}


/**
 * \brief 描画.
 * 
 */
void GameScene::Draw()
{
    m_meshFloor->Draw();
    m_player->Draw();
	m_ball->Draw();
	m_enemy->Draw();
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
void GameScene::CreateResources(DirectX::SimpleMath::Matrix projMat)
{
    auto modelManager = ResourceManager::Instance().GetModelManager();

    m_player->SetModel(modelManager->GetModel("ball"));

    m_meshFloor->SetModel(modelManager->GetModel("Stage"));

	m_ball->SetModel(modelManager->GetModel("ball"));

	m_enemy->SetModel(modelManager->GetModel("ball"));

    DirectX::SimpleMath::Vector3 v1{ -10.0f, 0.0f, -10.0f };
    DirectX::SimpleMath::Vector3 v2{ 0.0f, 0.0f, 10.0f };
    DirectX::SimpleMath::Vector3 v3{ 10.0f, 0.0f, -10.0f };

    m_camera->Initialize(projMat);
}

void GameScene::SetModel()
{
}
