// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/GameObject/GameObject.h"
#include "IsCollisionTable.h"
#include "ResolveCollisionTable.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 衝突管理クラス
 */
class  CollisionManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<Collider*> m_colliderList;	 // ゲームオブジェクトのリスト

	std::unique_ptr<IsCollisionTable> m_isCollsionTable;

	std::unique_ptr<ResolveCollisionTable> m_resolveCollisionTable;

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
		m_colliderList.push_back(collider);
	}

	// 内部実装
private:

};
