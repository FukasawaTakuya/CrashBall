/*****************************************************************//**
 * \file   Camera.h
 * \brief  カメラ
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Common/Screen.h"

/**
 * @brief カメラ
 */
class  Camera : public Component {

	// メンバ変数の宣言 -------------------------------------------------
protected:

	DirectX::SimpleMath::Vector3 m_forward;		// 右方向
	DirectX::SimpleMath::Vector3 m_up;			// 上方向
	DirectX::SimpleMath::Vector3 m_right;		// 前方向

	DirectX::SimpleMath::Matrix  m_view;		// ビュー行列

	DirectX::SimpleMath::Matrix m_proj;			// プロジェクション行列

	Transform* m_transform = nullptr;			// トランスフォームのキャッシュ

	float m_fov = DirectX::XMConvertToRadians(45.0f);
	float m_nearclip = 0.1f;
	float m_farclip = 200.0f;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_fov, PropertyType::Angle)
		AddProperty(m_nearclip, PropertyType::Float)
		AddProperty(m_farclip, PropertyType::Float)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Camera")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Camera(IGameObject* gameObject);

	// デストラクタ
	~Camera() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// ターゲットの方に向ける
	void LookAt(const DirectX::SimpleMath::Vector3& target);

	// ビュー行列の更新
	void UpdateView();

	// 取得/設定
public:

	// ビュー行列の取得
	DirectX::SimpleMath::Matrix GetView() const
	{
		return m_view;
	}

	// プロジェクション行列の取得
	DirectX::SimpleMath::Matrix GetProj() const
	{
		return m_proj;
	}

	// 前方向ベクトルの取得
	DirectX::SimpleMath::Vector3 GetForward() const
	{
		return m_forward;
	}

	// 右方向ベクトルの取得
	DirectX::SimpleMath::Vector3 GetRight() const
	{
		return m_right;
	}

	// 前方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetHorizontalForward() const
	{
		DirectX::SimpleMath::Vector3 forward = m_forward;
		forward.y = 0.0f;
		forward.Normalize();
		return forward;
	}

	// 右方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetHorizontalRight() const
	{
		DirectX::SimpleMath::Vector3 right = m_right;
		right.y = 0.0f;
		right.Normalize();
		return right;
	}

	// ビュー行列の設定
	void SetView(const DirectX::SimpleMath::Matrix& view)
	{
		m_view = view;
	}


	// プロジェクション行列の設定
	void SetProj(const DirectX::SimpleMath::Matrix& proj)
	{
		m_proj = proj;
	}

	// ウィンドウサイズ依存のリソースの設定
	virtual void SetWindowSizeResource() override
	{
		m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
			m_fov,
			Screen::GetAccept(),
			m_nearclip,
			m_farclip
		);
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