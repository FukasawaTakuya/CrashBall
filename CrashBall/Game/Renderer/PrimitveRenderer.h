// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Camera.h"
// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  PrimitiveManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;		// プリミティブバッチ

	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;								// ベーシックエフェクト

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	PrimitiveManager() = default;
	PrimitiveManager(PrimitiveManager&) = delete;
	PrimitiveManager& operator= (const PrimitiveManager&) = delete;

	// デストラクタ
	~PrimitiveManager() = default;

	// 操作
public:
	// インスタンスの取得
	static PrimitiveManager& Instance() {
		static PrimitiveManager instance;
		return instance;
	}

	void CreateResource(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::SimpleMath::Matrix projMat
	);

	void ApplyEffect(Camera* camera);

	void DrawBegin()	{ m_primitiveBatch->Begin(); }
	void DrawEnd()		{ m_primitiveBatch->End(); }

	void DrawLine(
		DirectX::VertexPositionColor v1,
		DirectX::VertexPositionColor v2
	);


	// 取得/設定
public:

	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* 
		GetPrimitiveBatch() { return m_primitiveBatch.get(); }

	DirectX::BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }

	ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }
	// 内部実装
private:

};
