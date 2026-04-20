// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "GameObject.h"
#include "Game/Component/Collider.h"
#include "Game/Component/RigitBody.h"
#include "Game/Component/Transform.h"

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

	DirectX::Model* m_pModel = nullptr;						// モデル

	DirectX::SimpleMath::Quaternion m_rotateValue;	// クオータニオン rotatevalue

	bool m_isGround;

	RigitBody* m_rigitbody;
	Transform* m_transform;
	Sphere* m_collider;

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

	void Draw(DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view);

	void Accelarate(DirectX::SimpleMath::Vector3 accel);

	// 移動
	void Move();

	void Rotate();

	// 取得/設定
public:

	bool GetIsGround() { return m_isGround; }

	void SetModel(DirectX::Model* pModel) { m_pModel = pModel; }

	void SetIsGround(bool flag) { m_isGround = flag; }

	// 内部実装
private:

};
