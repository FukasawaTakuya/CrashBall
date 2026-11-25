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
	// カメラの作成
	m_cameraObject	= std::make_unique<GameObject>();
 	m_cameraTrans	= m_cameraObject->AddComponent<Transform>();
	m_camera		= m_cameraObject->AddComponent<OrthgraphicCamera>();

	// 初期処理
	m_cameraObject->Awake();
	m_cameraTrans->SetWorldPosition(-m_lightDirection * 100.0f);
	m_camera->SetSize(SimpleMath::Vector2(CAMERA_SIZE, CAMERA_SIZE));
	m_camera->SetWindowSizeResource();
	m_camera->LookAt(SimpleMath::Vector3::Zero);
	m_cameraObject->Start(GameContext{});

	// シャドウマップの作成
	m_shadowMap = RenderTexture::CreateRenderTexture(true);
	m_shadowMap->SizeResources(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	m_shadowMap->SetCamera(m_camera);
}
