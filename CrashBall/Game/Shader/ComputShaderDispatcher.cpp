/*****************************************************************//**
 * \file   ComputShaderDispatcher.h
 * \brief  コンピュートシェーダーのディスパッチ管理クラス
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "ComputShaderDispatcher.h"

/**
 * \brief ディスパッチ命令の登録
 * 
 * \param shader シェーダー
 * \param groupNum スレッドグループ数
 */
void ComputShaderDispatcher::RegisterDispatchCommand(
	Shader* shader, 
	const DirectX::SimpleMath::Vector3 groupNum)
{
	m_dispatchCommandList.emplace_back(shader, groupNum);
}

/**
 * \brief ディスパッチ
 * 
 * \param context デバイスコンテキスト
 */
void ComputShaderDispatcher::Dispatch(ID3D11DeviceContext1* context)
{
	for (auto& dispathCmd : m_dispatchCommandList)
	{
		dispathCmd.shader->UpdateSubResources(context);
		dispathCmd.shader->Bind(context);
		context->Dispatch(
			dispathCmd.groupNum.x,
			dispathCmd.groupNum.y,
			dispathCmd.groupNum.z);
		dispathCmd.shader->ReleaseBind(context);

		dispathCmd.shader->CopyResource(context);
	}

	m_dispatchCommandList.clear();
}
