/*****************************************************************//**
 * \file   StageController.h
 * \brief  ステージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "../Default/Component.h"
#include "IWallMeshGetter.h"
#include "IFloorMeshGetter.h"
#include "IPaintConsumer.h"

#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

/**
 * \brief ステージ操作コンポーネント
 */
class  StageController : 
	public Component,			// 基底コンポーネント
	public IWallMeshGetter,		// 壁メッシュ関連情報取得
	public IFloorMeshGetter,	// 床メッシュ関連情報取得
	public IPaintConsumer		// ペイント消費
{

	// パラメータの宣言 -------------------------------------------------
private:

	float m_floorNormalY;	// 床判定基準になる法線のY成分
	float m_floorCenterPosY;// 床判定基準になる面の中心のY座標

	// データメンバの宣言 -----------------------------------------------
private:

	
	Mesh* m_meshCollider;	// コンポーネントのキャッシュ

	std::vector<Triangle*> m_floorMesh;		// 床メッシュ
	std::vector<Triangle*> m_wallMesh;		// 壁メッシュ

	std::unordered_map<Triangle*, DirectX::XMVECTORF32> m_floorMeshColor;	// 床メッシュの色情報

	int m_playerMeshCount = 0;	// プレイヤーが塗った面の数

	int m_enemyMeshCount = 0;	// 敵が塗ったの面の数

	int m_normalMeshCount = 0;	// 何も塗られていない面の数

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	StageController() = default;

	// コピーコンストラクタ
	StageController(
		IGameObject* gameObject,
		const StageController& other);

	// デストラクタ
	~StageController();

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

	// ペイント消費
	void ConsumePaint(int consumePaintNum) override;


	// 取得/設定
public:

	// 壁メッシュの取得
	const std::vector<Triangle*>& GetWallMesh() const override
	{
		return m_wallMesh;
	}

	// プレイヤーが塗った面の数の取得
	int GetPlayerMeshCount() const override
	{
		return m_playerMeshCount;
	}

	// 敵が塗ったの面の数の取得
	int GetEnemyMeshCount() const override
	{
		return m_enemyMeshCount;
	}

	// 何も塗られていない面の数の取得
	int GetNormalMeshCount() const override
	{
		return m_normalMeshCount;
	}

	// 面の合計の取得
	int GetTotalMeshCount() const override
	{
		return m_floorMeshColor.size();
	}


	// 内部実装
private:

	// 面に色を塗る
	void PaintFace(Triangle* face, const DirectX::XMVECTORF32& color);

	// JsonConverter
private:
	friend void from_json(const json& j, StageController& stageController);
	friend void to_json(json& j, const StageController& stageController);

	// 
public:

	void operator=(const StageController& other)
	{
		float m_floorNormalY = other.m_floorNormalY;
		float m_floorCenterPosY = other.m_floorCenterPosY;
	}
};