/*****************************************************************//**
 * \file   ResourceManager.cpp
 * \brief  リソース管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "ResourceManager.h"

/**
 * \brief マネージャーの作成
 * 
 */
void ResourceManager::CreateManager()
{
	m_modelManager = std::make_unique<ModelManager>();
}

/**
 * \brief リソースの作成
 * 
 * \param device
 */
void ResourceManager::CreateResources(ID3D11Device1* device)
{
	m_modelManager->CreateModel(device);
}
