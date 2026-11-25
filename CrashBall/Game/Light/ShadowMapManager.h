/*****************************************************************//**
 * \file   ShadowMapManager.h
 * \brief  シャドウマップ管理クラス
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once
#include "ShadowMap.h"
#include "Game/GameObject/GameObject.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Camera/OrthgraphicCamera.h"

 /**
  * \brief シャドウマップ管理クラス
  */
class  ShadowMapManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_lightDirection = { 0.5f, -1.0f, 0.5f };	// 平行光源方向

	std::unique_ptr<GameObject> m_cameraObject;	// カメラコンポーネント保持用オブジェクト
	OrthgraphicCamera* m_camera;// カメラコンポーネント
	Transform* m_cameraTrans;	// カメラ用のトランスフォーム

	MyRenderTexture* m_shadowMap;// シャドウマップ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ShadowMapManager();

	// デストラクタ
	~ShadowMapManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// シャドウマップの取得
	ID3D11ShaderResourceView* GetShadowMap()
	{ 
		return m_shadowMap->GetDepthStencilSrv();
	}

	DirectX::SimpleMath::Matrix GetView()
	{
		return m_camera->GetView();
	}

	DirectX::SimpleMath::Matrix GetProj()
	{
		return m_camera->GetProj();
	}

	DirectX::SimpleMath::Vector3 GetLightDirection()
	{
		return m_lightDirection;
	}

	// 内部実装
private:

};
