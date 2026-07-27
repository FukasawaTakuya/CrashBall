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
