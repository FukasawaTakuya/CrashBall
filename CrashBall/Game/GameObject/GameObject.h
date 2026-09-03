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
	std::vector<GameObject*> m_children;

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

	// データの保存
	void SaveData();

	virtual void SetResource(const ResourceContext& resourceContext);

	// パラメータの書き込み
	virtual void SaveParam();

	// データの再読み込み
	virtual void ReloadParam();

	// 子オブジェクトの追加
	void AddChildren(GameObject* child);

	// 子オブジェクトの初期化
	void InitializeChildren();

	// 子オブジェクトの更新
	void UpdateChildren(const GameContext& gameContext);

	// 子オブジェクトの描画
	void RenderChildren(const RenderContext& renderContext);

	// 子オブジェクトの終了処理
	void FinalizeChildren();

	// 取得/設定
public:

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

	// タグの取得
	ObjectTag GetTag() const override { return m_tag; }

	// コンポーネントの取得
	using IGameObject::GetComponent;

	// 子オブジェクトの取得
	const std::vector<GameObject*>& GetChildren() const
	{
		return m_children;
	}

	// 名前の取得
	std::string GetName() const
	{
		return m_name;
	}

	int GetID() const
	{
		return m_id;
	}

	// アクティブフラグの取得
	bool GetIsActive() const
	{
		return m_isActice;
	}

	// 名前の設定
	void SetName(std::string name)
	{
		m_name = name;
	}


	// タグの設定
	void SetTag(ObjectTag tag)
	{
		m_tag = tag;
	}

	// IDの設定
	void SetID(int id)
	{
		m_id = id;
	}

	// データの設定
	void SetData(ordered_json* data)
	{
		m_data = data;
	}

	// アクティブフラグの設定
	void SetIsActive(bool isActive)
	{
		m_isActice = isActive;
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
