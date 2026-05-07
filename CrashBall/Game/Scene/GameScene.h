/*****************************************************************//**
 * \file   GameScene.h
 * \brief  ゲームシーンに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Scene.h"
#include "Game/GameObject/Ball.h"
#include "Game/GameObject/Floor.h"
#include "Game/Common/Camera.h"
#include "Game/GameObject/Player/Player.h"
#include <Game/CollisionManager/CollisionManager.h>
//
// クラスの前方宣言 ===================================================


// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  GameScene : public Scene{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<MeshFloor> m_meshFloor;		// ステージ

	std::unique_ptr<Player> m_player;			// プレイヤー

	std::unique_ptr<Ball> m_ball;				// ボール

	std::vector<Triangle*> m_hitFaces;

	std::unique_ptr<CollisionManager> m_collisionManager;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameScene(SceneManager* pSceneManager);

	// デストラクタ
	~GameScene();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(float elapsedTime) override;

	// 描画
	void Draw() override;

	// 終了
	void Finalize() override;

	// リソース作成
	void CreateResources(DirectX::SimpleMath::Matrix projMat) override;

	void SetModel() override;


	// 取得/設定
public:

	// 内部実装
private:

};
