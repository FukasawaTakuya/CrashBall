#pragma once

#include "Component.h"

#include "Game/Component/Collider/Sphere.h"
#include "Game/Component/RigidBody.h"
#include "Game/Component/Transform.h"
#include "Game/Component/ModelRenderer.h"
#include <Game/Context/GameContext.h>

/**
 * @brief ボール操作クラス
 */
class  BallController : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Quaternion m_angularVelocity;	// 角速度

	bool m_isGround = false;						// 地上フラグ

	Transform*		m_transform			= nullptr;		// トランスフォームのコンポーネント
	RigidBody*		m_rigidbody			= nullptr;		// 物理演算のコンポーネント
	Sphere*			m_sphereCollider	= nullptr;		// 球のコライダーのコンポーネント
	ModelRenderer*	m_renderer			= nullptr;		// モデル描画のコンポーネント

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	BallController();

	// デストラクタ
	~BallController();

	// 操作
public:

	void Initialize();

	void Update(GameContext gameContext);

	// 移動
	void Move();

	// 回転の加算
	void AddRotate();

	// 回転
	void Rotate();

	// 取得/設定
public:

	bool GetIsGround() const { return m_isGround; }

	void SetIsGround(bool flag) { m_isGround = flag; }


	// 内部実装
private:

};
