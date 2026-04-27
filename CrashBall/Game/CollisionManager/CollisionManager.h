// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/GameObject/GameObject.h"

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

	std::vector<GameObject*> m_gameObjectList;	 // ゲームオブジェクトのリスト

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

	void SetCollider(GameObject* collider)
	{
		m_gameObjectList.push_back(collider);
	}

	// 内部実装
private:

};
