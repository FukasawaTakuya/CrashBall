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
//#include <Game/CommonResources.h>
//#include <Game/Collision.h>
//#include <Game/ResourceManager/ResourceManager.h>
//#include <Game/PrimitveManager.h>
//#include <Game/InputSystem.h>

// メンバ関数の定義 ===========================================================

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 * \param pSceneManager シーンマネージャー
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene(m_pSceneManager)
    //, m_floor   { std::make_unique<Floor>()                                    }
    //, m_meshFloor{ std::make_unique<MeshFloor>()                               }
    //, m_ball    { std::make_unique<Ball>(SimpleMath::Vector3::Up * 24.0f, 0.5f) }
    //, m_camera  { std::make_unique<Camera>() }                              
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
    //m_ball->Initialize();
    //m_floor->Initialize();
    //m_meshFloor->Initialize();

    //m_camera->SetCamera(SimpleMath::Vector3{ 0.0f, 18.0f, 25.0f }, SimpleMath::Vector3::Zero);
}

bool isDraw = true;

void GameScene::Update(float elapsedTime)
{
    auto key = Keyboard::Get().GetState();

    // マウス操作---------------------------------------------------------------------------

    auto mouse = Mouse::Get().GetState();

   // SimpleMath::Vector2 mousePos
   //     = InputSystem::Instance().GetMousePos();

   // SimpleMath::Matrix rotateZ = SimpleMath::Matrix::Identity;
   // SimpleMath::Matrix rotateX = SimpleMath::Matrix::Identity;

   // auto mouseDir = mousePos - m_mousePrevPos;

   // if (mouseDir.x < 0.0f) {
   //     rotateZ
   //         = SimpleMath::Matrix::CreateRotationZ(XMConvertToRadians(0.4f));
   // }
   // else if (mouseDir.x > 0.0f) {
   //     rotateZ
   //         = SimpleMath::Matrix::CreateRotationZ(-XMConvertToRadians(0.4f));
   // }

   // if (mouseDir.y > 0.0f) {
   //     rotateX
   //         = SimpleMath::Matrix::CreateRotationX(XMConvertToRadians(0.4f));
   // }
   // else if (mouseDir.y < 0.0f) {
   //     rotateX
   //         = SimpleMath::Matrix::CreateRotationX(-XMConvertToRadians(0.4f));
   // }

   // m_mousePrevPos = mousePos;

   // // 平面の回転-----------------------------------------------------------------

   // auto floorRotate = rotateZ * rotateX;

   //// m_meshFloor->Rotate(floorRotate);

   // if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::Enter))
   //     isDraw = !isDraw;

   // if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::R)) {
   //     m_ball->SetPos(SimpleMath::Vector3::Up * 4.0f);
   //     m_ball->SetVelocity(SimpleMath::Vector3::Zero);
   //     m_ball->Initialize();
   // }

   // m_ball->ResetAccel();

   // if (m_ball->GetIsGround())
   // {
   //     if (key.D) {
   //         m_ball->Accel(m_camera->GetRight() * 35.0f);
   //     }
   //     if (key.A) {
   //         m_ball->Accel(-m_camera->GetRight() * 35.0f);
   //     }
   //     if (key.W) {
   //         m_ball->Accel(m_camera->GetForward() * 35.0f);
   //     }
   //     if (key.S) {
   //         m_ball->Accel(-m_camera->GetForward() * 35.0f);
   //     }
   //     if (InputSystem::Instance().GetKeyboardTracker()->IsKeyPressed(Keyboard::Space))
   //     {
   //         m_ball->AddVelocity(SimpleMath::Vector3::Up * 14.8f);
   //     }
   // }

   // m_ball->Move(elapsedTime);


   // // メッシュと球の衝突判定
   // if (m_meshFloor->GetMesh()->IsCollision(m_ball.get()))
   // {
   //     m_ball->SetIsGround(true);

   //     // 衝突の解決
   //     m_meshFloor->GetMesh()->ResolveCol(m_ball.get());
   //     // 摩擦の適用
   //     m_ball->ApplyFriction();

   //     if (m_ball->GetVelocity().LengthSquared() > 0.0f) {
   //         m_ball->Rotate(elapsedTime);
   //     }
   // }
   // else m_ball->SetIsGround(false);


   // if (key.Right) {
   //     m_camera->RotateX(XMConvertToRadians(45.0f * elapsedTime));
   // }
   // if (key.Left) {
   //     m_camera->RotateX(XMConvertToRadians(-45.0f * elapsedTime));
   // }
   // if (key.Up) {
   //     m_camera->RotateY(XMConvertToRadians(45.0f * elapsedTime));
   // }
   // if (key.Down) {
   //     m_camera->RotateY(XMConvertToRadians(-45.0f * elapsedTime));
   // }

   // Mouse::Get().ResetScrollWheelValue();
   // m_camera->Zoom(-mouse.scrollWheelValue / 500.0f);

   // m_camera->FollowCamera(m_ball->GetPos());
}

void GameScene::Draw()
{


    //m_ball->Draw(m_camera->GetProjMat(), m_camera->GetViewMat());
    //m_meshFloor->Draw(m_camera->GetProjMat(), m_camera->GetViewMat());

    // 

    //auto primitiveManager = PrimitiveManager::Instance;
    //primitiveManager().ApplyEffect(m_camera.get());

    //auto primitiveBatch = primitiveManager().GetPrimitiveBatch();
    //primitiveBatch->Begin();


    //if (isDraw) {
    //    for (auto& face : m_meshFloor.get()->GetMesh()->GetFace())
    //    {
    //        VertexPositionColor pos{ face->GetCenter(), Colors::Green };
    //        VertexPositionColor vec{ face->GetCenter() + face->GetPlane()->GetNormal(), Colors::Red };
    //        //primitiveBatch->DrawLine(pos, vec);

    //        VertexPositionColor pos1{ face->GetPoint()[0], Colors::Red };
    //        VertexPositionColor pos2{ face->GetPoint()[1], Colors::Red };
    //        VertexPositionColor pos3{ face->GetPoint()[2], Colors::Red };
    //        primitiveBatch->DrawLine(pos1, pos2);
    //        primitiveBatch->DrawLine(pos1, pos3);
    //        primitiveBatch->DrawLine(pos3, pos2);
    //    }

    //    auto face = m_meshFloor->GetMesh()->GetHitFace();
    //    if (face != nullptr) {
    //        VertexPositionColor pos1{ face->GetPoint()[0], Colors::Blue };
    //        VertexPositionColor pos2{ face->GetPoint()[1], Colors::Blue };
    //        VertexPositionColor pos3{ face->GetPoint()[2], Colors::Blue };
    //        //primitiveBatch->DrawTriangle(pos1, pos2, pos3);
    //    }

    //}
    //primitiveBatch->End();

}

void GameScene::Finalize()
{
}

void GameScene::CreateResources(DirectX::SimpleMath::Matrix projMat)
{
    //auto modelManager = ResourceManager::Instance().GetModelManager();

    //m_floor->SetModel(modelManager->GetModel("floor"));

    //m_ball->SetModel(modelManager->GetModel("ball")); 

    //m_meshFloor->SetModel(modelManager->GetModel("Stage"));

    //DirectX::SimpleMath::Vector3 v1{ -10.0f, 0.0f, -10.0f };
    //DirectX::SimpleMath::Vector3 v2{ 0.0f, 0.0f, 10.0f };
    //DirectX::SimpleMath::Vector3 v3{ 10.0f, 0.0f, -10.0f };

    //triangle.SetTriangle(v1, v3, v2);

    //m_camera->Initialize(projMat);

}

void GameScene::SetModel()
{
}
