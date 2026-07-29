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


/**
 * @brief ターゲットカメラコンポーネント
 */
class  TargetCameraController : 
	public Component,
	public ICamera
{
	friend class ObjectInspectorGui;

public:

	// コンポーネント名 
	static constexpr char const* COMP_NAME = "TargetCameraController";

	// パラメータの宣言 -------------------------------------------------
protected:

	DirectX::SimpleMath::Vector3 m_baseOffset;	// 基準のオフセット

	// プロパティの設定
	BeginProperty()
		AddProperty(m_baseOffset, PropertyType::Vector3)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("TargetCameraController")


	// データメンバの宣言 -----------------------------------------------
protected:

	DirectX::SimpleMath::Vector3 m_up;				// 上方向
	DirectX::SimpleMath::Vector3 m_right;			// 前方向
	DirectX::SimpleMath::Vector3 m_forward;			// 右方向

	mutable DirectX::SimpleMath::Matrix  m_view;	// ビュー行列

	DirectX::SimpleMath::Quaternion m_offsetRotate;	// オフセット分の回転

	DirectX::SimpleMath::Vector3 m_offset;	// オフセット
	float m_zoomRate = 1.0f;				// オフセットの拡大倍率

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	const Transform* m_targetTransform = nullptr;	// ターゲットのトランスフォーム

	// 変更フラグ
	mutable bool m_isDirty = false;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	TargetCameraController() = default;

	// コンストラクタ
	TargetCameraController(
		IGameObject* gameObject,
		const DirectX::SimpleMath::Vector3& offest = DirectX::SimpleMath::Vector3::One);

	// コピーコンストラクタ
	TargetCameraController(
		IGameObject* gameObejct,
		const TargetCameraController& other
	);

	// デストラクタ
	~TargetCameraController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

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

	// ビュー行列の取得
	DirectX::SimpleMath::Matrix GetView() const override
	{
		// 変更があればビュー行列を更新
		if (m_isDirty)
		{
			UpdateView();
			m_isDirty = false;
		}

		return m_view;
	}

	// 前方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetForward() const override
	{
		DirectX::SimpleMath::Vector3 forward = m_forward;
		forward.y = 0.0f;
		forward.Normalize();
		return forward;
	}

	// 右方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetRight() const override
	{
		DirectX::SimpleMath::Vector3 right = m_right;
		right.y = 0.0f;
		right.Normalize();
		return right;
	}

	// 上方向ベクトルの取得
	DirectX::SimpleMath::Vector3 GetUp() const
	{
		return m_up;
	}

	// ターゲットの設定
	void SetTargetTransform(const Transform* targetTransform)
	{
		m_targetTransform = targetTransform;
	}

	// 内部実装
private:

	// ビュー行列の更新(GetViewで呼ぶためconst)
	void UpdateView() const;

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
	friend void from_json(const nlohmann::json& j, TargetCameraController& targetCamera);
	friend void to_json(nlohmann::json& j, const TargetCameraController& targetCamera);

	// 演算子オーバーロード
public:

	void operator=(const TargetCameraController& other)
	{
		m_baseOffset = other.m_baseOffset;

		// オフセットからターゲット方向のベクトル
		DirectX::SimpleMath::Vector3 offsetDire = XMVector3Normalize(-m_baseOffset);
		// 初期回転
		m_offsetRotate = DirectX::SimpleMath::Quaternion::FromToRotation(
			DirectX::SimpleMath::Vector3::Forward, offsetDire);
	}
};
