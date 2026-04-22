// 多重インクルードの防止 =====================================================
#pragma once


// ヘッダファイルの読み込み ===================================================
#include "GameObject.h"
#include "Game/Component/Collider.h"
#include "Game/Component/RigitBody.h"
#include "Game/Component/Transform.h"
#include "Game/Component/ModelRenderer.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class Ball : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	static constexpr float GRAVITY = 25.8f;			// 重力
	static constexpr float FRICTION = 0.99f;		// 摩擦係数

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Quaternion m_rotateValue;	// 回転値

	bool m_isGround;

	RigitBody*		m_rigitbody = nullptr;
	Transform*		m_transform = nullptr;
	Sphere*			m_collider	= nullptr;
	ModelRenderer*	m_renderer	= nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Ball(DirectX::SimpleMath::Vector3 pos, float radius);

	// デストラクタ
	~Ball() = default;

	// 操作
public:

	void Initialize();

	void Update(float elapsedTime);

	void Draw();

	// 移動
	void Move();

	void Rotate();

	// 取得/設定
public:

	bool GetIsGround() { return m_isGround; }

	void SetModel(DirectX::Model* pModel) { m_renderer->SetModel(pModel); }

	void SetIsGround(bool flag) { m_isGround = flag; }

	// 内部実装
private:

};
