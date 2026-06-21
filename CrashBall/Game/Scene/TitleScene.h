#pragma once

#include "Scene.h"
#include "Game/Camera/TitleCamera.h"
#include "Game/Component/Camera/TargetCamera.h"
#include "Game/GameObject/Object3D.h"
#include "Game/GameObject/Stage.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/GameObject/UIObject/Object2D.h"
/**
 * @brief 基底オブジェクト
 */
class  TitleScene : public Scene {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr DirectX::SimpleMath::Vector2 TITLE_INIT_POS
		= DirectX::SimpleMath::Vector2(320.0f, 220.0f);

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<TitleCamera> m_camera;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Stage> m_stage;
	std::unique_ptr<Object2D> m_titleSprite;

	RectTransform* m_titleSpriteTransform = nullptr;

	float m_radian = 0.0f;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleScene(ISceneController* pSceneController);

	// デストラクタ
	~TitleScene();

	// 操作
public:

	void Initialize();

	void Update(const GameContext& gameContext);

	void Draw(const RenderContext& renderContext);

	void Finalize();

	void CreateDeviceResources(const ResourceContext& resourceContext);

	void CreateWindowSizeResources(const DirectX::SimpleMath::Matrix& proj);

	ICamera* GetCamera() const
	{
		return m_camera->GetComponent<TargetCamera>();
	}


	// 取得/設定
public:

	// 内部実装
private:

};
