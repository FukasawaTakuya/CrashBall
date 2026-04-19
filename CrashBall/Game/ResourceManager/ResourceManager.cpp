#include "pch.h"
#include "ResourceManager.h"

void ResourceManager::CreateManager()
{
	m_modelManager = std::make_unique<ModelManager>();
}

void ResourceManager::CreateResources(ID3D11Device1* device)
{
	m_modelManager->CreateModel(device);
}
