/*****************************************************************//**
 * \file   SkyboxRenderManager.cpp
 * \brief  スカイボックス描画管理クラス
 *
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "SkyboxRenderManager.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
SkyboxRenderManager::SkyboxRenderManager()
{
}

/**
 * \brief 描画命令の登録
 * 
 */
void SkyboxRenderManager::RegisterRenderCommand()
{
	m_isRender = true;
}


/**
 * \brief 描画命令のクリア
 * 
 */
void SkyboxRenderManager::ClearRenderCommand()
{
	m_isRender = false;
}


/**
 * \brief 描画
 * 
 * \param context コンテキスト
 * \param view ビュー行列
 * \param proj プロジェクション行列
 */
void SkyboxRenderManager::Render(
	ID3D11DeviceContext1* context, 
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj)
{
	if (m_cubemap != nullptr && m_isRender)
	{
		// スカイボックスの描画
		m_effect->SetView(view);
		m_effect->SetProjection(proj);
		m_sky->Draw(m_effect.get(), m_skyInputLayout.Get());
	}
}

/**
 * \brief スカイボックスの作成
 * 
 * \param device デバイス
 * \param context デバイスコンテキスト
 */
void SkyboxRenderManager::CreateSkybox(
	ID3D11Device1* device,
	ID3D11DeviceContext1* context)
{
	m_sky.reset();
	m_effect.reset();
	m_skyInputLayout.Reset();

	m_sky = GeometricPrimitive::CreateGeoSphere(context, 2.f, 3,
		false /*invert for being inside the shape*/);

	m_effect = std::make_unique<SkyboxEffect>(device);

	m_sky->CreateInputLayout(m_effect.get(),
		m_skyInputLayout.ReleaseAndGetAddressOf());
}
