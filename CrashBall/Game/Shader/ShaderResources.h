/*****************************************************************//**
 * \file   ShaderResources.h
 * \brief  シェーダーリソースをまとめたファイル
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once

#include <variant>
#include <d3d11shader.h>
#include <d3dcompiler.h>
#include "wrl/client.h"
#include "d3d11.h"
#include <string>
#include <vector>

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

	// 
	template<typename T>
	void SetVariable(const T& value)
	{
		if (variables.size() > 0) return;

		std::memcpy(data.data(), &value, sizeof(T));
	}
};

// シェーダテクスチャ情報
struct ShaderTextrueInfo
{
	std::string name;
	ID3D11ShaderResourceView* texture = nullptr;
	uint32_t registerSlot;
};

// UAV情報
struct UnorderedAccessViewInfo : public ConstantBufferInfo{};

// 定数バッファに関するものをまとめた構造体
struct ConstantBufferResource
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;	// 定数バッファ本体
	ConstantBufferInfo info;						// 定数バッファ情報
};

// UAVに関するものをまとめた構造体
struct RWStructuredResource
{
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> uav;	// UAV本体
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;			// バッファ本体
	UnorderedAccessViewInfo info;							// UAV情報
	Microsoft::WRL::ComPtr<ID3D11Buffer> stagingBuffer[3];	// ステージングバッファ
	void* cpudata;	// CPU側のデータ

private:
	std::function<void(ID3D11Device1*)> createUAVCmd	// UAV作成命令
		= [](ID3D11Device1*){};	

	int uavCount;	// UAV数

public:

	// UAV作成命令の実行
	void DoUavCreateCmd(ID3D11Device1* device);

	// UAV作成命令の設定
	void SetUAVCreateCmd(int uavCount);
};

// シェーダの本体を扱うバリアント
using ShaderVariantCom = std::variant<
	Microsoft::WRL::ComPtr<ID3D11VertexShader>,
	Microsoft::WRL::ComPtr<ID3D11PixelShader>,
	Microsoft::WRL::ComPtr<ID3D11ComputeShader>>;

// シェーダ情報
struct ShaderInfo
{
	ShaderVariantCom					shader;				// シェーダ本体
	Microsoft::WRL::ComPtr<ID3DBlob>	blob;				// バイナリ情報
	std::vector<ConstantBufferResource>	constantBuffer;		// 定数バッファリスト
	std::vector<ShaderTextrueInfo> shaderTetureInfo;		// シェーダに渡すテクスチャ情報リスト
	std::vector<RWStructuredResource> rwStructuredResource;	// UAV情報
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;	// 入力レイアウト
	int dispath;	// コンピュートシェーダーのディスパッチ
};

