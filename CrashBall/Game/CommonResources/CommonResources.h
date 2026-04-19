// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class CommonResources  {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11Device1*			m_device;
	ID3D11DeviceContext1*	m_context;
	DirectX::CommonStates*	m_state;


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:
	// コンストラクタ
	CommonResources() = default;

	CommonResources(const CommonResources&) = delete;

	CommonResources& operator=(const CommonResources) = delete;

	// デストラクタ
	~CommonResources() = default;

public:

	static CommonResources& Instance() {
		static CommonResources instance;
		return instance;
	}

	// 操作
public:

	void Initialize(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state
	);

	// 取得/設定
public:

	ID3D11Device1*			GetDevice()	{ return m_device; }
	ID3D11DeviceContext1*	GetContext(){ return m_context; }
	DirectX::CommonStates*	GetState()	{ return m_state; }

	// 内部実装
private:

};

