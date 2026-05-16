/*****************************************************************//**
 * \file   ModelRenderer.cpp
 * \brief  モデル描画クラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRenderer.h"
#include "Game/Renderer/ModelRendererManager.h"

/**
 * \brief コンストラクタ.
 * 
 */
ModelRenderer::ModelRenderer()
{
}

/**
 * \brief デストラクタ.
 * 
 */
ModelRenderer::~ModelRenderer()
{
}

/**
 * \brief モデルの描画.
 * 
 * \param ワールド行列
 */
void ModelRenderer::Draw(const DirectX::SimpleMath::Matrix& world)
{
	if (m_pModel == nullptr) return;

	auto& modelManager = ModelRendererManager::Instance();

	// 描画命令の登録
	if(m_pModel != nullptr)
		modelManager.RegisterDrawCommand({ m_pModel, world });
}

/**
 * \brief モデルの設定
 * 
 * \param モデルのポインタ
 */
void ModelRenderer::SetModel(DirectX::Model* pModel)
{
	m_pModel = pModel;
}
