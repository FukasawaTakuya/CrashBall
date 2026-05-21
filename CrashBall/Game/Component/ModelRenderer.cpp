/*****************************************************************//**
 * \file   ModelRenderer.cpp
 * \brief  モデル描画クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRenderer.h"

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
void ModelRenderer::Render(
	IModelRendererManager* rendererManager, 
	const DirectX::SimpleMath::Matrix& world)
{
	if (m_pModel == nullptr) return;

	// 描画命令の登録
	if(m_pModel != nullptr)
		rendererManager->RegisterRenderCommand({ m_pModel, world });
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
