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
 * \brief	モデルの描画.
 * 
 * \param	ワールド行列
 */
void ModelRenderer::Draw(const DirectX::SimpleMath::Matrix& world)
{
	m_pModel->UpdateEffects([&](IEffect* pEffect)
		{
			BasicEffect* pBasicEffect = dynamic_cast<BasicEffect*>(pEffect);
            pBasicEffect->SetLightingEnabled(true);
		});


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
