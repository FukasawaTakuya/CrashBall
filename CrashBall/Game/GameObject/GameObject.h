/*****************************************************************//**
 * \file   GameObject.h
 * \brief  基底オブジェクトに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Component.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのコンテナ
	std::vector<std::unique_ptr<Component>> m_components;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObject() = default;

	// デストラクタ
	~GameObject() = default;

	// 操作
public:
	// 取得/設定
public:

	// コンポーネントの追加
	template<typename CompType, typename... Args>
	CompType* AddComponent(Args&&... args)
	{
		// コンポーネントの生成
		auto comp = std::make_unique<CompType>(std::forward<Args>(args)...);
		comp->SetOwner(this);

		// ポインタの取得
		CompType* pComp = comp.get();
		// コンテナに格納
		m_components.emplace_back(std::move(comp));

		return pComp;
	}

	// コンポーネントの取得
	template<typename CompType>
	CompType* GetComponent()
	{
		// コンポーネントのポインタ
		CompType* pComp = nullptr;
		for (auto& comp : m_components)
		{
			// アップキャスト
			pComp = dynamic_cast<CompType*>(comp.get());

			// null出ないならbreak
			if (pComp != nullptr) break;
		}

		return pComp;
	}

	// 内部実装
private:

};
