/*****************************************************************//**
 * \file   Ball.h
 * \brief  ボールクラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "GameObject.h"
#include "Game/Component/Collider/Sphere.h"
#include "Game/Component/RigidBody.h"
#include "Game/Component/Transform.h"
#include "Game/Component/ModelRenderer.h"
#include "Game/Component/BallController.h"

 /**
 * @brief ボールクラス
 */
class Ball : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	static constexpr float GRAVITY = 25.8f;			// 重力
	static constexpr float FRICTION = 0.992f;		// 摩擦係数

	// データメンバの宣言 -----------------------------------------------
protected:

	DirectX::SimpleMath::Quaternion m_angularVelocity;	// 角速度

	bool m_isGround = false;						// 地上フラグ

	RigidBody*		m_rigidbody		 = nullptr;		// 物理演算のコンポーネント
	Transform*		m_transform		 = nullptr;		// トランスフォームのコンポーネント
	Sphere*			m_sphereCollider = nullptr;		// 球のコライダーのコンポーネント
	ModelRenderer*	m_renderer		 = nullptr;		// モデル描画のコンポーネント

	BallController* m_ballController;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Ball(float radius, ObjectTag tag = ObjectTag::Defaut);

	// デストラクタ
	~Ball() = default;

	// 操作
public:

	// 初期化
	virtual void Initialize() override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

	// 描画
	virtual void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// 取得/設定
public:

	bool GetIsGround() const { return m_ballController->GetIsGround(); }

	void SetPosition(DirectX::SimpleMath::Vector3 position);

	// 内部実装
private:

};
