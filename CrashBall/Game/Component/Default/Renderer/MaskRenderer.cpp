#include "pch.h"
#include "MaskRenderer.h"

RegisterComponent(MaskRenderer)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
MaskRenderer::MaskRenderer(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void MaskRenderer::Awake()
{
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_modelRender = GetGameObject()->GetComponent<ModelRenderer>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MaskRenderer::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MaskRenderer::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void MaskRenderer::Render(const RenderContext& renderContext)
{
	renderContext.modelRendererManager->RegisterMaskRenderCommand(
		m_modelRender->GetModel(),
		m_modelRender->GetVertexShader(),
		m_modelRender->GetPixelShader(),
		m_transform->GetWorld());
}
