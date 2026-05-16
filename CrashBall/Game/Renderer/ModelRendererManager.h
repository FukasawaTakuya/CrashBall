/*****************************************************************//**
 * \file   ModelRendererManager.h
 * \brief  モデル描画管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Common/Camera.h"

// 描画命令の登録用
struct ModelDrawCommand
{
	DirectX::Model* pModel;				// モデルのポインタ
	DirectX::SimpleMath::Matrix world;	// ワールド行列
};


/**
 * @brief 基底オブジェクト
 */
class  ModelRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<ModelDrawCommand> m_drawCommandList;	// 描画命令格納用のコンテナ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	ModelRendererManager() = default;

	// 複数生成の禁止
	ModelRendererManager(ModelRendererManager&) = delete;
	ModelRendererManager& operator= (const ModelRendererManager&) = delete;

	// デストラクタ
	~ModelRendererManager() = default;

	// 操作
public:

	// インスタンスの取得
	static ModelRendererManager& Instance() {
		static ModelRendererManager instance;
		return instance;
	}

	// 描画命令の登録
	void RegisterDrawCommand(const ModelDrawCommand& drawCommand);

	// 描画命令のクリア
	void ClearCommandList();

	// 描画
	void Draw(Camera* camera);


	// 取得/設定
public:

	// 内部実装
private:

};
