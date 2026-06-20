/*****************************************************************//**
 * \file   IPaintConsumer.h
 * \brief  面の消費のインターフェース 
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

/**
 * \brief 面の消費のインターフェース 
 */
class  IPaintConsumer {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IPaintConsumer() = default;

	// デストラクタ
	~IPaintConsumer() = default;

	// 操作
public:

	// 面の消費
	virtual void ConsumePaint(int consumePaintNum) = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
