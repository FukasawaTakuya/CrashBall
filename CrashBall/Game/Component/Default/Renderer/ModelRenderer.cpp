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

RegisterComponent(ModelRenderer)

/**
 * \brief コンストラクタ.
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ModelRenderer::ModelRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void ModelRenderer::Awake()
{
	m_transform = GetGameObject()->GetComponent<Transform>();
}

/**
 * \brief モデルの描画
 * 
 * \param 描画管理
 * \param ワールド行列
 */
void ModelRenderer::Render(const RenderContext& renderContext)
{
	if(m_pModel != nullptr)
		renderContext.modelRendererManager->
		RegisterRenderCommand(
			m_pModel, 
			m_vertexShader.get(),
			m_pixelShader.get(),
			m_transform->GetWorld());
}