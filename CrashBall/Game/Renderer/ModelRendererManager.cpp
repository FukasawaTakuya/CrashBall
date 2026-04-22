/*****************************************************************//**
 * \file   ModelRendererManager.cpp
 * \brief  モデル描画管理クラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "ModelRendererManager.h"
#include "Game/Common/CommonResources.h"

/**
 * \brief 描画命令の登録.
 * 
 * \param 描画命令
 */
void ModelRendererManager::RegisterDrawCommand(const ModelDrawCommand& drawCommand)
{
	m_drawCommandList.emplace_back(drawCommand);
}

/**
 * \brief 描画命令のクリア
 * 
 */
void ModelRendererManager::ClearCommandList()
{
	m_drawCommandList.clear();
}

/**
 * \brief 描画.
 * 
 * \param カメラ
 */
void ModelRendererManager::Draw(Camera* camera)
{
	auto context = CommonResources::Instance().GetContext();
	auto state = CommonResources::Instance().GetState();

	DirectX::SimpleMath::Matrix view = camera->GetViewMat();
	DirectX::SimpleMath::Matrix proj = camera->GetProjMat();

	for (auto& drawCommand : m_drawCommandList)
	{
		drawCommand.pModel->Draw(context, *state, drawCommand.world, view, proj);
	}
}
