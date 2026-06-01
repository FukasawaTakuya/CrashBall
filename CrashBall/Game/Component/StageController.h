#pragma once

#include "Component.h"
#include "Game/Component/Collider/Mesh.h"
#include "Game/Component/ModelRenderer.h"
#include "Game/Component/Transform.h"
#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

/**
 * \brief ステージ操作コンポーネント
 */
class  StageController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float SCALE = 15.0f;	// スケール

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	Mesh* m_meshCollider = nullptr;

	std::vector<Triangle*> m_floorMesh;		// 床メッシュ
	std::vector<Triangle*> m_wallMesh;		// 壁メッシュ

	std::unordered_map<Triangle*, XMVECTORF32> m_floorMeshColor;	// 床メッシュの色情報

	int m_playerMeshCount = 0;

	int m_enemyMeshCount = 0;



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

	// 床メッシュの取得
	const std::vector<Triangle*>& GetFloorMesh()
	{
		return m_floorMesh;
	}

	// 壁メッシュの取得
	const std::vector<Triangle*>& GetWallMesh()
	{
		return m_wallMesh;
	}

	// 内部実装
private:

	// 面に色を塗る
	void PaintFace(Triangle* face, const XMVECTORF32& color);

};
