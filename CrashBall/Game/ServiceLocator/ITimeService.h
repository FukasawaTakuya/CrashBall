/*****************************************************************//**
 * \file   ITimeService.h
 * \brief  時間管理クラスのインターフェース
 * 
 * \author it252184
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/Service.h"

/**
 * @brief 基底オブジェクト
 */
class  ITimeService : public Service {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

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

	virtual float GetElapsedTime() const = 0;

	virtual float GetUnscaleElapsedTime() const = 0;

	virtual void SetTimeScale(float timeScale) = 0;

	// 内部実装
private:

};
