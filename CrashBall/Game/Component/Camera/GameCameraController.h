/*****************************************************************//**
 * \file   GameCameraController.h
 * \brief  ゲームカメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "TargetCameraController.h"

/**
 * @brief ゲームカメラ操作コンポーネント
 */
class  GameCameraController : public TargetCameraController 
{

	friend class ObjectInspectorGui;

	//パラメータの宣言 -------------------------------------------------
private:

	float m_rotateAngleRad = 0.0f;	// 回転角度

	// データメンバの宣言 -----------------------------------------------
private:

	// ターゲットカメラコンポーネントのキャッシュ
	TargetCameraController* m_targetCamera = nullptr;		

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	GameCameraController() = default;

	// コンストラクタ
	GameCameraController(IGameObject* gameObejct);

	// コピーコンストラクタ
	GameCameraController(
		IGameObject* gameObject,
		const GameCameraController& other
	);

	// デストラクタ
	~GameCameraController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// トランスフォームを追尾
	void TargetingTransform();

	// 取得/設定
public:

	// 内部実装
private:

	// JsonConverter
private:

	friend void to_json(nlohmann::json& j, const GameCameraController& gameCameraController);
	friend void from_json(const nlohmann::json& j, GameCameraController& gameCameraController);

	// 演算子オーバーロード
public:

	void operator=(const GameCameraController& other)
	{
		m_rotateAngleRad = other.m_rotateAngleRad;
	}
};
