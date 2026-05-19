/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  リソース管理クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "ModelManager.h"

/**
 * @brief 基底オブジェクト
 */
class  ResourceManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<ModelManager> m_modelManager;	// モデル管理クラス


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	ResourceManager() = default;
	
	// 複数生成の禁止
	ResourceManager(ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;

	// デストラクタ
	~ResourceManager() = default;

	// 操作
public:
	// インスタンスの取得
	static ResourceManager& Instance() {
		static ResourceManager instance;
		return instance;
	}

	// マネージャーの作成
	void CreateManager();

	// リソースの作成
	void CreateResources(ID3D11Device1* device);

	// 取得/設定
public:

	// モデル管理クラスの取得
	ModelManager* GetModelManager() const { return m_modelManager.get(); }

	// 内部実装
private:

};
