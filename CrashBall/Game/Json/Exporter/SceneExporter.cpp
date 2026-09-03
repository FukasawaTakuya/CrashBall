/*****************************************************************//**
 * \file   SceneExporter.h
 * \brief  シーンエクスポーター
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "SceneExporter.h"

#include <filesystem>
#include <fstream>

/**
 * \brief コンストラクタ
 * 
 */
SceneExporter::SceneExporter()
	: m_gameObjectExporter(std::make_unique<GameObjectExporter>())
{
}

/**
 * \brief デストラクタ
 * 
 */
SceneExporter::~SceneExporter()
{
}

/**
 * \brief シーンのエクスポート
 * 
 * \param scene シーン
 */
void SceneExporter::ExportScene(Scene* scene)
{
	// 保存フォルダ
	std::filesystem::path exportFile = "Resources/Data/Objects" + scene->GetSceneName();

	// オブジェクト保存フォルダ
	std::filesystem::path objectExportFile = exportFile.string() + "/Objects";


	// フォルダの作成
	std::filesystem::create_directories(exportFile); 
	std::filesystem::create_directories(objectExportFile);

	// エクスポート先のパス
	std::string exportPath = exportFile.string() + "/";
	std::string objectExportPath = objectExportFile.string() + "/";

	// 保存ファイル名
	std::ofstream ofs(exportPath + scene->GetSceneName() + ".json");

	// Json
	ordered_json sceneData;

	sceneData["SceneName"] = scene->GetSceneName();

	// オブジェクト名の保存とオブジェクトのエクスポート
	for (auto obj : *scene->GetGameObjects())
	{
		//sceneData["Objects"].push_back(obj->GetName());

		// オブジェクトのエクスポート
		m_gameObjectExporter->ExporterGameObject(obj, objectExportPath);
	}

	// 書き込み
	ofs << sceneData.dump(3);
}
