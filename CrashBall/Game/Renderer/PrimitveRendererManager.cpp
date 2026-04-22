/*****************************************************************//**
 * \file   PrimitveRendererManager.cpp
 * \brief  プリミティブ描画管理クラスに関するソースファイル
 * 
 * \author it252184
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "PrimitveRendererManager.h"
#include "Game/Common/CommonResources.h"

using namespace DirectX;

/**
 * \brief リソースの作成.
 * 
 * \param device
 * \param context
 * \param projMat
 */
void PrimitiveRendererManager::CreateResource(
	ID3D11Device1* device,
	ID3D11DeviceContext1* context,
    DirectX::SimpleMath::Matrix projMat
)
{
    // プリミティブバッチの作成
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
    // ベーシックエフェクトの作成
    m_basicEffect = std::make_unique<BasicEffect>(device);

    // 射影行列のセット
    m_basicEffect->SetProjection(projMat);
    m_basicEffect->SetVertexColorEnabled(true);

    // 入力レイアウトの設定
    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionColor>(
            device,
            m_basicEffect.get(),
            m_inputLayout.ReleaseAndGetAddressOf()));
}

/**
 * \brief 描画命令の登録.
 * 
 * \param drawCommand 描画命令
 */
void PrimitiveRendererManager::RegisterDrawCommand(const PrimitiveDrawCommand& drawCommand)
{
    m_drawCommand.emplace_back(drawCommand);
}

/**
 * \brief 描画命令のクリア.
 * 
 */
void PrimitiveRendererManager::ClearCommandList()
{
    m_drawCommand.clear();
}

/**
 * \brief 描画.
 * 
 * \param pCamera カメラのポインタ
 */
void PrimitiveRendererManager::Draw(Camera* pCamera)
{
    auto context = CommonResources::Instance().GetContext();
    auto state = CommonResources::Instance().GetState();

    // ブレンドステートの設定（不透明）
    context->OMSetBlendState(state->AlphaBlend(), nullptr, 0xFFFFFFFF);
    // 深度バッファの設定（通常）
    context->OMSetDepthStencilState(state->DepthDefault(), 0);
    // カリングの設定（カリングなし）
    context->RSSetState(state->CullClockwise());

    // ビュー行列のセット
    m_basicEffect->SetView(camera->GetViewMat());
    // ワールド行列のセット
    m_basicEffect->SetWorld(SimpleMath::Matrix::Identity);

    // コンテキストの適用
    m_basicEffect->Apply(context);
    // 入力レイアウトのセット
    context->IASetInputLayout(m_inputLayout.Get());

    // 描画開始
    m_primitiveBatch->Begin();

    // 描画命令の実行
    for (auto& drawCommand : m_drawCommand)
    {
        m_primitiveBatch->Draw(
            drawCommand.topology,
            drawCommand.vertices.data(),
            drawCommand.vertexCount
        );
    }

    // 描画終了
    m_primitiveBatch->End();
}