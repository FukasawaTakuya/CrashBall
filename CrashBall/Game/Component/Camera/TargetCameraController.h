/*****************************************************************//**
 * \file   TargetCameraController.h
 * \brief  ターゲットカメラコンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "ICamera.h"
#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Camera/Camera.h"


/**
 * @brief ターゲットカメラコンポーネント
 */
class  TargetCameraController : public Component
{
	// データメンバの宣言 -----------------------------------------------
protected:

	DirectX::SimpleMath::Quaternion m_offsetRotate;	// オフセット分の回転

	DirectX::SimpleMath::Vector3 m_baseOffset;	// 基準のオフセット
	DirectX::SimpleMath::Vector3 m_offset;		// オフセット
	float m_zoomRate = 1.0f;					// オフセットの拡大倍率

	Transform* m_transform	= nullptr;	// トランスフォームのキャッシュ
	Camera* m_camera		= nullptr;	// カメラのキャッシュ

	const Transform* m_targetTransform = nullptr;	// ターゲットのトランスフォーム

	// パラメータの宣言 -------------------------------------------------
protected:

	// プロパティの設定
	BeginProperty()
		AddProperty(m_baseOffset, PropertyType::Vector3)
		EndProperty()

		// コンポーネント名の設定
		SetCompName("TargetCameraController")


		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	TargetCameraController() = default;

	// コンストラクタ
	TargetCameraController(IGameObject* gameObject);

	// デストラクタ
	~TargetCameraController();

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 初期化
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// X方向の回転
	void RotateX(float angleRad);

	// Y方向の回転
	void RotateY(float angleRad);

	// オフセットのズーム
	void Zoom(float value);

	// トランスフォームを追尾
	void TargetingTransform();

	// 取得/設定
public:

	// ターゲットの設定
	void SetTargetTransform(const Transform* targetTransform)
	{
		m_targetTransform = targetTransform;
	}

	// 基準のオフセットの設定
	void SetBaseOffset(const DirectX::SimpleMath::Vector3& baseOffset)
	{
		m_baseOffset = baseOffset;
	}

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
};
