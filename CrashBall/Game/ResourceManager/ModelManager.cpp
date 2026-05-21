/*****************************************************************//**
 * \file   ModelManager.cpp
 * \brief  モデル管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelManager.h"
#include "Game/Common/CommonResources.h"

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
 * \brief ファクトリーに登録
 * 
 * \param key　キー
 * \param fileName	ファイル名
 */
void ModelManager::RegisterFactory(std::string key, const wchar_t* fileName)
{
	m_modelFactory.emplace(key, fileName);
}

/**
 * \brief モデルの生成
 * 
 * \param device　デバイス
 */
void ModelManager::CreateModel(ID3D11Device1* device)
{
	m_models.clear();

	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");

	for (auto& file : m_modelFactory) {
		auto model = Model::CreateFromSDKMESH(device, file.second, fx);

		m_models.emplace(file.first, std::move(model));
	}
}

DirectX::Model* ModelManager::GetModel(const std::string& key)
{
	auto it = m_models.find(key);

	if (it != m_models.end())
	{
		return it->second.get();
	}
	else return nullptr;
}
