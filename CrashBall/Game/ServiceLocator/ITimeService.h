/*****************************************************************//**
 * \file   ITimeService.h
 * \brief  時間管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/Service.h"

/**
 * @brief 時間管理クラスのインターフェース
 */
class  ITimeService : public Service {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ITimeService() = default;

	// デストラクタ
	virtual ~ITimeService() = default;

	// 操作
public:

	// 取得/設定
public:

	// 経過時間の取得(スケーリング有り)
	virtual float GetElapsedTime() const = 0;

	// 経過時間の取得(スケーリング無し)
	virtual float GetUnscaleElapsedTime() const = 0;

	// タイムスケールの設定
	virtual void SetTimeScale(float timeScale) = 0;

	// 内部実装
private:

};
