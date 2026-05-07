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
			// pBasicEffect->SetLightingEnabled(true);
			// pBasicEffect->SetPerPixelLighting(true);
			   
			// pBasicEffect->SetLightEnabled(0, true);
			// pBasicEffect->SetLightEnabled(1, false);
			// pBasicEffect->SetLightEnabled(2, false);
			   
			// pBasicEffect->SetLightDirection(0, SimpleMath::Vector3(0.0f, -1.0f, -1.0f));
			   
			// pBasicEffect->SetDiffuseColor(SimpleMath::Vector3{ 1.0f, 1.0f, 1.0f });
			   
			// pBasicEffect->SetAmbientLightColor(SimpleMath::Vector3(0.3f, 0.3f, 0.3f));
		});


	auto& modelManager = ModelRendererManager::Instance();

	// モデルのポインタがnullでなければ描画命令登録
	if(m_pModel != nullptr)
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
