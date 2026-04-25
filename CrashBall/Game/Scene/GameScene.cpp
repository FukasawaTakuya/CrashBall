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
#include "Game/Renderer/PrimitveRendererManager.h"

// メンバ関数の定義 ===========================================================

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 * \param pSceneManager シーンマネージャー
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene(m_pSceneManager)
    , m_meshFloor{ std::make_unique<MeshFloor>()                               }
    , m_ball    { std::make_unique<Ball>(0.5f) }
    , m_player  { std::make_unique<Player>(0.5f)}
{
}

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
    m_player->Initialize(SimpleMath::Vector3::Up * 24.0f);
    m_meshFloor->Initialize();

    m_camera->SetCamera(SimpleMath::Vector3{ 0.0f, 18.0f, 25.0f }, SimpleMath::Vector3::Zero);

    m_player->SetCamera(m_camera.get());
}

void GameScene::Update(float elapsedTime)
{
    auto key = Keyboard::Get().GetState();
    auto mouse = Mouse::Get().GetState();

    Transform* ballTransform = m_player->GetComponent<Transform>();
    RigitBody* ballRigitbody = m_player->GetComponent<RigitBody>();

    if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::R)) {
        m_ball->Initialize(SimpleMath::Vector3::Up * 24.0f);
        m_player->Initialize(SimpleMath::Vector3::Up * 24.0f);
        m_hitFaces.clear();
    }

    ballRigitbody->ResetAccel();

    if (m_ball->GetIsGround())
    {
        if (key.D) {
            ballRigitbody->Accel(m_camera->GetRight() * 35.0f);
        }
        if (key.A) {
            ballRigitbody->Accel(-m_camera->GetRight() * 35.0f);
        }
        if (key.W) {
            ballRigitbody->Accel(m_camera->GetForward() * 35.0f);
        }
        if (key.S) {
            ballRigitbody->Accel(-m_camera->GetForward() * 35.0f);
        }
        if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::Space))
        {
            ballRigitbody->AddVelocity(m_camera->GetForward() * 35.8f);
        }
        if (ballRigitbody->GetVelocity().LengthSquared() > 0.0f) {
            m_ball->Rotate();
        }
    }

    m_ball->Move();

    m_player->Update();

     // メッシュと球の衝突判定
    if (Collision::IsCollision(m_ball->GetComponent<Sphere>(), m_meshFloor->GetMesh()))
    {
        m_ball->SetIsGround(true);

        // 衝突の解決
        Collision::ResolveCollision(m_ball.get(), m_meshFloor->GetMesh());
        // 摩擦の適用
        ballRigitbody->ApplyFriction();
    }
    else m_ball->SetIsGround(false);

    if (Collision::IsCollision(m_player->GetComponent<Sphere>(), m_meshFloor->GetMesh()))
    {
        m_player->SetIsGround(true);

        // 衝突の解決
        Collision::ResolveCollision(m_player.get(), m_meshFloor->GetMesh());
        // 摩擦の適用
        ballRigitbody->ApplyFriction();
    }
    else m_player->SetIsGround(false);



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

    m_camera->FollowCamera(ballTransform->GetPosition());
}


/**
 * \brief 描画.
 * 
 */
void GameScene::Draw()
{
    //m_ball->Draw();
    m_meshFloor->Draw();
    m_player->Draw();

    auto primitiveRenderer = PrimitiveRendererManager::Instance;

    auto& hitFace = m_meshFloor->GetMesh()->GetHitFace();

    if (!hitFace.empty()) {
        for (auto& face : hitFace)
        {
            bool isPush = true;
            for (auto& hitFaces : m_hitFaces)
            {
                if (face == hitFaces)
                {
                    isPush = false;
                    break;
                }
            }
            if(isPush) m_hitFaces.emplace_back(face);
        }
    }

    for (auto& face : m_hitFaces)
    {

        SimpleMath::Vector3 normal = face->GetPlane()->GetNormal();
        assert(normal.Length() > 0.0f);

        std::vector<VertexPositionNormalColor> pos;

        pos.emplace_back(face->GetPoint()[0] + normal * 0.01f, normal,  Colors::White);
        pos.emplace_back(face->GetPoint()[1] + normal * 0.01f, normal,  Colors::White);
        pos.emplace_back(face->GetPoint()[2] + normal * 0.01f, normal,  Colors::White);

        primitiveRenderer().RegisterDrawCommand({
            D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, pos
            });
    }
}


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

    m_ball->SetModel(modelManager->GetModel("ball")); 
    m_player->SetModel(modelManager->GetModel("ball"));

    m_meshFloor->SetModel(modelManager->GetModel("Stage"));

    DirectX::SimpleMath::Vector3 v1{ -10.0f, 0.0f, -10.0f };
    DirectX::SimpleMath::Vector3 v2{ 0.0f, 0.0f, 10.0f };
    DirectX::SimpleMath::Vector3 v3{ 10.0f, 0.0f, -10.0f };

    m_camera->Initialize(projMat);
}

void GameScene::SetModel()
{
}
