/*****************************************************************//**
 * \file   ModelManager.cpp
 * \brief  モデル管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelManager.h"

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
 * \brief ファイル名を登録
 * 
 * \param key　キー
 * \param fileName	ファイル名
 */
void ModelManager::RegisterFile(
	std::string key, 
	const std::wstring& fileName)
{
	m_files.emplace(key, fileName);
}

/**
 * \brief モデルの生成
 * 
 * \param device　デバイス
 */
void ModelManager::CreateModel(ID3D11Device1* device)
{
	m_models.clear();

	for (auto& file : m_files) {

		EffectFactory fx(device);
		// テクスチャのパスを設定
		fx.SetDirectory(L"Resources/Models");

		// モデルを作成
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, file.second.c_str(), fx);
		// コンテナに追加
		m_models.emplace(file.first, std::move(model));
	}
}

/**
 * \brief モデルの取得
 * 
 * \param key キー
 * \return モデル
 */
DirectX::Model* ModelManager::GetModel(const std::string& key)
{
	auto it = m_models.find(key);

	if (it != m_models.end())
	{
		return it->second.get();
	}
	else return nullptr;
}
