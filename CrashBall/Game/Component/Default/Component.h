/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/IGameObject.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Common/Utility.h"

// プロパティタイプ
enum class PropertyType
{
	None,
	Bool,
	Int,
	Float,
	Vector2,
	Vector3,
	Quaternion,
	Color,
	String,
	Enum,
};

// プロパティ情報
struct PropertyInfo
{
	std::string name;							// プロパティ名
	PropertyType propType;						// プロパティタイプ
	std::type_index propTypeId{typeid(void)};	// プロパティのtypeid
	void* data;									// プロパティのアドレス
};

/**
 * \brief 基底コンポーネント
 */
class  Component {

// マクロの宣言 ---------------------------------------------------------

	// プロパティ記述開始
#define BeginProperty()\
private:	\
	std::vector<PropertyInfo> m_properties = { \

	// プロパティの追加
#define AddProperty(field, type)\
	{ PropertyInfo(Utility::RemoveMemberPrefix(#field), type, typeid(field), &field) } ,

	// プロパティ記述終了
#define EndProperty()\
	};

	// コンポーネント名の設定
#define SetCompName(compName)\
	std::string m_compName = compName;

	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_gameObject = nullptr;	// ゲームオブジェクト
	
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Component() = default;

	// コンストラクタ
	Component(IGameObject* gameObject);

	// デストラクタ
	virtual ~Component() = default;

	// 操作
public:

	// 初期化
	virtual void Initialize() {};

	// 更新
	virtual void Update(const GameContext& gameContext) {};

	// 描画
	virtual void Render(const RenderContext& renderContext) {};

	// 取得/設定
public:

	// ゲームオブジェクトの取得
	IGameObject* GetGameObject() const 
	{ 
		return m_gameObject; 
	}

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const = 0;

	// コンポーネント名の取得
	virtual std::string GetCompName() const = 0;

private:

	friend void to_json(ordered_json& j, const Component& component);
	friend void from_json(const ordered_json& j, Component& component);
};
