/*****************************************************************//**
 * \file   BallController.h
 * \brief  ボール操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

/**
 * \brief ボール操作コンポーネント
 */
class  BallController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float SCALE = 0.025f;

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Quaternion m_angularVelocity;	// 角速度

	bool m_isGround = false;							// 地上フラグ

	Transform*		m_transform			= nullptr;		// トランスフォームのコンポーネント
	RigidBody*		m_rigidbody			= nullptr;		// 物理演算のコンポーネント
	Sphere*			m_sphereCollider	= nullptr;		// 球のコライダーのコンポーネント
	ModelRenderer*	m_renderer			= nullptr;		// モデル描画のコンポーネント

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	BallController(IGameObject* gameObject);

	// デストラクタ
	~BallController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();

	// 移動
	void Move();

	// 回転の加算
	void AddRotate();

	// 回転
	void Rotate();

	// 取得/設定
public:

	// 地上フラグの取得
	bool GetIsGround() const { return m_isGround; }

	// 内部実装
private:

	// 地上フラグの設定
	void SetIsGround(bool flag) { m_isGround = flag; }
};
