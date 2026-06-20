/*****************************************************************//**
 * \file   Ball.h
 * \brief  ボールクラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "GameObject.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/BallController.h"

 /**
 * \brief ボールクラス
 */
class Ball : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	static constexpr float GRAVITY = 25.8f;		// 重力
	static constexpr float FRICTION = 1.0f;		// 摩擦係数(1.0fで１秒経ったら止まる)

	// データメンバの宣言 -----------------------------------------------
protected:

	BallController* m_ballController;	// ボール操作コンポーネントのキャッシュ

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

	// 内部実装
private:

};
