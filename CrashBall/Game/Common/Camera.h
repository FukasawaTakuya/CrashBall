/*****************************************************************//**
 * \file   Camera.h
 * \brief  カメラクラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once


 /**
 * \brief カメラクラス
 */
class  Camera {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr int WIDTH = 1280;

	static constexpr int HEIGHT = 720;

	static constexpr DirectX::SimpleMath::Vector3 OFFSET = { 0.0f, 4.5f, 12.0f };	// オフセット

	static constexpr float ROTATE_LIMIT = 70.0f;			// 回転の限界値


	// データメンバの宣言 -----------------------------------------------
protected:

	DirectX::SimpleMath::Vector3 m_eye;				// 視点
	DirectX::SimpleMath::Vector3 m_target;			// 注視点
	DirectX::SimpleMath::Vector3 m_up;				// 上方向
	DirectX::SimpleMath::Vector3 m_right;			// 前方向
	DirectX::SimpleMath::Vector3 m_forward;			// 右方向
	DirectX::SimpleMath::Matrix  m_projMat;			// 射影行列
	DirectX::SimpleMath::Matrix  m_viewMat;			// ビュー行列
	DirectX::SimpleMath::Vector3 m_offset;			// オフセット
	
	float m_zoomRate = 1.0f;						// 拡大倍率

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Camera();

	// デストラクタ
	~Camera();

	// 操作
public:

	// 初期化
	void Initialize(const DirectX::SimpleMath::Matrix& projMat);

	// カメラのX軸回転
	void RotateX(float angle);

	// カメラのY軸回転
	void RotateY(float angle);

	// ズーム
	void Zoom(float value);

	// 追従
	void FollowCamera(DirectX::SimpleMath::Vector3 pos);

	// 取得 / 設定
public:

	// 注視点の取得
	DirectX::SimpleMath::Vector3 GetTarget();

	// 視点の取得
	DirectX::SimpleMath::Vector3 GetEye();

	// Rayの取得
	DirectX::SimpleMath::Vector3 GetRay(float x, float y);

	// ビュー行列の取得
	DirectX::SimpleMath::Matrix GetViewMat();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix GetProjMat();

	// 前方向(XZ平面)のベクトルの取得
	DirectX::SimpleMath::Vector3 GetForward();

	DirectX::SimpleMath::Vector3 GetRight();


	// 注視点のセット
	void SetTarget(DirectX::SimpleMath::Vector3 target);

	// 視点のセット
	void SetEye(DirectX::SimpleMath::Vector3 eye);

	// カメラのセット
	void SetCamera(
		const DirectX::SimpleMath::Vector3& eye,
		const DirectX::SimpleMath::Vector3& target);

	// 内部実装
private:

	void UpdataView();
};
