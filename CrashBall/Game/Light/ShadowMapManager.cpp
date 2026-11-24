/*****************************************************************//**
 * \file   ShadowMapManager.h
 * \brief  シャドウマップ管理クラス
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "ShadowMapManager.h"

#include "Game/RenderTexture/RenderTexture.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ShadowMapManager::ShadowMapManager()
{
	m_cameraObject	= std::make_unique<GameObject>();
 	m_cameraTrans	= m_cameraObject->AddComponent<Transform>();
	m_camera		= m_cameraObject->AddComponent<OrthgraphicCamera>();

	m_cameraTrans->SetWorldPosition(-m_lightDirection * 100.0f);

	m_cameraObject->Awake();
	m_camera->SetSize(SimpleMath::Vector2(180.0f, 180.0f));
	m_camera->SetWindowSizeResource();
	m_camera->LookAt(SimpleMath::Vector3::Zero);
	m_cameraObject->Start(GameContext{});

	m_shadowMap = RenderTexture::CreateRenderTexture();
	m_shadowMap->SizeResources(4096.0f * 2.0f, 4096.0f * 2.0f);
	m_shadowMap->SetCamera(m_camera);

	m_shadowMap->m_isDepth = true;
}
