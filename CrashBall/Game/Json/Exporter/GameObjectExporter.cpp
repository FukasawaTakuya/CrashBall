#include "pch.h"
#include "GameObjectExporter.h"


#include <fstream>

/**
 * \brief コンストラクタ
 * 
 */
GameObjectExporter::GameObjectExporter()
{
}

/**
 * \brief デストラクタ
 * 
 */
GameObjectExporter::~GameObjectExporter()
{
}

/**
 * \brief エクスポート
 * 
 * \param gameObject エクスポートするゲームオブジェクト
 * \param exportPath エクスポート先のパス
 */
void GameObjectExporter::ExporterGameObject(
	GameObject* gameObject,
	const std::string& exportPath)
{
	std::ofstream ofs(exportPath + gameObject->GetName() + ".json");

	ordered_json jsonData;

	jsonData["name"] = gameObject->GetName();
	jsonData["tag"] = gameObject->GetTag();
	//jsonData["isActive"] = gameObject->GetIsActive();

	//for (auto& comp : *gameObject->GetComponentsList())
	//{
	//	jsonData["components"].push_back(
	//		""// ComponentExporter(comp)
	//	);
	//}

	//std::string s = TO_STRING_VELUE(int)
	//OutputDebugStringA(s.c_str());
}
