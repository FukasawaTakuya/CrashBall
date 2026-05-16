/*****************************************************************//**
 * \file   CommonResources.h
 * \brief  共通リソースに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

/**
 * @brief 共通リソース
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

	// 複数生成の禁止
	CommonResources(const CommonResources&) = delete;
	CommonResources& operator=(const CommonResources&) = delete;

	// デストラクタ
	~CommonResources() = default;

public:
	// インスタンスの取得
	static CommonResources& Instance() {
		static CommonResources instance;
		return instance;
	}

	// 操作
public:

	// 初期化
	void Initialize(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state
	)
	{
		m_device = device;
		m_context = context;
		m_state = state;
	}


	// 取得/設定
public:

	// デバイスの取得
	ID3D11Device1*			GetDevice()	{ return m_device; }
	// コンテキストの取得
	ID3D11DeviceContext1*	GetContext(){ return m_context; }
	// コモンステートの取得
	DirectX::CommonStates*	GetState()	{ return m_state; }

	// 内部実装
private:

};

