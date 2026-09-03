#include "pch.h"
#include "GameObjectFactory.h"

#include <fstream>

//std::unique_ptr<GameObject> GameObjectFactory::CreateObjectFromJson(ordered_json& data)
//{
//	// ゲームオブジェクトの生成
//	std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
//
//	obj->SetName(data["name"]);
//	obj->SetTag(data["tag"]);
//	obj->SetIsActive(data["isActive"]);
//	obj->SetData(&data);
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
