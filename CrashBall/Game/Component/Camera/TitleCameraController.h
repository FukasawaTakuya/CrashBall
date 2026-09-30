/*****************************************************************//**
 * \file   TitleCameraController.h
 * \brief  タイトルカメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "TargetCameraController.h"


/**
 * @brief 基底タイトルカメラ操作コンポーネント
 */
class  TitleCameraController : public TargetCameraController
{
	// メンバ変数の宣言 -----------------------------------------------
private:

	// 1秒間の回転量
	float m_rotateAngeleRad = 0.0f;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_baseOffset, PropertyType::Vector3)
		AddProperty(m_rotateAngeleRad, PropertyType::Float)
		AddProperty(m_targetTransform, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("TitleCameraController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:


	// コンストラクタ
	TitleCameraController(IGameObject* gameObject);

	// デストラクタ
	~TitleCameraController() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}

	// JsonConverter
private:

	friend void from_json(const json& j, TitleCameraController& titleCameraController);
	friend void to_json(json& j, const TitleCameraController& titleCameraController);
};
