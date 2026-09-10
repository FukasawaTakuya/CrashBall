/*****************************************************************//**
 * \file   GameObject.h
 * \brief  基底オブジェクト 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/IGameObject.h"

#include "Game/Factory/ComponentFactory.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"

#include "Game/Component/Default/Component.h"

#include "Game/Json/Enum/JsonEnumSerializers.h"

/**
 * \brief 基底オブジェクト
 */
class GameObject : public IGameObject {

	friend class ObjectInspectorGui;
	friend class GameObjectExporter;

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのコンテナ
	std::vector<std::unique_ptr<Component>> m_components;

	// 検索用のコンポーネントのコンテナ
	std::unordered_map<std::type_index, Component*> m_componentsMap;

	// タグ
	ObjectTag m_tag;

	// オブジェクト名
	std::string m_name = "object";

	// ID
	int m_id = 0;

	// アクティブフラグ
	bool m_isActice = true;

	// 子オブジェクト
	std::vector<std::unique_ptr<GameObject>> m_children;

protected:

	// Jsonデータ
	ordered_json* m_data = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObject(ObjectTag tag = ObjectTag::Default);

	// コンストラクタ
	GameObject(ordered_json* data);

	// デストラクタ
	~GameObject() = default;

	// 操作
public:

	// 開始処理
	virtual void Awake();

	// 初期化
	virtual void Start(const GameContext& gameContext);

	// 更新
	virtual void Update(const GameContext& gameContext);

	// 描画
	virtual void Render(const RenderContext& renderContext);

	// 終了処理
	virtual void Finalize() {};

	// リソースの設定
	virtual void SetResource(const ResourceContext& resourceContext);

	// データの保存
	void SaveData();

	// コンポーネントの追加
	template<typename CompType, typename... Args>
	CompType* AddComponent(Args&&... args)
	{
		auto comp = ComponentFactory::Create<CompType>(this, std::forward<Args>(args)...);

		// コンポーネントの生成
		CompType* pComp = comp.get();
		// コンテナに格納
		m_components.push_back(std::move(comp));
		// 検索用コンテナに格納
		m_componentsMap.emplace(typeid(CompType), pComp);
		// 親がComponentでないときに親のIDでもマップに登録
		if (pComp->GetBaseTypeid() != typeid(Component))
		{
			m_componentsMap.emplace(pComp->GetBaseTypeid(), pComp);
		}
		// コンポーネントのポインタを返す
		return pComp;
	}

	// コンポーネントの追加
	Component* AddComponent(std::unique_ptr<Component>&& comp)
	{
		Component* pComp = comp.get();
		// コンテナに格納
		m_components.push_back(std::move(comp));
		// 検索用コンテナに格納
		m_componentsMap.emplace(typeid(*pComp), pComp);
		// 親がComponentでないときに親のIDでもマップに登録
		if (pComp->GetBaseTypeid() != typeid(Component))
		{
			m_componentsMap.emplace(pComp->GetBaseTypeid(), pComp);
		}
		return pComp;
	}

	// 子オブジェクトの追加
	void AddChildren(std::unique_ptr<GameObject>&& child);

	// 子オブジェクトの削除
	void RemoveChild(const std::string& name);

	// 子オブジェクトの検索
	GameObject* FindChild(const std::string& name);

	// 取得/設定
public:


	// コンポーネントの取得
	using IGameObject::GetComponent;

	// 子オブジェクトの取得
	const std::vector<std::unique_ptr<GameObject>>& GetChildren() const
	{
		return m_children;
	}

	// 名前の取得
	std::string GetName() const override
	{
		return m_name;
	}

	// タグの取得
	ObjectTag GetTag() const override { return m_tag; }

	int GetID() const override
	{
		return m_id;
	}

	// アクティブフラグの取得
	bool GetIsActive() const override
	{
		return m_isActice;
	}

	// 名前の設定
	void SetName(std::string name) override
	{
		m_name = name;
	}

	// タグの設定
	void SetTag(ObjectTag tag) override
	{
		m_tag = tag;
	}

	// IDの設定
	void SetID(int id) override
	{
		m_id = id;
	}

	// アクティブフラグの設定
	void SetIsActive(bool isActive) override
	{
		m_isActice = isActive;
	}

	// データの設定
	void SetData(ordered_json* data)
	{
		m_data = data;
	}

	// 内部実装
private:

	// 関数テンプレート無しでコンポーネントを取得する
	Component* GetComponent(std::type_index type) override
	{
		auto it = m_componentsMap.find(type);
		// イテレータが終端でなければコンポーネントを返す
		if (it != m_componentsMap.end()) {
			return it->second;
		}
		// イテレータが終端ならnullptrを返す
		else return nullptr;
	}

	// コンポーネントの取得
	const std::vector<std::unique_ptr<Component>>* GetComponentsList() const
	{
		return &m_components;
	}

private:
	friend void to_json(ordered_json& j, const GameObject& gameObject);
};
