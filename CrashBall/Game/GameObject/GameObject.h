/*****************************************************************//**
 * \file   GameObject.h
 * \brief  基底オブジェクト 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/IGameObject.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Component/Default/Component.h"

#include "Game/Json/Enum/JsonEnumSerializers.h"

/**
 * \brief 基底オブジェクト
 */
class GameObject : public IGameObject {

	friend class ObjectInspectorGui;

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのコンテナ
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	// タグ
	ObjectTag m_tag;

	// オブジェクト名
	std::string m_name = "object";

	// 子オブジェクト
	std::vector<GameObject*> m_children;

protected:

	// Jsonデータ
	json* m_data = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameObject(ObjectTag tag = ObjectTag::Defaut);

	// コンストラクタ
	GameObject(json* data);

	// デストラクタ
	~GameObject() = default;

	// 操作
public:

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(const GameContext& gameContext) = 0;

	// 描画
	virtual void Render(const RenderContext& renderContext) = 0;

	// 終了処理
	virtual void Finalize() = 0;

	// パラメータの書き込み
	virtual void SaveParam();

	// 初期化用のパラメータの書き込み
	virtual void SaveInitParam();

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

	// 子オブジェクトの取得
	const std::vector<GameObject*>& GetChildren()
	{
		return m_children;
	}

	// 名前の取得
	std::string GetName()
	{
		return m_name;
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
