#pragma once
#include "d3d11shader.h"
#include <d3dcompiler.h>
#include <variant>

#include "Game/ResourceManager/Interface/IShaderManager.h"

using ShaderVariant = std::variant<
	ID3D11VertexShader*,
	ID3D11PixelShader*>;

struct ConstatBufferPtr
{
	ID3D11Buffer* buffer;
	ConstantBufferInfo info;
};

 /**
  * \brief シェーダ
  */
class  Shader {

	// メンバ変数の宣言 -----------------------------------------------
private:

	ShaderVariant m_shader;								// シェーダー
	ID3DBlob* m_blob;									// バイナリ情報
	std::vector<ConstatBufferPtr> m_constantBuffer;		// 定数バッファ
	std::vector<ShaderTextrueInfo> m_shaderTextrueInfo;	// シェーダに渡すテクスチャ情報
	ID3D11InputLayout* m_inputLayout;					// 入力レイアウト

	// コンスタントバッファのマップ
	std::unordered_map<std::string, ConstantBufferInfo*> m_constantInfoMap;
	// シェーダに渡すテクスチャ情報のマップ
	std::unordered_map<std::string, ShaderTextrueInfo*> m_shaderTextureInfoMap;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Shader();

	// デストラクタ
	~Shader() = default;

	// 操作
public:

	// サブリソースの更新
	void UpdateSubResources(ID3D11DeviceContext1* conetxt);

	// コンテキストにシェーダを渡す
	void Bind(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// バイナリ情報の取得
	ID3DBlob* GetBlob() const { return m_blob; }

	// 定数バッファ情報の取得
	ConstantBufferInfo* GetConstatntBufferInfo(const std::string& name)
	{
		auto it = m_constantInfoMap.find(name);
		if (it != m_constantInfoMap.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}
	// シェーダに渡すテクスチャ情報の取得
	ShaderTextrueInfo* GetShaderTextrueInfo(const std::string& name)
	{
		auto it = m_shaderTextureInfoMap.find(name);
		if (it != m_shaderTextureInfoMap.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	// 入力レイアウトの取得
	ID3D11InputLayout* GetInputLayOut() const
	{
		return m_inputLayout;
	}

	// シェーダの設定
	void SetShader(const ShaderInfo* shaderInfo);

	// 内部実装
private:
};
