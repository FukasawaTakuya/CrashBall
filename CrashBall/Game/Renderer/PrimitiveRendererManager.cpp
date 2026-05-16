/*****************************************************************//**
 * \file   PrimitveRendererManager.cpp
 * \brief  プリミティブ描画管理クラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "PrimitiveRendererManager.h"
#include "Game/Common/CommonResources.h"

using namespace DirectX;

/**
 * \brief リソースの作成.
 * 
 * \param device デバイス
 * \param context コンテキスト
 * \param projMat 射影行列
 */
void PrimitiveRendererManager::CreateResource(
	ID3D11Device1* device,
	ID3D11DeviceContext1* context,
    DirectX::CommonStates* state,
    DirectX::SimpleMath::Matrix projMat
)
{
    // プリミティブバッチの作成
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionNormalColor>>(context);
    // ベーシックエフェクトの作成
    m_basicEffect = std::make_unique<BasicEffect>(device);

    // 射影行列のセット
    m_basicEffect->SetProjection(projMat);
    m_basicEffect->SetVertexColorEnabled(true);

    // ライティングの有効化
    m_basicEffect->SetLightingEnabled(true);

    // 入力レイアウトの設定
    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionNormalColor>(
            device,
            m_basicEffect.get(),
            m_inputLayout.ReleaseAndGetAddressOf()));

    // ブレンドステートの設定
    context->OMSetBlendState(state->Opaque(), nullptr, 0xFFFFFFFF);
    // カリングの設定
    context->RSSetState(state->CullClockwise());

}

/**
 * \brief 描画命令の登録.
 * 
 * \param drawCommand 描画命令
 */
void PrimitiveRendererManager::RegisterDrawCommand(PrimitiveDrawCommand drawCommand)
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

    // 深度バッファの設定
    context->OMSetDepthStencilState(state->DepthDefault(), 0);

    // ビュー行列のセット
    m_basicEffect->SetView(pCamera->GetViewMat());
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
        if (drawCommand.vertices.empty()) continue;

        m_primitiveBatch->Draw(
            drawCommand.topology,
            drawCommand.vertices.data(),
            drawCommand.vertices.size()
        );
    }

    // 描画終了
    m_primitiveBatch->End();
}