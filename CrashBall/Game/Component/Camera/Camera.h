#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/Transform.h"

/**
 * @brief カメラ
 */
class  Camera : public Component {

	// メンバ変数の宣言 -------------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_right;			// 前方向
	DirectX::SimpleMath::Vector3 m_forward;			// 右方向

	DirectX::SimpleMath::Matrix  m_view;			// ビュー行列

	DirectX::SimpleMath::Matrix* m_proj = nullptr;	// プロジェクション行列

	Transform* m_transform = nullptr;				// トランスフォームのキャッシュ

	// プロパティの設定
	BeginProperty()
	EndProperty()

		// コンポーネント名の設定
	SetCompName("Camera")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Camera(IGameObject* gameObject) : Component(gameObject) {};

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

	//
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

	// 前方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetForward() const
	{
		DirectX::SimpleMath::Vector3 forward = m_forward;
		forward.y = 0.0f;
		forward.Normalize();
		return forward;
	}

	// 右方向(XZ平面)ベクトルの取得
	DirectX::SimpleMath::Vector3 GetRight() const
	{
		DirectX::SimpleMath::Vector3 right = m_right;
		right.y = 0.0f;
		right.Normalize();
		return right;
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