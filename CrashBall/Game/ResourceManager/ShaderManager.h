/*****************************************************************//**
 * \file   ShaderManager.h
 * \brief  シェーダ管理クラス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/ResourceManager/Interface/IShaderManager.h"

 /**
  * \brief シェーダ管理クラス
  */
class  ShaderManager : public IShaderManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	using ShaderCollection = std::unordered_map<std::string, ShaderInfo>;

	ShaderCollection m_shaders;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ShaderManager();

	// デストラクタ
	~ShaderManager() = default;

	// 操作
public:

	// シェーダの作成
	void CreateShader(ID3D11Device1* device);

	// 取得/設定
public:

	// シェーダ情報の取得
	ShaderInfo* GetShaderInfo(const std::string& key) override
	{
		auto it = m_shaders.find(key);
		if (it != m_shaders.end())
		{
			return &it->second;
		}
	}

	// 内部実装
private:

	// 定数バッファの作成
	void CreateConstatBuffer(ShaderInfo& shaderInfo, ID3D11Device1* device);

	// 入力レイアウトの作成
	void CreateInputLayout(ShaderInfo& shaderInfo, ID3D11Device1* device);
};
