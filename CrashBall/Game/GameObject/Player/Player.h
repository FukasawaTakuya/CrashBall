/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤークラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"

class Camera;

/**
 * @brief プレイヤークラス
 */
class  Player : public Ball{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<Player>> m_stateMachine;	// ステートマシン

	Camera* m_pCamera = nullptr;							// カメラのポインタ

	const Transform* m_enemyTransform = nullptr;			// 敵のトランスフォーム

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Player(float radius);

	// デストラクタ
	~Player() = default;

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const GameContext& gameContext) override;

	// 終了処理
	void Finalize() override;

	// 取得/設定
public:

	// カメラのポインタの取得
	Camera* GetCamera() { return m_pCamera; }

	// カメラのポインタのセット
	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform() { return m_enemyTransform; }

	void SetEnemyTransform(Transform* enemyTransform)
	{
		m_enemyTransform = enemyTransform;
	}

	// 内部実装
private:

};
