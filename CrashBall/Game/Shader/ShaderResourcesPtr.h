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

 // シェーダーのポインタ保持用
using ShaderVariant = std::variant<
	ID3D11VertexShader*,
	ID3D11PixelShader*,
	ID3D11ComputeShader*>;

// 定数バッファのポインタ保持用
struct ConstantBufferPtr
{
	ID3D11Buffer* buffer = nullptr;	// 定数バッファのポインタ
	ConstantBufferInfo info;// 定数バッファ情報
};

// 読み書き可能構造化バッファーのポインタ保持用
struct RWStructuredBufferResourcePtr
{
	ID3D11UnorderedAccessView* uav;	// UAVのポインタ
	ID3D11Buffer* buffer;			// バッファのポインタ
	UnorderedAccessViewInfo info;	// UAV情報
	ID3D11Buffer* stagingBuffer[3];	// ステージングバッファのポインタ
	uint32_t uavCount;				// UAV数
	void* cpudata;					// CPU側のデータ格納先
	std::function<void(int)> submitUavCreateCmd;	// 本体のUAV作成命令保持用

	int frameCount = 0;	// ステージングバッファ用の経過フレーム数
};

// 書き換え可能シェーダーテクスチャのポインタ保持用
struct RWShaderTextrueResourcePtr
{
	std::string name;			// テクスチャ名
	ID3D11Texture2D* texture2D;	// テクスチャのポインタ
	uint32_t registerSlot;

	ID3D11UnorderedAccessView* uav;		// UAVのポインタ
	ID3D11Texture2D* stagingtexture[3];	// ステージングテクスチャのポインタ

	std::function<void(ID3D11Texture2D* texture2D)> submitUavCrateCmd;			// 本体のUAV作成命令保持用
	std::function<void(ID3D11Texture2D* texture2D)> submitUavCrateCmdWithCopy;	// 本体のUAV作成命令保持用
};

