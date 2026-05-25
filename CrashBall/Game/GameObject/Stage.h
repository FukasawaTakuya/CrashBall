#pragma once

#include "GameObject.h"
#include "Game/Component/Collider/Mesh.h"
#include "Game/Component/ModelRenderer.h"
#include "Game/Component/Transform.h"


/**
 * @brief ステージオブジェクト
 */
class  Stage : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	const float SCALE = 10.0f;								// スケール

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	Transform*		m_transform = nullptr;
	Mesh*			m_meshCollider	= nullptr;
	ModelRenderer*	m_renderer	= nullptr;

	std::vector<Triangle*> m_floorMesh;		// 床メッシュ
	std::vector<Triangle*> m_wallMesh;		// 壁メッシュ

	std::unordered_map<Triangle*, XMVECTORF32> m_floorColor;	// 床メッシュの色情報

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

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

	// モデルのセット
	void SetModel(DirectX::Model* pModel) {
		m_renderer->SetModel(pModel);
	}

	// 内部実装
private:

	// 面に色を塗る
	void PaintFace(Triangle* face, const XMVECTORF32& color);

};
