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
#include "Game/Component/TargetCamera.h"
#include "PlayerStatusController.h"
#include "IPaintConsumer.h"
#include "StageController.h"


/**
 * \brief プレイヤー操作コンポーネント
 */
class  PlayerController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	// 初期位置
	static constexpr DirectX::SimpleMath::Vector3 INIT_POSITION
		= DirectX::SimpleMath::Vector3(0.0f, 12.0f, 5.0f);

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<PlayerController>> m_stateMachine;	// ステートマシン

	const TargetCamera* m_pCamera = nullptr;				// カメラのポインタ

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

	// 
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 取得/設定
public:

	// カメラのポインタの取得
	const TargetCamera* GetCamera() { return m_pCamera; }

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform() { return m_enemyTransform; }
	
	// 面消費インターフェースの取得
	IPaintConsumer* GetPaintConsumer() const
	{
		return m_paintConsumer;
	}

	// カメラのポインタのセット
	void SetCamera(const TargetCamera* pCamera) { m_pCamera = pCamera; }

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
