#pragma once
#include "Game/Component/Default/Component.h"

class GameObject;

/**
 * \brief
 */
class  ComponentFactory {

	using CreataFunc = Component*(*)(json);

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<std::unique_ptr<Component>> m_components;

	std::unordered_map<std::string, CreataFunc> m_createComp;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	ComponentFactory();

	// 複数生成の禁止
	ComponentFactory(ComponentFactory&) = delete;
	ComponentFactory& operator=(ComponentFactory&) = delete;

	// デストラクタ
	~ComponentFactory() = default;

	// 操作
public:

	// コンポーネントの生成
	static Component* Create(json data, GameObject* gameObject);

	// コンポーネントの生成
	template<typename CompType, typename... Args>
	static CompType* Create(GameObject* gameObject, Args&&... args)
	{
		auto& instance = GetInstance();

		// コンポーネントの生成
		auto comp = std::make_unique<CompType>(gameObject, std::forward<Args>(args)...);

		// ポインタの取得
		CompType* pComp = comp.get();
		// コンテナに格納
		instance.m_components.push_back(std::move(comp));

		// コンポーネントのポインタを返す
		return pComp;
	}
	// 内部実装
private:

	// インスタンスの取得
	static ComponentFactory& GetInstance()
	{
		static auto instance = ComponentFactory();
		return instance;
	}

	// トランスフォームの作成
	Component* CreateTransform(GameObject* gameObject, json data);

};
