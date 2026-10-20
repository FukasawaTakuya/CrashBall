/*****************************************************************//**
 * \file   MiniMap.h
 * \brief  ミニマップ
 *
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "MiniMap.h"

#include "Game/RenderTexture/RenderTexture.h"

RegisterComponent(MiniMap)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
MiniMap::MiniMap(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief デストラクタ
 * 
 */
MiniMap::~MiniMap()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void MiniMap::Awake()
{
	// レンダーテクスチャの作成
	m_renderTextrue = RenderTexture::CreateRenderTexture();

	// サイズの設定
	m_renderTextrue->SizeResources(m_size, m_size);

	// カメラの設定
	m_renderTextrue->SetCamera(m_pSubCamera);

	// コンポーネントのキャッシュの取得
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MiniMap::Start(const GameContext& gameContext)
{
	m_spriteRenderer->SetSize(m_renderTextrue->GetWidth(), m_renderTextrue->GetHeight());
	m_spriteRenderer->SetSprite(m_renderTextrue->GetShaderResourceView());
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MiniMap::Update(const GameContext& gameContext)
{
	// カメラの前方向に合わせて回転
	SimpleMath::Vector3 forward = SimpleMath::Vector3::Forward;
	float dot = forward.Dot(m_pMainCamera->GetHorizontalForward());

	// 180度を越えたら回転方向を反転
	float cross = forward.Cross(m_pMainCamera->GetHorizontalForward()).y;
	cross = cross > 0.0f ? 1.0f : -1.0f;
	m_rectTransform->SetLocalRotate(std::acos(dot) * cross);
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void MiniMap::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->SetSprite(m_renderTextrue->GetShaderResourceView());
}

/**
 * \brief 終了処理
 * 
 */
void MiniMap::Finalize()
{
	// レンダーテクスチャの削除
	RenderTexture::DeleteRenderTexture(m_renderTextrue);
}
