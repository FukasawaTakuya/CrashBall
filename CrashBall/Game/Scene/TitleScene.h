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

/**
 * @brief タイトルシーン
 */
class  TitleScene : public Scene {

	// クラス定数の宣言 -------------------------------------------------
private:

	// タイトルロゴの初期位置
	static constexpr DirectX::SimpleMath::Vector2 TITLE_INIT_POS
		= DirectX::SimpleMath::Vector2(320.0f, 220.0f);

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<TitleCamera> m_camera;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Stage> m_stage;
	std::unique_ptr<Object2D> m_titleSprite;
	std::unique_ptr<Button> m_startButton;

	RectTransform* m_titleSpriteTransform = nullptr;

	float m_radian = 0.0f;

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
