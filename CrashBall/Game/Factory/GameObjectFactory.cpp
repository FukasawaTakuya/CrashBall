#include "pch.h"
#include "GameObjectFactory.h"

/**
 * \brief データからのゲームオブジェクトの作成
 * 
 * \param data jsonデータ
 * \return 
 */
std::unique_ptr<GameObject> GameObjectFactory::CreataFromJson(ordered_json data)
{
	//std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();

	//obj->SetName(data["name"]);
	//obj->SetTag(data["tag"]);
	//obj->SetIsActive(data["isActive"]);




	//return std::move(obj);
}
