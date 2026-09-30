/*****************************************************************//**
 * \file   ModelManager.h
 * \brief  モデル管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/ResourceManager/Interface/IModelManager.h"

/**
 * @brief モデル管理クラス
 */
class  ModelManager : public IModelManager{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	using ModelCollection 
		= std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>;

	ModelCollection	m_models;	// モデルのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ModelManager();

	// デストラクタ
	~ModelManager();

	// 操作
public:

	// モデルの作成
	void CreateModel(ID3D11Device1* device);

	// 取得/設定
public:

	// モデルの取得
	DirectX::Model* GetModel(const std::string& key) override;

	// 内部実装
private:

};
