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
	// メンバ変数の宣言 -----------------------------------------------
private:

	// ターゲットカメラコンポーネントのキャッシュ
	TargetCameraController* m_targetCamera = nullptr;

	float m_rotateAngleRad = 0.0f;	// 回転角度

	// プロパティの設定
	BeginProperty()
		AddProperty(m_baseOffset, PropertyType::Vector3)
		AddProperty(m_rotateAngleRad, PropertyType::Float)
		AddProperty(m_targetTransform, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("GameCameraController")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameCameraController(IGameObject* gameObejct);

	// デストラクタ
	~GameCameraController() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// トランスフォームを追尾
	void TargetingTransform();

	// 取得/設定
public:

	// 内部実装
private:

	// プロパティの取得
	const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	std::string GetCompName() const override
	{
		return m_compName;
	}

	// JsonConverter
private:

	friend void to_json(nlohmann::json& j, const GameCameraController& gameCameraController);
	friend void from_json(const json& j, GameCameraController& gameCameraController);

};
