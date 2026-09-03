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
	// 書き込むファイル名
	std::ofstream ofs(exportPath + gameObject->GetName() + ".json");

	ordered_json jsonData;

	//::to_json(jsonData, *gameObject); include

	jsonData["name"] = gameObject->GetName();
	jsonData["tag"] = gameObject->GetTag();
	jsonData["id"] = gameObject->GetID();
	jsonData["isActive"] = gameObject->GetIsActive();

	// コンポーネントを書き込む
	for (auto& comp : *gameObject->GetComponentsList())
	{
		jsonData["components"].push_back(
			*static_cast<Component*>(comp.get())
		);
	}

	jsonData["children"] = nullptr;

	// 子オブジェクトを書き込む
	for (auto child : gameObject->GetChildren())
	{
		jsonData["children"].push_back(child->GetName());
		ExporterGameObject(child, exportPath);
	}

	// ファイルに書き込み
	ofs << jsonData.dump(3);
}
