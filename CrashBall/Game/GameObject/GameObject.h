/*****************************************************************//**
 * \file   GameObject.h
 * \brief  基底オブジェクト 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include <unordered_map>
#include <algorithm>

#include "Game/GameObject/IGameObject.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Component/Default/Component.h"

/**
 * \brief 基底オブジェクト
 */
class GameObject : public IGameObject {

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

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(const GameContext& gameContext) = 0;

	// 描画
	virtual void Render(const RenderContext& RenderContext) = 0;

	// 終了処理
	virtual void Finalize() = 0;

	// 取得/設定
public:

	// コンポーネントの追加
	template<typename CompType, typename... Args>
	CompType* AddComponent(Args&&... args)
	{
		// コンポーネントの生成
		auto comp = std::make_unique<CompType>(this, std::forward<Args>(args)...);

		// ポインタの取得
		CompType* pComp = comp.get();
		// コンテナに格納
		m_components.emplace(typeid(CompType), std::move(comp));

		// コンポーネントのポインタを返す
		return pComp;
	}

	// タグの取得
	ObjectTag GetTag() const override { return m_tag; }

	// コンポーネントの取得
	using IGameObject::GetComponent;

	// 内部実装
private:

	// 関数テンプレート無しでコンポーネントを取得する
	Component* GetComponent(std::type_index type) override
	{
		auto it = m_components.find(type);
			// イテレータが終端でなければコンポーネントを返す
			if (it != m_components.end()) {
				return it->second.get();
			}
			// イテレータが終端ならnullptrを返す
			else return nullptr;
	}
};
