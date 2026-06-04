/*****************************************************************//**
 * \file   SpriteRendererManager.h
 * \brief  スプライト描画管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/ISpriteRendererManager.h"


/**
 * @brief スプライト描画管理クラス
 */
class  SpriteRendererManager : public ISpriteRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	// スプライトバッチ

	std::vector<SpriteRenderCmd> m_renderCommad;			// 描画命令コンテナ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRendererManager();

	// デストラクタ
	~SpriteRendererManager();

	// 操作
public:

	void Reder();

	// 描画命令の登録
	void RegisterRenderCommand(
		ID3D11ShaderResourceView* pSprite,
		const RECT rect,
		int orderInLayer = 0dddd,
		const DirectX::XMVECTORF32 color = DirectX::Colors::White) override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// スプライトバッチの作成
	void Create(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};
