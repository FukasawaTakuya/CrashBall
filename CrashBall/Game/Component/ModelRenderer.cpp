/*****************************************************************//**
 * \file   ModelRenderer.cpp
 * \brief  モデル描画クラスに関するソースファイル
 * 
 * \author it252184
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
 * \brief	モデルの描画.
 * 
 * \param	ワールド行列
 */
void ModelRenderer::Draw(const DirectX::SimpleMath::Matrix& world)
{
	auto& modelManager = ModelRendererManager::Instance();

	modelManager.RegisterDrawCommand({ m_pModel, world });
}

/**
 * \brief	モデルのセット.
 * 
 * \param	モデルのポインタ
 */
void ModelRenderer::SetModel(DirectX::Model* pModel)
{
	m_pModel = pModel;
}
