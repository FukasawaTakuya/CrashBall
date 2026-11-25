/*****************************************************************//**
 * \file   ModelRendererManager.cpp
 * \brief  モデル描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRendererManager.h"

#include "Game/RenderTexture/RenderTexture.h"

using namespace DirectX;

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
	const DirectX::SimpleMath::Color& diffuseColor,
	Shader* vertexShader,
	Shader* pixelShader,
	const DirectX::SimpleMath::Matrix& world)
{
	m_renderCommand.emplace_back(model, diffuseColor, vertexShader, pixelShader, world);
}

/**
 * \brief マスクへの描画命令の登録
 *
 * \param model モデル
 * \param vertexShader 頂点シェーダ
 * \param pixelShader　ピクセルシェーダ
 * \param world ワールド行列
 */
void ModelRendererManager::RegisterMaskRenderCommand(
	MyModel* model,
	Shader* vertexShader,
	Shader* pixelShader,
	const DirectX::SimpleMath::Matrix& world)
{
	m_maskRenderCommand.emplace_back(
		model, 
		DirectX::SimpleMath::Color{ 1.0f, 1.0f,1.0f, 1.0f }, 
		vertexShader, pixelShader, world);
}

/**
 * \brief 描画命令のクリア
 * 
 */
void ModelRendererManager::ClearRenderCommand()
{
	m_renderCommand.clear();
	m_maskRenderCommand.clear();
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
	const DirectX::SimpleMath::Matrix& proj,
	const DirectX::SimpleMath::Vector3& lightDire,
	const DirectX::SimpleMath::Matrix& lightView,
	const DirectX::SimpleMath::Matrix& lightProj,
	ID3D11ShaderResourceView* shadowMap)
{
	for (auto& renderCommand : m_renderCommand)
	{
		if (renderCommand.pModel		== nullptr ||
			renderCommand.vertexShader	== nullptr ||
			renderCommand.pixelShader	== nullptr) return;

		renderCommand.pModel->Draw(
			renderCommand.world, 
			view, 
			proj, 
			renderCommand.diffuseColor,
			renderCommand.vertexShader,
			renderCommand.pixelShader,
			lightDire,
			lightView,
			lightProj,
			shadowMap,
			state, 
			context);
	}
}


/**
 * \brief 深度のみの描画
 * 
 * \param context デバイスコンテキスト
 * \param state コモンステート
 * \param view ビュー行列
 * \param proj プロジェクション行列
 * \param lightDire 光の方向
 * \param lightView	光源視点のビュー行列
 * \param lightProj 光源視点のプロジェクション行列
 * \param shadowMap シャドウマップ
 */
void ModelRendererManager::RenderDepth(
	ID3D11DeviceContext1* context, 
	DirectX::CommonStates* state, 
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& renderCommand : m_renderCommand)
	{
		if (renderCommand.pModel == nullptr ||
			renderCommand.vertexShader == nullptr ||
			renderCommand.pixelShader == nullptr) return;

		renderCommand.pModel->Draw(
			renderCommand.world,
			view,
			proj,
			renderCommand.diffuseColor,
			renderCommand.vertexShader,
			nullptr,
			SimpleMath::Vector3::Zero,
			SimpleMath::Matrix::Identity,
			SimpleMath::Matrix::Identity,
			nullptr,
			state,
			context);
	}
}

/**
 * \brief マスクの描画
 *
 * \param context デバイスコンテキスト
 * \param state コモンステート
 * \param view ビュー行列
 * \param proj プロジェクション行列
 */
void ModelRendererManager::RenderMask(
	ID3D11DeviceContext1* context, 
	DirectX::CommonStates* state, const 
	DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj)
{
	m_mask->Begin(context);

	for (auto& renderCommand : m_maskRenderCommand)
	{
		if (renderCommand.pModel == nullptr ||
			renderCommand.vertexShader == nullptr ||
			renderCommand.pixelShader == nullptr) return;

		renderCommand.pModel->Draw(
			renderCommand.world,
			view,
			proj,
			renderCommand.diffuseColor,
			renderCommand.vertexShader,
			renderCommand.pixelShader,
			SimpleMath::Vector3::Zero,
			SimpleMath::Matrix::Identity,
			SimpleMath::Matrix::Identity,
			nullptr,
			state,
			context);
	}
}

/**
 * \brief マスクの作成
 * 
 */
void ModelRendererManager::CreateMask()
{
	m_mask = RenderTexture::CreateCustomRenderTexture(DXGI_FORMAT_R8_UNORM);
}
