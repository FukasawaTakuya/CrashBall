/*****************************************************************//**
 * \file   ShaderResourcesPtr.h
 * \brief  シェーダーリソースのポインタをまとめたファイル
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once
#include <variant>
#include <functional>
#include "ShaderResources.h"
#include "d3d11.h"

 // シェーダーのポインタを保持するバリアント
using ShaderVariant = std::variant<
	ID3D11VertexShader*,
	ID3D11PixelShader*,
	ID3D11ComputeShader*>;

// 定数バッファのポインタを保持する構造体
struct ConstantBufferPtr
{
	ID3D11Buffer* buffer = nullptr;	// 定数バッファのポインタ
	ConstantBufferInfo info;// 定数バッファ情報
};

// 読み書き可能構造化バッファーのポインタを保持する構造体
struct RWStructuredBufferPtr
{
	ID3D11UnorderedAccessView* uav;	// UAVのポインタ
	ID3D11Buffer* buffer;			// バッファのポインタ
	UnorderedAccessViewInfo info;	// UAV情報
	ID3D11Buffer* stagingBuffer[3];	// ステージングバッファのポインタ
	uint32_t uavCount;				// UAV数
	void* cpudata;					// CPU側のデータ格納先
	std::function<void(int)> setUavCreateCmd;	// UAV作成命令の設定命令

	int frameCount = 0;							// ステージングバッファ用の経過フレーム数
};

// 書き換え可能シェーダーテクスチャ
struct RWShaderTextruePtr
{
	std::string name;
	ID3D11Texture2D* texture2D;	// テクスチャのポインタ
	uint32_t registerSlot;

	ID3D11UnorderedAccessView* uav;		// UAVのポインタ
	ID3D11Texture2D* stagingtexture[3];	// ステージングテクスチャのポインタ

	std::function<void(ID3D11Texture2D* texture2D)> setUavCrateCmd;	// UAV作成命令の設定命令
};

