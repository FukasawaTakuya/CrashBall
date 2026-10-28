/*****************************************************************//**
 * \file   ModelManager.cpp
 * \brief  モデル管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelManager.h"
#include "Game/Common/Utility.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ModelManager::ModelManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
ModelManager::~ModelManager()
{
}

/**
 * \brief モデルの生成
 * 
 * \param device　デバイス
 */
void ModelManager::CreateModel(ID3D11Device1* device)
{
	m_models.clear();

	for (auto& file : std::filesystem::directory_iterator("Resources/Model"))
	{
		// ファイルパス
		std::string path = file.path().string();
		// モデルを作成
		auto model = std::make_unique<MyModel>();
		model->Create(device, file.path().string());

		// キーを抽出
		size_t end = path.rfind(".");
		size_t start = path.rfind("Model") + 6;
		std::string key = path.substr(start, end - start);
		// コンテナに追加
		m_models.emplace(key, std::move(model));
	}
}

MyModel* ModelManager::GetModel(const std::string& key)
{
	auto it = m_models.find(key);

	if (it != m_models.end())
	{
		return it->second.get();
	}
	else return nullptr;
}
