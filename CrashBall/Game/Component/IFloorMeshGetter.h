/*****************************************************************//**
 * \file   IFloorMeshGetter.h
 * \brief  床メッシュ取得クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

/**
 * \brief 床メッシュ取得クラスのインターフェース
 */
class  IFloorMeshGetter {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IFloorMeshGetter() = default;

	// デストラクタ
	~IFloorMeshGetter() = default;

	// 操作
public:

	// 取得/設定
public:

	// プレイヤーが塗った面の数の取得
	virtual int GetPlayerMeshCount() const = 0;

	// 敵が塗ったの面の数の取得
	virtual int GetEnemyMeshCount() const = 0;

	// 何も塗られていない面の数の取得
	virtual int GetNormalMeshCount() const = 0;

	// 内部実装
private:

};
