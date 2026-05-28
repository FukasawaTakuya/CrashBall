/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/IGameObject.h"

/**
 * @brief 基底コンポーネント
 */
class  Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	IGameObject* m_owner = nullptr;	// オーナー

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Component() = default;

	// デストラクタ
	virtual ~Component() = default;

	// 操作
public:

	// 取得/設定
public:

	// オーナーの取得
	IGameObject* GetOwner() { return m_owner; }

	// オーナーの設定
	void SetOwner(IGameObject* owner)
	{
		m_owner = owner;
	}

	// 内部実装
private:

};
