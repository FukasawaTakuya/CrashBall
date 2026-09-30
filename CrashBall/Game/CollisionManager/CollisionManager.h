/*****************************************************************//**
 * \file   CollisionManager.h
 * \brief  衝突管理クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "IsCollisionTable.h"


 /**
 * \brief 衝突管理クラス
 */
class  CollisionManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	std::vector<Collider*> m_colliders;								// コライダー

	std::unique_ptr<IsCollisionTable> m_isCollsionTable;			// 衝突検知関数テーブル

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

	// コライダーの登録
	void RegistCollider(Collider* collider)
	{
		m_colliders.push_back(collider);
	}

	// 内部実装
private:

};
