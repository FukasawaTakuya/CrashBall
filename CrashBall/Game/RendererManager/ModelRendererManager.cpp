/*****************************************************************//**
 * \file   ModelRendererManager.cpp
 * \brief  モデル描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRendererManager.h"

using namespace DirectX;

/**
 * \brief 描画命令の登録.
 * 
 * \param model
 * \param world
 */
void ModelRendererManager::RegisterRenderCommand(
	DirectX::Model* model,
	const DirectX::SimpleMath::Matrix& world)
{
	m_renderCommand.emplace_back(model, world);
}

/**
 * \brief 描画命令の登録
 * 
 * \param model モデル
 * \param vertexShader 頂点シェーダ
 * \param pixelShader　ピクセルシェーダ
 * \param world ワールド行列
 */
void ModelRendererManager::RegisterRenderCommand(
	MyModel* model,
	Shader* vertexShader,
	Shader* pixelShader,
	const DirectX::SimpleMath::Matrix& world)
{
	m_myrenderCommand.emplace_back(model,vertexShader, pixelShader, world);
}

/**
 * \brief 描画命令のクリア
 * 
 */
void ModelRendererManager::ClearRenderCommand()
{
	m_renderCommand.clear();
	m_myrenderCommand.clear();
}

/**
 * \brief 描画
 * 
 * \param context コンテキスト
 * \param state コモンステート
 * \param view ビュー行列
 * \param proj プロジェクション行列
 */
void ModelRendererManager::Render(
	ID3D11DeviceContext1* context,
	DirectX::CommonStates* state,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj
)
{
	//for (auto& renderCommand : m_renderCommand)
	//{
	//	if (renderCommand.pModel == nullptr) return;

	//	renderCommand.pModel->Draw(context, *state, renderCommand.world, view, proj);
	//}

	for (auto& renderCommand : m_myrenderCommand)
	{
		if (renderCommand.pModel == nullptr) return;

		renderCommand.pModel->Draw(
			renderCommand.world, 
			view, 
			proj, 
			renderCommand.vertexShader,
			renderCommand.pixelShader,
			state, 
			context);
	}
}
