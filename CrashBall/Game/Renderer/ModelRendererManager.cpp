/*****************************************************************//**
 * \file   ModelRendererManager.cpp
 * \brief  モデル描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRendererManager.h"
#include "Game/Common/CommonResources.h"

using namespace DirectX;

/**
 * \brief 描画命令の登録.
 * 
 * \param 描画命令
 */
void ModelRendererManager::RegisterRenderCommand(const ModelRenderCommand& renderCommand)
{
	m_renderCommandList.emplace_back(renderCommand);
}

/**
 * \brief 描画命令のクリア
 * 
 */
void ModelRendererManager::ClearCommandList()
{
	m_renderCommandList.clear();
}

/**
 * \brief 描画
 * 
 * \param context コンテキスト
 * \param state コモンステート
 * \param camera カメラのポインタ
 */
void ModelRendererManager::Render(
	ID3D11DeviceContext1* context,
	DirectX::CommonStates* state,
	Camera* camera)
{
	SimpleMath::Matrix view = camera->GetViewMat();
	SimpleMath::Matrix proj = camera->GetProjMat();

	for (auto& renderCommand : m_renderCommandList)
	{
		renderCommand.pModel->Draw(context, *state, renderCommand.world, view, proj);
	}
}
