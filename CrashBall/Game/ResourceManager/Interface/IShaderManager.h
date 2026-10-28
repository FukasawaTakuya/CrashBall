/*****************************************************************//**
 * \file   IShaderManager.h
 * \brief  シェーダ管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include <variant>
#include <d3d11shader.h>
#include <d3dcompiler.h>
#include "wrl/client.h"
#include "d3d11.h"
#include <string>

// シェーダの変数情報
struct ShaderVariableInfo
{
	std::string name;
	uint32_t size;
	uint32_t offset;
};

// 定数バッファ情報
struct ConstantBufferInfo
{
	std::string name;		// 名前
	uint32_t size;			// サイズ
	uint32_t registerSlot;	// レジスタ番号

	std::vector<ShaderVariableInfo> variables;	// 変数情報

	std::vector<std::byte> data;// データ

	// 定数バッファに値を設定
	template<typename T>
	void SetVariable(
		const std::string& name,
		const T& value)
	{
		for (auto& vari : variables)
		{
			if (vari.name != name)
				continue;

			// 型・サイズが一致しているか確認
			if (vari.size != sizeof(T))
				continue;

			if (vari.offset + sizeof(T) > data.size())
				continue;

			std::memcpy(
				data.data() + vari.offset,
				&value,
				sizeof(T));
			break;
		}
	}
};

// シェーダテクスチャ情報
struct ShaderTextrueInfo
{
	std::string name;
	ID3D11ShaderResourceView* texture;
	uint32_t registerSlot;
};

// 定数バッファに関するものをまとめた構造体
struct ConstantBufferResource
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	ConstantBufferInfo info;
};

// シェーダの本体を扱うバリアント
using ShaderVariantCom = std::variant<
	Microsoft::WRL::ComPtr<ID3D11VertexShader>,
	Microsoft::WRL::ComPtr<ID3D11PixelShader>>;

// シェーダ情報
struct ShaderInfo
{
	ShaderVariantCom					shader;				// シェーダ本体
	Microsoft::WRL::ComPtr<ID3DBlob>	blob;				// バイナリ情報
	std::vector<ConstantBufferResource>	constantBuffer;		// 定数バッファ
	std::vector<ShaderTextrueInfo> shaderTetureInfo;		// シェーダに渡すテクスチャ情報
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;	// 入力レイアウト
};

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
