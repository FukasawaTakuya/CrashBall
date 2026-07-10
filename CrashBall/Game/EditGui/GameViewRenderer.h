#pragma once


/**
 * \brief 基底オブジェクト
 */
class  GameViewRenderer {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// 描画領域
	RECT m_gameViewRect;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameViewRenderer();

	// デストラクタ
	~GameViewRenderer();

	// 操作
public:

	// 更新
	void Update(ID3D11ShaderResourceView* srv);

	// 取得/設定
public:

	// 描画領域の取得
	RECT GetGameViewRect() const
	{
		return m_gameViewRect;
	}

	// 内部実装
private:

};
