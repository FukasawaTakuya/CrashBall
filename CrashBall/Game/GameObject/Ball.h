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
#include "Game/Component/Ball/BallController.h"

 /**
 * \brief ボールクラス
 */
class Ball : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	BallController* m_ballController = nullptr;	// ボール操作コンポーネントのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Ball(float radius, ObjectTag tag = ObjectTag::Defaut);

	Ball(json* data, ObjectTag tag = ObjectTag::Defaut);

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

	// パラメータの書き込み
	virtual void SaveParam() override;

	// 初期化用のパラメータの書き込み
	virtual void SaveInitParam() override;

	// データの再読み込み
	virtual void ReloadJson() override;

	// 取得/設定
public:

	// 内部実装
private:

};
