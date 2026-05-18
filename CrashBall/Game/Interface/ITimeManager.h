#pragma once


/**
 * @brief 基底オブジェクト
 */
class  ITimeManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ITimeManager() = default;

	// デストラクタ
	virtual ~ITimeManager() = default;

	// 操作
public:

	// 取得/設定
public:

	virtual float GetElapsedTime() const = 0;

	virtual float GetUnscaleElapsedTime() const = 0;

	virtual void SetElapsedTime(float elapsedTime) = 0;

	virtual void SetTimeScale(float timeScale) = 0;

	// 内部実装
private:

};
