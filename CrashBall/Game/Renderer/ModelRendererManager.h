/*****************************************************************//**
 * \file   ModelRendererManager.h
 * \brief  モデル描画管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Common/Camera.h"
#include "Game/Interface/IModelRendererManager.h"

/**
 * @brief モデル描画管理クラス
 */
class  ModelRendererManager : public IModelRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<ModelDrawCommand> m_drawCommandList;	// 描画命令格納用のコンテナ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ModelRendererManager() = default;

	// デストラクタ
	~ModelRendererManager() = default;

	// 操作
public:

	// 描画命令の登録
	void RegisterDrawCommand(const ModelDrawCommand& drawCommand) override;

	// 描画命令のクリア
	void ClearCommandList();

	// 描画
	void Render(Camera* camera);


	// 取得/設定
public:

	// 内部実装
private:

};
