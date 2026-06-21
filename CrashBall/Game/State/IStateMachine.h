#pragma once

/**
 * @brief ステートマシンのインターフェース
 */
class  IStateMachine {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IStateMachine() = default;

	// デストラクタ
	virtual ~IStateMachine() = default;

	// 操作
public:

	// 関数テンプレート無しでステートを変更
	template<typename State>
	void ChangeState()
	{
		ChangeState(typeid(State));
	}



	// 取得/設定
public:

	// 内部実装
protected:

	// ステートを変更
	virtual void ChangeState(std::type_index stateType) = 0;

};
