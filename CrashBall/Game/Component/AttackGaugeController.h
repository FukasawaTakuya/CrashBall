/*****************************************************************//**
 * \file   AttackGaugeController.h
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/GameObject/IGameObject.h"
#include "Game/Context/GameContext.h"
#include "Default/SpriteRenderer.h"

#include "IFloorMeshGetter.h"
#include "PlayerStatusController.h"

/**
 * @brief 攻撃ゲージ操作コンポーネント
 */
class  AttackGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	const DirectX::XMVECTORF32 GAUGE_COLOR = DirectX::Colors::Yellow;	// プレイヤーの面の色
	const DirectX::XMVECTORF32 GAUGE_TRACK_COLOR = DirectX::Colors::Gray;


	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pAttackGauge		  = nullptr;	// 攻撃ゲージ
	IGameObject* m_pAttackGaugeTrack  = nullptr;	// 攻撃ゲージの土台

	SpriteRenderer* m_gaugeRenderer = nullptr;
	SpriteRenderer* m_gaugeTrackRenderer = nullptr;

	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	AttackGaugeController(
		IGameObject* gameObejct,
		IGameObject* pAttackGauge,
		IGameObject* pAttackGaugeTrack
	);

	// デストラクタ
	~AttackGaugeController();

	// 操作
public:

	void Initilize();

	void Update(const GameContext& gameContext);

	// 取得/設定
public:

	//  床メッシュ取得コンポーネントの設定
	void SetFloorMeshGetter(IFloorMeshGetter* floorMeshGetter)
	{
		m_floorMeshGetter = floorMeshGetter;
	}


	// 内部実装
private:

};
