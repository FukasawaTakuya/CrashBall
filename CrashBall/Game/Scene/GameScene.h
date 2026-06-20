/*****************************************************************//**
 * \file   GameScene.h
 * \brief  ゲームシーンクラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Scene.h"

#include "Game/GameObject/Ball.h"
#include "Game/GameObject/Stage.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/GameObject/Enemy/Enemy.h"
#include "Game/GameObject/UIObject/GamePanel.h"

#include "Game/Common/GameCamera.h"

#include "Game/CollisionManager/CollisionManager.h"


/**
 * \brief 基底オブジェクト
 */
class  GameScene : public Scene{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<Stage>		m_stage;		// ステージ
	std::unique_ptr<Player>		m_player;		// プレイヤー
	std::unique_ptr<Enemy>		m_enemy;		// 敵
	std::unique_ptr<GamePanel>	m_gamePanel;	// パネル

	std::unique_ptr<CollisionManager> m_collisionManager;	// 衝突管理オブジェクト

	std::unique_ptr<GameCamera> m_camera;	// カメラ

	// 読み取り専用のコンポーネントのキャッシュ
	const EnemyController*			m_enemyController		 = nullptr;
	const PlayerStatusController*	m_playerStatusController = nullptr;
	const StageController*			m_stageController		 = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameScene(ISceneController* pSceneManager);

	// デストラクタ
	~GameScene();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Draw(const RenderContext& renderContext) override;

	// 終了
	void Finalize() override;

	// リソース作成
	void CreateDeviceResources(const ResourceContext& resourceContext) override;

	// リソース作成
	void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj) override;

	// 取得/設定
public:

	// カメラの取得
	ICamera* GetCamera() const override
	{
		return m_camera->GetComponent<TargetCamera>();
	}


	// 内部実装
private:

};
