/*****************************************************************//**
 * \file   Scene.h
 * \brief  基底シーン
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once
#include <string>


#include "ISceneController.h"
#include "Game/Json/IJsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Component/Camera/ICamera.h"

/**
 * \brief 基底シーン
 */
class Scene {

	// データメンバの宣言 -----------------------------------------------
protected:

	ISceneController* m_pSceneController;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	Scene(
		ISceneController* pSceneManager,
		IJsonDataManager* jsonDataManager);

	virtual ~Scene() = default;

	// 操作
public:

	virtual void Initialize() = 0;

	virtual void Update(const GameContext& gameContext) = 0;

	virtual void Render(const RenderContext& renderContext) = 0;

	virtual void Finalize() = 0;

	virtual void CreateDeviceResources(const ResourceContext& resourceContext) = 0;

	virtual void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj) = 0;

	// 取得/設定
public:
	virtual ICamera* GetCamera() const = 0;

	// 内部実装
protected:
	void ChangeScene(SceneID nextSceneID);
};
