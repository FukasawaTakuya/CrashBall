/*****************************************************************//**
 * \file   IsCollisionTable.h
 * \brief  衝突検知関数テーブルに関するヘッダーファイル
 * 
 * \author it252184
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Collider.h"
#include "Collision.h"

/**
 * @brief 衝突検知関数テーブル
 */
class  IsCollisionTable {

	// 関数ポインタ
	using Func = bool(*)(Collider*, Collider*);

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	Func m_isCollisionTable[TYPE_COUNT][TYPE_COUNT];	// 衝突検知関数のテーブル

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IsCollisionTable();

	// デストラクタ
	~IsCollisionTable();

	// 操作
public:

	// 取得/設定
public:

	// 衝突判定
	bool IsCollision(Collider* col1, Collider* col2);

	// 内部実装
private:

	// コライダータイプをIntにキャスト
	int ToInt(ColliderType type) { return static_cast<int>(type); }

	// 球対球
	static bool SphereVsSphere(Collider* col1, Collider* col2);

	// 球対メッシュ
	static bool SphereVsMesh(Collider* col1, Collider* col2);

	// メッシュ対メッシュ
	static bool MeshVsMesh(Collider* col1, Collider* col2);
};

