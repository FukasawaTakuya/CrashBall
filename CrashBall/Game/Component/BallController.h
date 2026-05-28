#pragma once

#include "Component.h"

#include "Game/Component/Collider/Sphere.h"
#include "Game/Component/RigidBody.h"
#include "Game/Component/Transform.h"
#include "Game/Component/ModelRenderer.h"

/**
 * @brief ボール操作クラス
 */
class  BallController : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	static constexpr float GRAVITY = 25.8f;			// 重力
	static constexpr float FRICTION = 0.992f;		// 摩擦係数

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Quaternion m_angularVelocity;	// 角速度

	bool m_isGround = false;						// 地上フラグ

	RigidBody* m_rigidbody = nullptr;		// 物理演算のコンポーネント
	Transform* m_transform = nullptr;		// トランスフォームのコンポーネント
	Sphere* m_sphereCollider = nullptr;		// 球のコライダーのコンポーネント
	ModelRenderer* m_renderer = nullptr;		// モデル描画のコンポーネント



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	BallController();

	// デストラクタ
	~BallController();

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
