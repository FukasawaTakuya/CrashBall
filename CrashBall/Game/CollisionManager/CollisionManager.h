/*****************************************************************//**
 * \file   CollisionManager.h
 * \brief  衝突管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "IsCollisionTable.h"
#include "ResolveCollisionTable.h"


 /**
 * \brief 衝突管理クラス
 */
class  CollisionManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<Collider*> m_colliders;								// コライダー

	std::unique_ptr<IsCollisionTable> m_isCollsionTable;			// 衝突検知関数テーブル

	std::unique_ptr<ResolveCollisionTable> m_resolveCollisionTable;	// 衝突解決関数テーブル

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	CollisionManager();

	// デストラクタ
	~CollisionManager();

	// 操作
public:

	void Update();

	// 取得/設定
public:

	void RegistCollider(Collider* collider)
	{
		m_colliders.push_back(collider);
	}

	// 内部実装
private:

};
