// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Collider.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  MeshFloor {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::Model* m_pModel;					// モデル
	DirectX::SimpleMath::Matrix m_rotate;		// 回転

	std::unique_ptr<Mesh> m_mesh;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MeshFloor();

	// デストラクタ
	~MeshFloor();

	// 操作
public:
	void Initialize();

	void Update(float elapsedTime);

	void Draw(DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view);

	void Rotate(DirectX::SimpleMath::Matrix rotate);

	void SetModel(DirectX::Model* pModel) { 
		m_pModel = pModel; 
	}


	// 取得/設定
public:

	Mesh* GetMesh() { return m_mesh.get(); }

	// 内部実装
private:

};
