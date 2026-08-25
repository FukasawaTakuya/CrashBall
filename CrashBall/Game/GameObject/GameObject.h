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
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	// タグ
	ObjectTag m_tag;

	// オブジェクト名
	std::string m_name = "object";

	// アクティブフラグ
	bool m_isActice = true;

	// 子オブジェクト
	std::vector<GameObject*> m_children;

protected:

	// Jsonデータ
	json* m_data = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObject(ObjectTag tag = ObjectTag::Default);

	// コンストラクタ
	GameObject(json* data);

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
		m_components.emplace(typeid(CompType), std::move(comp));

		// コンポーネントのポインタを返す
		return pComp;
	}

	Component* AddComponent(std::unique_ptr<Component>&& comp)
	{
		Component* ptr = comp.get();
		m_components.emplace(typeid(*comp.get()), std::move(comp));
		return ptr;
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

	// データの設定
	void SetData(json* data)
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
		auto it = m_components.find(type);
			// イテレータが終端でなければコンポーネントを返す
			if (it != m_components.end()) {
				return it->second.get();
			}
			// イテレータが終端ならnullptrを返す
			else return nullptr;
	}

	// コンポーネントの取得
	const std::unordered_map<std::type_index, std::unique_ptr<Component>>* GetComponentsList() const
	{
		return &m_components;
	}
};
