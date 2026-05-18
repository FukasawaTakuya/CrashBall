
#pragma once
#include "Game/Interface/ITimeManager.h"

/**
 * @brief 時間取得クラス
 */
class TimeService {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ITimeManager* m_timeManager;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	TimeService() = default;

	// 複数生成の禁止
	TimeService(TimeService&) = delete;
	TimeService& operator= (const TimeService&) = delete;

	// デストラクタ
	~TimeService() = default;

	// 操作
public:
	// インスタンスの取得
	static TimeService& Instance() {
		static TimeService instance;
		return instance;
	}

	// 取得/設定
public:

	// 入力の取得
	ITimeManager* GetTime() { return m_timeManager; }

	// 入力システムのインターフェースの設定
	void SetTime(ITimeManager* timeManager) { m_timeManager = timeManager; }

	// 内部実装
private:

};