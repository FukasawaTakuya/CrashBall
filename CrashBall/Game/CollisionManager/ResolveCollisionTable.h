/*****************************************************************//**
 * \file   ResolveCollisionTable.h
 * \brief  衝突解決関数テーブル 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Collider/Collider.h"
#include "Collision.h"

/**
 * @brief 衝突解決関数テーブル
 */
class  ResolveCollisionTable {

	// 関数ポインタ
	using Func = void(*)(Collider*, Collider*);

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	Func m_table[TYPE_COUNT][TYPE_COUNT]{};	// 衝突判定関数のテーブル

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ResolveCollisionTable();

	// デストラクタ
	~ResolveCollisionTable();

	// 操作
public:

	// 取得/設定
public:

	void ResolveCollision(Collider* col1, Collider* col2);

	// 内部実装
private:

	// コライダータイプをIntにキャスト
	int ToInt(ColliderType type) { return static_cast<int>(type); }

	// 球対球
	static void SphereVsSphere(Collider* col1, Collider* col2);

	// 球対メッシュ
	static void SphereVsMesh(Collider* col1, Collider* col2);

	// メッシュ対メッシュ
	static void MeshVsMesh(Collider* col1, Collider* col2);
};

