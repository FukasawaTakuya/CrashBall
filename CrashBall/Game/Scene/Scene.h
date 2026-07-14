/*****************************************************************//**
 * \file   Scene.h
 * \brief  基底シーン
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once
#include <string>

#include "Interface/ISceneChanger.h"
#include "Game/Json/IJsonDataManager.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Component/Camera/ICamera.h"

#include "Game/GameObject/GameObject.h"

/**
 * \brief 基底シーン
 */
class Scene {

	// データメンバの宣言 -----------------------------------------------
protected:

	ISceneChanger* m_pSceneManager;

	std::vector<GameObject*> m_gameObjects;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Scene(
		ISceneChanger* pSceneManager,
		IJsonDataManager* jsonDataManager);

	// デストラクタ
	virtual ~Scene() = default;

	// 操作
public:

	// 遷移時の処理
	virtual void OnEnter(
		const ResourceContext& resourceContext,
		const GameContext& gameContext
		) = 0;

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(const GameContext& gameContext) = 0;
	
	// 描画
	virtual void Render(const RenderContext& renderContext) = 0;

	// 終了処理
	virtual void Finalize() = 0;

	// デバイス依存のリソース作成
	virtual void CreateDeviceResources(const ResourceContext& resourceContext) = 0;

	// ウインドウサイズ依存のリソース作成
	virtual void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj) = 0;

	// パラメータの書き込み
	virtual void SaveParam() = 0;

	// パラメータの再読み込み
	virtual void ReloadParam() = 0;

	// 取得/設定
public:
	// カメラの取得
	virtual ICamera* GetCamera() const = 0;

	// ゲームオブジェクトの取得
	std::vector<GameObject*>* GetGameObjects()
	{
		return &m_gameObjects;
	}

	// 内部実装
protected:
	void ChangeScene(SceneID nextSceneID);
};
