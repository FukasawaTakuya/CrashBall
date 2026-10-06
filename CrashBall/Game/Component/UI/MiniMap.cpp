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
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MiniMap::Start(const GameContext& gameContext)
{
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();

	m_spriteRenderer->SetSize(m_renderTextrue->GetWidth(), m_renderTextrue->GetHeight());
	m_spriteRenderer->SetSprite(m_renderTextrue->GetShaderResourceView());

	m_pSubCamera->GetGameObject()->GetComponent<Transform>()->
		SetRotate(SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, XMConvertToRadians(-90.0f), 0.0f));
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void MiniMap::Update(const GameContext& gameContext)
{
	m_spriteRenderer->SetSprite(m_renderTextrue->GetShaderResourceView());
}

/**
 * \brief 終了処理
 * 
 */
void MiniMap::Finalize()
{
	RenderTexture::DeleteRenderTexture(m_renderTextrue);
}
