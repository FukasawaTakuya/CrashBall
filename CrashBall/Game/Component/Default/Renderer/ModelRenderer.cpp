/*****************************************************************//**
 * \file   ModelRenderer.cpp
 * \brief  モデル描画クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRenderer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ModelRenderer::ModelRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
	m_transform = GetGameObject()->GetComponent<Transform>();
}

/**
 * \brief デストラクタ.
 * 
 */
ModelRenderer::~ModelRenderer()
{
}

/**
 * \brief モデルの描画
 * 
 * \param 描画管理
 * \param ワールド行列
 */
void ModelRenderer::Render(IModelRendererManager* rendererManager)
{
	if (m_pModel == nullptr) return;

	// 描画命令の登録
	if(m_pModel != nullptr)
		rendererManager->RegisterRenderCommand(m_pModel, m_transform->GetWorld());
}

/**
 * \brief ディフーズカラーの設定
 * 
 * \param color 色
 */
void ModelRenderer::SetDiffuseColor(const DirectX::XMVECTORF32& color)
{
	m_pModel->UpdateEffects(
		[&](IEffect* effect) {

			BasicEffect* basic = dynamic_cast<BasicEffect*>(effect);
			if (basic)
			{
				basic->SetDiffuseColor(color);
			}
		});
}

