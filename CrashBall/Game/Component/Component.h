/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネントに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

class GameObject;

/**
 * @brief 基底コンポーネント
 */
class  Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	GameObject* m_owner = nullptr;

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
	GameObject* GetOwner() { return m_owner; }

	// オーナーの設定
	void SetOwner(GameObject* owner)
	{
		m_owner = owner;
	}

	// 内部実装
private:

};
