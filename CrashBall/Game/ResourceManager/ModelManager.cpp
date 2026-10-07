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

	for (auto& file : std::filesystem::directory_iterator("Resources/Models"))
	{
		EffectFactory fx(device);
		fx.SetDirectory(L"Resources/Models"); // <- ddsのフォルダ

		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"Models") + 7;

		std::wstring ws = path.substr(end, 8).c_str();
		if (ws == L".sdkmesh")
		{
			// モデルを作成
			std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, path.c_str(), fx);

			std::wstring key = path.substr(start, end - start);
			// コンテナに追加
			m_models.emplace(Utility::ConvertToMultiByteChar(key), std::move(model));
		}
	}

	for (auto& file : std::filesystem::directory_iterator("Resources/CMO"))
	{
		EffectFactory fx(device);
		fx.SetDirectory(L"Resources/CMO"); // <- ddsのフォルダ

		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"CMO") + 4;

		std::wstring ws = path.substr(end, 4).c_str();
		if (ws == L".cmo")
		{
			// モデルを作成
			std::unique_ptr<Model> model = Model::CreateFromCMO(device, path.c_str(), fx);

			std::wstring key = path.substr(start, end - start);
			// コンテナに追加
			m_models.emplace(Utility::ConvertToMultiByteChar(key), std::move(model));
		}
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
