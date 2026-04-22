/*****************************************************************//**
 * \file   ModelManager.cpp
 * \brief  モデル管理クラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelManager.h"
#include "Game/Common/CommonResources.h"

using namespace DirectX;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

/**
 * モデルの登録
 * 
 * \param key		マップのキー
 * \param fileName	ファイル名
 */
void ModelManager::RegisterModel(std::string key, const wchar_t* fileName)
{
	m_factory.emplace(key, fileName);
}

void ModelManager::CreateModel(ID3D11Device1* device)
{
	// コンテナのクリア
	m_models.clear();

	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");   // テクスチャーが貼ってある場合は設定する

	for (auto& file : m_factory) {
		auto model = Model::CreateFromSDKMESH(device, file.second, fx);

		m_models.emplace(file.first, std::move(model));
	}
}
