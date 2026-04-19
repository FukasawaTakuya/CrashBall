// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "pch.h"
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
protected:
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

	template<typename CompType, typename... Arg>
	CompType* AddComponent(Arg&&...arg)
	{
		auto comp = std::make_unique<CompType>(std::forward(arg...));
		comp->SetOwner(this);
		m_components.emplace_back(std::move(comp));
		return comp;
	}

	template<typename CompType>
	CompType* GetComponent()
	{
		return m_components.at(typeid(CompType)).get();
	}

	// 内部実装
private:

};
