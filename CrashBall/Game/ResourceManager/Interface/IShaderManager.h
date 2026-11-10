/*****************************************************************//**
 * \file   IShaderManager.h
 * \brief  シェーダ管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once
#include "Game/Shader/ShaderResources.h"

 /**
  * \brief シェーダ管理クラスのインターフェース
  */
class  IShaderManager {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IShaderManager() = default;
	// デストラクタ
	virtual ~IShaderManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// シェーダ情報の取得
	virtual ShaderInfo* GetShaderInfo(const std::string& key) = 0;

	// 内部実装
private:

};
