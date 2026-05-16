/*****************************************************************//**
 * \file   ModelManager.h
 * \brief  モデル管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Common/Camera.h"

/**
 * @brief 基底オブジェクト
 */
class  ModelManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// エイリアス宣言
	using FileCollection 
		= std::unordered_map<std::string, const wchar_t*>;
	using ModelCollection 
		= std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>;

	FileCollection	m_factory;	// モデルファクトリー
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

	// ファクトリーに登録
	void RegisterModel(std::string key, const wchar_t* fileName);

	// モデルの作成
	void CreateModel(ID3D11Device1* device);

	// 取得/設定
public:

	// モデルの取得
	DirectX::Model* GetModel(const std::string& key) { return m_models[key].get(); }

	// 内部実装
private:

};
