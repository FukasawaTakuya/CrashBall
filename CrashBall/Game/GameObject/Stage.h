/*****************************************************************//**
 * \file   Stage.h
 * \brief  ステージオブジェクト
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "GameObject.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Stage/StageController.h"


/**
 * \brief ステージオブジェクト
 */
class  Stage : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	StageController* m_stageController;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Stage(json* data);

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

	// パラメータの書き込み
	void SaveParam() override;

	// 初期化用のパラメータの書き込み
	void SaveInitParam() override;

	// データの再読み込み
	void ReloadParam() override;


	// 取得/設定
public:

	// 内部実装
private:

	// JsonConverter
private:

	friend void to_json(json& j, const Mesh& mesh);
	friend void from_json(const json& j, Mesh& mesh);

};
