/*****************************************************************//**
 * \file   TargetCamera.h
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
class  TargetCamera : 
	public Component,
	public ICamera
{

	// クラス定数の宣言 -------------------------------------------------
private:


	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_up;				// 上方向
	DirectX::SimpleMath::Vector3 m_right;			// 前方向
	DirectX::SimpleMath::Vector3 m_forward;			// 右方向

	mutable DirectX::SimpleMath::Matrix  m_view;	// ビュー行列

	DirectX::SimpleMath::Vector3 m_forwardOffset;	// 前方向に直したオフセット
	DirectX::SimpleMath::Quaternion m_initRotate;	// 初期化用の回転


	DirectX::SimpleMath::Vector3 m_offset;	// オフセット
	float m_zoomRate = 1.0f;				// オフセットの拡大倍率

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	const Transform* m_targetTransform = nullptr;	// ターゲットのトランスフォーム

	// 変更フラグ
	mutable bool m_isDirty = false;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TargetCamera(
		IGameObject* gameObject,
		const DirectX::SimpleMath::Vector3& offest);

	// デストラクタ
	~TargetCamera();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 操作
public:

	// X方向の回転
	void RotateX(float angleRad);

	// Y方向の回転
	void RotateY(float angleRad);

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

	// ターゲットの設定
	void SetTargetTransform(const Transform* targetTransform)
	{
		m_targetTransform = targetTransform;
	}

	// 内部実装
private:

	// ビュー行列の更新(GetViewで呼ぶためconst)
	void UpdateView() const;
};
