/*****************************************************************//**
 * \file   IComponent.h
 * \brief  コンポーネントのインターフェース
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include <vector>
#include <string>
#include <typeindex>

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Factory/ComponentRegister.h"

#include "Game/Common/Utility.h"

class IGameObject;

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
	std::type_index propTypeId{ typeid(void) };	// プロパティのtypeid
	void* data;									// プロパティのアドレス
};


/**
 * @brief コンポーネントのインターフェース
 */
class  IComponent {

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

	// コンポーネントの登録
#define RegsterComponent(Comp)\
	static constexpr ComponetRegister<Comp> s_compRegisgter(#Comp); \
	static constexpr std::string s_compName = #Comp;

	// 操作
public:

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(const GameContext& gameContext) = 0;

	// 描画
	virtual void Render(const RenderContext& renderContext) = 0;


	// 取得/設定
public:

	// ゲームオブジェクトの取得
	virtual IGameObject* GetGameObject() const = 0;

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const = 0;

	// コンポーネント名の取得
	virtual std::string GetCompName() const = 0;

private:

	friend void to_json(ordered_json& j, const IComponent& component);
	friend void from_json(const ordered_json& j, IComponent& component);

};
