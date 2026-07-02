/*****************************************************************//**
 * \file   IObjectEditGui.h
 * \brief  オブジェクト編集GUIのインターフェース
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

class GameObject;

 /**
  * \brief オブジェクト編集GUIのインターフェース
  */
class  IObjectEditGui {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IObjectEditGui() = default;

	// デストラクタ
	~IObjectEditGui() = default;

	// 操作
public:

	// 取得/設定
public:

	// オブジェクトリストの設定
	virtual void SetObejcts(std::vector<GameObject*>* objects) = 0;

	// 内部実装
private:

};