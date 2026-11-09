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

	// シェーダーリソースの作成
	void CreateShaderResource(ShaderInfo& shaderInfo, ID3D11Device1* device);

	// 定数バッファの作成
	void CreateConstantBuffer(
		ShaderInfo& shaderInfo, 
		ID3D11Device1* device, 
		ID3D11ShaderReflection* reflection,
		D3D11_SHADER_INPUT_BIND_DESC& bindDesc);

	// シェーダーテクスチャの作成
	void CreateShaderTexture(
		ShaderInfo& shaderInfo,
		D3D11_SHADER_INPUT_BIND_DESC& bindDesc);

	// UAVの作成
	void CreateRWStructuredResource(
		ShaderInfo& shaderInfo,
		ID3D11ShaderReflection* reflection,
		D3D11_SHADER_INPUT_BIND_DESC& bindDesc);

	// 入力レイアウトの作成
	void CreateInputLayout(ShaderInfo& shaderInfo, ID3D11Device1* device);
};
