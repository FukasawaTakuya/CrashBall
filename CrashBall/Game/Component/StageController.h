#pragma once

#include "Default/Component.h"
#include "IWallMeshGetter.h"

#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/ModelRenderer.h"
#include "Game/Component/Default/Transform.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

/**
 * \brief ステージ操作コンポーネント
 */
class  StageController : public Component, public IWallMeshGetter {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float SCALE = 15.0f;	// スケール

	const XMVECTORF32 PLAYER_COLOR = DirectX::Colors::LightSkyBlue;	// プレイヤー床のの色
	const XMVECTORF32 ENEMY_COLOR = DirectX::Colors::LightPink;		// 敵の床の色

	// データメンバの宣言 -----------------------------------------------
private:

	
	Mesh* m_meshCollider;	// コンポーネントのキャッシュ

	std::vector<Triangle*> m_floorMesh;		// 床メッシュ
	std::vector<Triangle*> m_wallMesh;		// 壁メッシュ

	std::unordered_map<Triangle*, XMVECTORF32> m_floorMeshColor;	// 床メッシュの色情報

	int m_playerMeshCount = 0;	// プレイヤーの面の数

	int m_enemyMeshCount = 0;	// 敵の面の数

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	StageController(IGameObject* gameObject);

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


	// 取得/設定
public:

	// 壁メッシュの取得
	const std::vector<Triangle*>& GetWallMesh() const override
	{
		return m_wallMesh;
	}

	// 内部実装
private:

	// 面に色を塗る
	void PaintFace(Triangle* face, const XMVECTORF32& color);

};
