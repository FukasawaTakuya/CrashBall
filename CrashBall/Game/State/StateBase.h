// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <Game/GameObject/Ball.h>

// クラスの前方宣言 ===================================================
template <typename Owner>
class StateMachine;

// クラスの定義 ===============================================================
/**
 * @brief ステート基底クラス
 */
template <typename Owner>
class  StateBase {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	Owner* m_owner = nullptr;						// オーナー

	StateMachine<Owner>* m_pStateMachine = nullptr;	// ステートマシンのポインタ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	StateBase() = default;

	// デストラクタ
	virtual ~StateBase() = default;

	// 操作
protected:

	// 開始処理
	virtual void OnEnter() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 終了処理
	virtual void OnExit() = 0;

public:
	
	// 開始処理の呼び出し関数
	void CallOnEnter() {
		// nullチェック
		if (m_owner == nullptr) return;
		OnEnter();
	}

	// 更新処理の呼び出し関数
	void CallUpdate() {
		// nullチェック
		if (m_owner == nullptr) return;
		Update();
	}

	// 終了処理の呼び出し関数
	void CallOnExit() {
		// nullチェック
		if (m_owner == nullptr) return;
		OnExit();
	}

	// 取得/設定
public:

	// オーナーのセット
	void SetOwner(Owner* owner) { m_owner = owner; }

	// ステートマシンのセット
	void SetStateMachine(StateMachine<Owner>* pStateMachine) { m_pStateMachine = pStateMachine; }

	// 内部実装
private:

};
