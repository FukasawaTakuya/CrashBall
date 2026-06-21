/*****************************************************************//**
 * \file   IModelManager.h
 * \brief  モデル管理クラスのインターフェース 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include <string>
#include <Model.h>

/**
 * @brief モデル管理クラスのインターフェース
 */
class  IModelManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IModelManager() = default;

	// デストラクタ
	virtual ~IModelManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// モデルの取得
	virtual DirectX::Model* GetModel(const std::string& key) = 0;


	// 内部実装
private:

};
