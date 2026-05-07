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
    , m_meshFloor{ std::make_unique<MeshFloor>()  }
    , m_player   { std::make_unique<Player>(0.5f) }
    , m_collisionManager{ std::make_unique<CollisionManager>() }
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
    m_player->Initialize(SimpleMath::Vector3::Up * 24.0f);
    m_meshFloor->Initialize();

    m_camera->SetCamera(SimpleMath::Vector3{ 0.0f, 18.0f, 25.0f }, SimpleMath::Vector3::Zero);

    m_player->SetCamera(m_camera.get());

    m_collisionManager->RegistCollider(m_player->GetComponent<Sphere>());
    m_collisionManager->RegistCollider(m_meshFloor->GetComponent<Mesh>());
}

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
        m_player->Initialize(SimpleMath::Vector3::Up * 50.0f);
        m_hitFaces.clear();
    }

    m_player->Update();
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

    m_camera->FollowCamera(palyerTransform->GetPosition());
}


/**
 * \brief 描画.
 * 
 */
void GameScene::Draw()
{
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

        std::vector<VertexPositionNormalColor> pos;

        pos.emplace_back(face->GetPoint()[0] + normal * 0.01f, normal, Colors::Blue);
        pos.emplace_back(face->GetPoint()[1] + normal * 0.01f, normal, Colors::Blue);
        pos.emplace_back(face->GetPoint()[2] + normal * 0.01f, normal, Colors::Blue);

        primitiveRenderer().RegisterDrawCommand({
            D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, pos
            });
    }
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

    DirectX::SimpleMath::Vector3 v1{ -10.0f, 0.0f, -10.0f };
    DirectX::SimpleMath::Vector3 v2{ 0.0f, 0.0f, 10.0f };
    DirectX::SimpleMath::Vector3 v3{ 10.0f, 0.0f, -10.0f };

    m_camera->Initialize(projMat);
}

void GameScene::SetModel()
{
}
