// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 敵オブジェクト
 */
class  Enemy : public Ball {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<Enemy>> m_stateMachine;	// ステートマシン

	// 進行方向
	DirectX::SimpleMath::Vector3 m_direction;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Enemy(float radius);

	// デストラクタ
	~Enemy();

	// 操作
public:

	// 初期化処理
	void Inisitialize(DirectX::SimpleMath::Vector3 position);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 取得/設定
public:

	DirectX::SimpleMath::Vector3 GetDirection() const { return m_direction; }

	void SetDirection(DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }

	// 内部実装
private:

};
