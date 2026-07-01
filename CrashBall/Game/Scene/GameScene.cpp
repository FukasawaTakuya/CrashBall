/*****************************************************************//**
 * \file   GameScene.cpp
 * \brief  ゲームシーンクラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "GameScene.h"
#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"


using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param pSceneManager シーンマネージャー
 */
GameScene::GameScene(
    ISceneController* pSceneManager,
    IJsonDataManager* jsonDataManager)
	: Scene(pSceneManager, jsonDataManager)
    , m_stage           (std::make_unique<Stage>(jsonDataManager->GetJsonData("stage")))
    , m_player          (std::make_unique<Player>(jsonDataManager->GetJsonData("player")))
	, m_enemy           (std::make_unique<Enemy>(jsonDataManager->GetJsonData("enemy")))
    , m_gamePanel       (std::make_unique<GamePanel>(jsonDataManager->GetJsonData("gamePanel")))
    , m_collisionManager(std::make_unique<CollisionManager>())
    , m_camera          (std::make_unique<GameCamera>(jsonDataManager->GetJsonData("gameCamera")))
{
    // プレイヤーの初期設定
    PlayerController* playerController = m_player->GetComponent<PlayerController>();
    playerController->SetEnemyTransform (m_enemy->GetComponent<Transform>());
    playerController->SetCamera         (m_camera->GetComponent<TargetCamera>());
    playerController->SetStageInterface (m_stage->GetComponent<StageController>());

    // 敵の初期設定
    m_enemy->GetComponent<EnemyController>()->SetFloor(m_stage->GetComponent<StageController>());

    // ターゲットのトランスフォームの設定
    m_camera->GetComponent<TargetCamera>()->SetTargetTransform(m_player->GetComponent<Transform>());

    // コライダーの登録
    m_collisionManager->RegistCollider(m_player->GetComponent<Sphere>());
    m_collisionManager->RegistCollider(m_stage->GetComponent<Mesh>());
    m_collisionManager->RegistCollider(m_enemy->GetComponent<Sphere>());

    // 読み取り専用のキャッシュ
    m_enemyController        = m_enemy->GetComponent<EnemyController>();
    m_stageController        = m_stage->GetComponent<StageController>();
    m_playerStatusController = m_player->GetComponent<PlayerStatusController>();
}

/**
 * \brief デストラクタ
 * 
 */
GameScene::~GameScene()
{
}

/**
 * \brief 初期化
 * 
 * \param projMat 射影行列
 */
void GameScene::Initialize()
{
    m_player->Initialize();
    m_enemy->Initialize();
    m_stage->Initialize();
    m_enemy->Initialize();
    m_gamePanel->Initialize();
    m_camera->Initialize();
}

/**
 * \brief 更新.
 * 
 * \param 
 */
void GameScene::Update(const GameContext& gameContext)
{
    float elapsedTime = Time::GetElapsedTime();

    if (Input::GetKeyTrigger(Keyboard::R)) {
        Initialize();
    }

    m_player->Update(gameContext);
	m_enemy->Update(gameContext);
    m_stage->Update(gameContext);
    m_camera->Update(gameContext);

    m_collisionManager->Update();

    // UI用の数値の設定
    m_gamePanel->SetUIValue(
        m_stageController->GetPlayerMeshCount(),
        m_stageController->GetEnemyMeshCount(),
        m_stageController->GetTotalMeshCount(),
        m_playerStatusController->GetAttacckCost(),
        m_playerStatusController->GetAttackPower(),
        m_enemyController->GetHp(),
        m_enemyController->GetMaxHP()
    );

    m_gamePanel->Update(gameContext);

    if (m_enemyController->GetHp() <= 0.0f || 
        Input::GetKeyDown(Keyboard::Escape))
    {
        m_pSceneController->RequestChangeScene(SceneID::Title);
    }
}


/**
 * \brief 描画.
 * 
 */
void GameScene::Render(const RenderContext& renderContext)
{
    m_stage->Render(renderContext);
    m_player->Render(renderContext);
	m_enemy->Render(renderContext);
    m_gamePanel->Render(renderContext);
}


/**
 * \brief 終了処理.
 * 
 */
void GameScene::Finalize()
{
}

/**
 * \brief デバイス依存のリソース作成
 * 
 * \param resourceContext リソース用のコンテキスト
 */
void GameScene::CreateDeviceResources(const ResourceContext& resourceContext)
{
    auto& modelManager = resourceContext.modelManager;

    ModelRenderer* playerRenderer = m_player->GetComponent<ModelRenderer>();
    ModelRenderer* enemyRenderer = m_enemy->GetComponent<ModelRenderer>();

    // モデルの設定
    playerRenderer->SetModel(modelManager->GetModel(playerRenderer->GetModelKey()));
    enemyRenderer->SetModel(modelManager->GetModel(enemyRenderer->GetModelKey()));

    // ディフーズカラーの設定
    playerRenderer->SetDiffuseColor(GameColor::PLAYER);
    enemyRenderer->SetDiffuseColor(GameColor::ENEMY);

    // UIのスプライトの設定
    m_gamePanel->SetSprite(resourceContext);
}

/**
 * \brief ウインドウサイズ依存のリソース作成
 * 
 * \param proj 射影行列
 */
void GameScene::CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj)
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void GameScene::SaveParam()
{
    m_player->SaveParam();
    m_enemy->SaveParam();
    m_stage->SaveParam();
    m_gamePanel->SaveParam();
    m_camera->SaveParam();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void GameScene::ReloadParam()
{
    m_player->ReloadParam();
    m_enemy->ReloadParam();
    m_stage->ReloadParam();
    m_gamePanel->ReloadParam();
    m_camera->ReloadParam();
}
