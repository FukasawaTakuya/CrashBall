/*****************************************************************//**
 * \file   IWallMeshGetter.h
 * \brief  壁メッシュ取得クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once
#include <vector>
#include "Game/Geometory/Triangle.h"

/**
 * @brief 壁メッシュ取得クラスのインターフェース
 */
class  IWallMeshGetter {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IWallMeshGetter() = default;

	// デストラクタ
	~IWallMeshGetter() = default;

	// 操作
public:

	// 取得/設定
public:

	// 壁メッシュの取得
	virtual const std::vector<Triangle*>& GetWallMesh() const = 0;

	// 内部実装
private:

};
