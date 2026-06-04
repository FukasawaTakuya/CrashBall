	/*****************************************************************//**
	 * \file   IGameObject.h
	 * \brief  ゲームオブジェクトのインターフェース
	 * 
	 * \author 深沢拓矢
	 * \date   May 2026
	 *********************************************************************/

#pragma once

// タグ
enum class ObjectTag
{
	Defaut,
	Player,
	Enemy,
	Stage,
};

class Component;

/**
 * \brief 基底オブジェクトのインターフェース
 */
class  IGameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IGameObject() = default;

	// デストラクタ
	~IGameObject() = default;

	// 操作
public:

	// 取得/設定
public:

	// コンポーネントの取得
	template<typename CompType>
	CompType* GetComponent()
	{
		auto comp = GetComponent(typeid(CompType));

		if (comp != nullptr)
		{
			return static_cast<CompType*>(comp);
		}
		else
		{
			return nullptr;
		}
	}

	// タグの取得
	virtual ObjectTag GetTag() const = 0;

	// 内部実装
protected:

	// 関数テンプレート無しでコンポーネントを取得する
	virtual Component* GetComponent(std::type_index type) = 0;

};
