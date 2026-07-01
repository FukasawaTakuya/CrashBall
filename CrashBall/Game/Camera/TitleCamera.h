#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Camera/TitleCameraController.h"

/**
 * @brief タイトルカメラ
 */
class  TitleCamera : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// コントローラーコンポーネントのキャッシュ
	TitleCameraController* m_cameraController = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleCamera();

	// デストラクタ
	~TitleCamera();

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

	// パラメータの書き込み
	void SaveParam() override;

	// 初期化用のパラメータの書き込み
	void SaveInitParam() override;

	// データの再読み込み
	void ReloadParam() override;


	// 取得 / 設定
public:
	// 内部実装
private:

};
