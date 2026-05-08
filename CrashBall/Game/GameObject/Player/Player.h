/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤークラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once


// ヘッダファイルの読み込み ===================================================
#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"

// クラスの前方宣言 ===================================================
class Camera;

// クラスの定義 ===============================================================
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

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Player(float radius);

	// デストラクタ
	~Player() = default;

	// 操作
public:

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update();

	void Draw();

	// 取得/設定
public:

	// カメラのポインタの取得
	Camera* GetCamera() { return m_pCamera; }

	// カメラのポインタのセット
	void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	// 内部実装
private:

};
