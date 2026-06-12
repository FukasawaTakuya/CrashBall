/*****************************************************************//**
 * \file   FloorMeshGaugeController.h
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Default/SpriteRenderer.h"
#include "Default/RectTransform.h"
#include "Default/TextRenderer.h"
#include "IFloorMeshGetter.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Common/Screen.h"


/**
 * @brief 
 */
class  FloorMeshGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr DirectX::SimpleMath::Vector2 POSITION = { Screen::CENTER_X, 50.0f };	// 描画位置


	// データメンバの宣言 -----------------------------------------------
private:

	SpriteRenderer* m_spriteRenderer = nullptr;		// スプライト描画コンポーネント

	TextRenderer* m_textRenderer = nullptr;

	RectTransform* m_rectTransfrom = nullptr;		// トランスフォーム

	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	IGameObject* m_pPalyerMeshBar = nullptr;

	IGameObject* m_pEnemyMeshBar = nullptr;

	SpriteRenderer* m_playerBarSpriteRenderer	= nullptr;
	SpriteRenderer* m_enemyBarSpriteRenderer	= nullptr;
	RectTransform* m_playerBarRectTransform		= nullptr;
	RectTransform* m_enemyBarRectTransform		= nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FloorMeshGaugeController(IGameObject* gameObject);

	// デストラクタ
	~FloorMeshGaugeController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();

	// 取得/設定
public:

	//  床メッシュ取得コンポーネントの設定
	void SetFloorMeshGetter(IFloorMeshGetter* floorMeshGetter)
	{
		m_floorMeshGetter = floorMeshGetter;
	}

	void SetContext(
		IFloorMeshGetter* floorMeshGetter,
		IGameObject* pPlayerMeshBar,
		IGameObject* pEnemyMeshBar);

	// 内部実装
private:

};