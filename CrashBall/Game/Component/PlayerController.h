/*****************************************************************//**
 * \file   PlayerController.h
 * \brief  プレイヤー操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Default/Component.h"

#include "Game/State/StateMachine.h"
#include "Game/Common/Camera.h"
#include "PlayerStatusController.h"
#include "IPaintConsumer.h"
#include "StageController.h"


/**
 * \brief プレイヤー操作コンポーネント
 */
class  PlayerController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<PlayerController>> m_stateMachine;	// ステートマシン

	PlayerStatusController* m_playerStateController = nullptr;		// プレイヤーステータス管理コンポーネント

	const Camera* m_pCamera = nullptr;				// カメラのポインタ

	const Transform* m_enemyTransform = nullptr;	// 敵のトランスフォームコンポーネント

	IPaintConsumer* m_paintConsumer = nullptr;		// 面消費インターフェース

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerController(IGameObject* owner);

	// デストラクタ
	~PlayerController();

	// 操作
public:

	// 更新
	void Update(const GameContext& gameContext);

	// 取得/設定
public:

	// カメラのポインタの取得
	const Camera* GetCamera() { return m_pCamera; }

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform() { return m_enemyTransform; }
	
	// 面消費インターフェースの取得
	IPaintConsumer* GetPaintConsumer() const
	{
		return m_paintConsumer;
	}

	// カメラのポインタのセット
	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	// 敵のトランスフォームの設定
	void SetEnemyTransform(Transform* enemyTransform)
	{
		m_enemyTransform = enemyTransform;
	}

	// ステージ操作コンポーネントからインターフェースを設定する
	void SetStageInterface(StageController* stageController)
	{
		// 面消費コンポーネントの設定
		m_paintConsumer = stageController;
		// 床メッシュ取得コンポーネントを設定
		GetGameObject()->GetComponent<PlayerStatusController>()->SetFloorMeshGetter(stageController);
	}


	// 内部実装
private:

};
