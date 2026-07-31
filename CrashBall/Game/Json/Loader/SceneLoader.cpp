#include "pch.h"
#include "SceneLoader.h"

#include <fstream>

#include "Game/Factory/GameObjectFactory.h"

/**
 * \brief コンストラクタ
 * 
 */
SceneLoader::SceneLoader()
{
}

/**
 * \brief デストラクタ
 * 
 */
SceneLoader::~SceneLoader()
{
}

void SceneLoader::LoadScene(Scene* scene)
{
	std::filesystem::path loadPath("Resources/Data/" + scene->GetSceneName() + "/");

	std::filesystem::path objectLoadPath(loadPath.string() + "Objects/");

	std::ifstream ifs("Resources/Data/" + scene->GetSceneName() + "/" + scene->GetSceneName() + ".json");

	ordered_json sceneData;

	ifs >> sceneData;

	for (auto& object : sceneData["Objects"])
	{
		auto obj = GameObjectFactory::CreateObjectFromJson(
			object,
			objectLoadPath.string()
		);

		// TODO:JsonManagerにファイルパスとjsonを保管
		scene->AddObject(std::move(obj));
	}
}
