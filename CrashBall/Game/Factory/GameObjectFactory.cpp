#include "pch.h"
#include "GameObjectFactory.h"

#include <fstream>

/**
 * \brief データからのゲームオブジェクトの作成
 * 
 * \param objectName オブジェクト名
 * \param loadPath ファイルパス
 * \return ゲームオブジェクト
 */
//std::unique_ptr<GameObject> GameObjectFactory::CreateObjectFromJson(
//	const std::string& objectName, 
//	const std::string& loadPath)
//{
//	// ファイルの読み込み
//	std::ifstream ifs(loadPath + objectName + ".json");
//
//	ordered_json data;
//
//	ifs >> data;
//
//	// ゲームオブジェクトの生成
//	std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
//
//	obj->SetName(data["name"]);
//	obj->SetTag(data["tag"]);
//	obj->SetIsActive(data["isActive"]);
//
//	// コンポーネントの追加
//	for (auto& comp : data["components"])
//	{
//		auto compPtr = obj->AddComponent(
//			ComponentFactory::CreataFromJson(comp["compName"], obj.get())
//		);
//
//		comp.get_to<Component>(*compPtr);
//	}
//
//	return std::move(obj);
//}
