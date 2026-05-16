/*****************************************************************//**
 * \file   GameObject.h
 * \brief  基底オブジェクトに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "pch.h"
#include "Game/Component/Component.h"


// タグ
enum class ObjectTag
{
	Defaut,
	Player,
	Enemy,
	Stage,
};

/**
 * @brief 基底オブジェクト
 */
class GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのコンテナ
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	// タグ
	ObjectTag m_tag;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObject(ObjectTag tag = ObjectTag::Defaut)
		: m_tag(tag)
	{};

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
		// オーナーの設定
		comp->SetOwner(this);

		// ポインタの取得
		CompType* pComp = comp.get();
		// コンテナに格納
		m_components.emplace(typeid(CompType), std::move(comp));

		// コンポーネントのポインタを返す
		return pComp;
	}

	// コンポーネントの取得
	template<typename CompType>
	CompType* GetComponent()
	{
		// イテレータの取得
		auto it = m_components.find(typeid(CompType));
		// イテレータが終端でなければコンポーネントを返す
		if (it != m_components.end()) {
			return static_cast<CompType*>(it->second.get());
		}
		// イテレータが終端ならnullptrを返す
		return nullptr;
	}

	// タグの取得
	ObjectTag GetTag() const { return m_tag; }

	// 内部実装
private:

};
