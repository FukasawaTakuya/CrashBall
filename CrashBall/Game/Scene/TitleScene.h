/*****************************************************************//**
 * \file   TitleScene.h
 * \brief  タイトルシーン
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Scene.h"
#include "Game/Camera/TitleCamera.h"
#include "Game/GameObject/Object3D.h"
#include "Game/GameObject/Stage.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/GameObject/UIObject/Object2D.h"
#include "Game/GameObject/UIObject/Button.h"
#include "Game/GameObject/UIObject/TitleLogo.h"

/**
 * @brief タイトルシーン
 */
class  TitleScene : public Scene {

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<TitleCamera> m_camera;		// カメラ
	std::unique_ptr<Player>		 m_player;		// プレイヤー
	std::unique_ptr<Stage>		 m_stage;		// ステージ
	std::unique_ptr<TitleLogo>	 m_titleLogo;	// タイトルロゴ
	std::unique_ptr<Button>		 m_startButton;	// スタートボタン

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleScene(
		ISceneController* pSceneController,
		IJsonDataManager* jsonDataManager);

	// デストラクタ
	~TitleScene();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// デバイス依存のリソース作成
	void CreateDeviceResources(const ResourceContext& resourceContext) override;

	// ウインドウサイズ依存のリソース作成
	void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj) override;

	// パラメータの書き込み
	void SaveParam() override;

	// パラメータの再読み込み
	void ReloadParam() override;

	// カメラの取得
	ICamera* GetCamera() const override
	{
		return m_camera->GetComponent<TargetCamera>();
	}


	// 取得/設定
public:

	// 内部実装
private:

};
