#pragma once

#include "Default/Component.h"

#include "Game/State/StateMachine.h"
#include "Game/Common/Camera.h"


/**
 * \brief プレイヤー操作クラス
 */
class  PlayerController : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<PlayerController>> m_stateMachine;	// ステートマシン

	const Camera* m_pCamera;			// カメラのポインタ

	const Transform* m_enemyTransform;	// 敵のトランスフォーム

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

	// カメラのポインタのセット
	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform() { return m_enemyTransform; }

	// 敵のトランスフォームの設定
	void SetEnemyTransform(Transform* enemyTransform)
	{
		m_enemyTransform = enemyTransform;
	}

	// 内部実装
private:

};
