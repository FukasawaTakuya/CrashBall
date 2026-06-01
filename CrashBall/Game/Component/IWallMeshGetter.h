#pragma once
#include <vector>
#include "Default/Collider/Triangle.h"

/**
 * @brief ステージ操作
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
