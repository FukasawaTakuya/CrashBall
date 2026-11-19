/*****************************************************************//**
 * \file   ShaderResources.h
 * \brief  シェーダーリソースをまとめたファイル
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "ShaderResources.h"
#include "Shader.h"

/**
 * \brief UAV作成依頼の実行
 * 
 * \param device デバイス
 */
void RWStructuredResource::DoUavCreateCmd(ID3D11Device1* device)
{
	// 命令の実行
	createUAVCmd(device);
	createUAVCmd = [](ID3D11Device1*) {};
}

/**
 * \brief UAV作成以来の発行
 *
 * \param uavCount UAV数
 * \param rwPtr RWStructuredのポインタを保持する構造体
 */
void RWStructuredResource::SubmitUAVCreateCmd(int uavCount, RWStructuredBufferResourcePtr* rwPtr)
{
	this->uavCount = uavCount;
	createUAVCmd = [&, rwPtr](ID3D11Device1* device)
		{
			// バッファの作成
			D3D11_BUFFER_DESC bufDesc = {};
			bufDesc.Usage = D3D11_USAGE_DEFAULT;
			bufDesc.ByteWidth = info.size * this->uavCount;
			bufDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
			bufDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			bufDesc.StructureByteStride = info.size;
			device->CreateBuffer(&bufDesc, nullptr, buffer.ReleaseAndGetAddressOf());
			// UAVの作成
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = this->uavCount;
			device->CreateUnorderedAccessView(buffer.Get(), &uavDesc, uav.ReleaseAndGetAddressOf());

			// ステージングバッファの作成
			bufDesc.Usage = D3D11_USAGE_STAGING;
			bufDesc.BindFlags = 0;
			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			bufDesc.MiscFlags = 0;

			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[0].ReleaseAndGetAddressOf());
			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[1].ReleaseAndGetAddressOf());
			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[2].ReleaseAndGetAddressOf());

			// ポインタを渡す
			rwPtr->uav = uav.Get();
			rwPtr->buffer = buffer.Get();
			rwPtr->stagingBuffer[0] = stagingBuffer[0].Get();
			rwPtr->stagingBuffer[1] = stagingBuffer[1].Get();
			rwPtr->stagingBuffer[2] = stagingBuffer[2].Get();
		};
}

/**
 * \brief UAV作成依頼の実行
 * 
 * \param device デバイス
 */
void RWShaderTextrueResource::DoUavCreateCmd(ID3D11Device1* device)
{
	// 命令の実行
	createUAVCmd(device);
	createUAVCmd = [](ID3D11Device1*) {};
}

/**
 * \brief UAV作成以来の発行
 *
 * \param textrue2D テクスチャ
 * \param rwTexPtr RWShaderTextrueのポインタを保持する構造体
 */
void RWShaderTextrueResource::SubmitUAVCreateCmd(
	ID3D11Texture2D* texture2D, 
	RWShaderTextrueResourcePtr* rwTexPtr)
{
	this->texture2D = texture2D;

	createUAVCmd =
		[&, rwTexPtr](ID3D11Device1* device)
		{
			// 渡されたレンダーターゲットをそのまま使う
			D3D11_TEXTURE2D_DESC texDesc{};
			this->texture2D->GetDesc(&texDesc);
			device->CreateUnorderedAccessView(this->texture2D, nullptr, uav.ReleaseAndGetAddressOf());

			// ステージングテクスチャの作成
			texDesc.Usage = D3D11_USAGE_STAGING;
			texDesc.BindFlags = 0;
			texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texDesc.MiscFlags = 0;

			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[0].ReleaseAndGetAddressOf());
			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[1].ReleaseAndGetAddressOf());
			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[2].ReleaseAndGetAddressOf());

			// ポインタを渡す
			rwTexPtr->uav = uav.Get();
			rwTexPtr->stagingtexture[0] = stagingtexture[0].Get();
			rwTexPtr->stagingtexture[1] = stagingtexture[1].Get();
			rwTexPtr->stagingtexture[2] = stagingtexture[2].Get();
		};
}

/**
 * \brief UAV作成命令の設定
 *
 * \param textrue2D テクスチャ
 * \param rwTexPtr RWShaderTextrueのポインタを保持する構造体
 */
void RWShaderTextrueResource::SubmitUAVCreateCmdWithCopy(
	ID3D11Texture2D* texture2D, 
	RWShaderTextrueResourcePtr* rwTexPtr)
{
	this->texture2D = texture2D;

	createUAVCmd =
		[&, rwTexPtr](ID3D11Device1* device)
		{
			// 渡されたデスクから新しくレンダーターゲットを作る
			D3D11_TEXTURE2D_DESC texDesc{};
			this->texture2D->GetDesc(&texDesc);
			device->CreateTexture2D(&texDesc, nullptr, texture2DCopy.ReleaseAndGetAddressOf());
			device->CreateUnorderedAccessView(texture2DCopy.Get(), nullptr, uav.ReleaseAndGetAddressOf());

			// ステージングテクスチャの作成
			texDesc.Usage = D3D11_USAGE_STAGING;
			texDesc.BindFlags = 0;
			texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texDesc.MiscFlags = 0;

			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[0].ReleaseAndGetAddressOf());
			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[1].ReleaseAndGetAddressOf());
			device->CreateTexture2D(&texDesc, nullptr, stagingtexture[2].ReleaseAndGetAddressOf());

			// ポインタを渡す
			rwTexPtr->uav = uav.Get();
			rwTexPtr->stagingtexture[0] = stagingtexture[0].Get();
			rwTexPtr->stagingtexture[1] = stagingtexture[1].Get();
			rwTexPtr->stagingtexture[2] = stagingtexture[2].Get();
		};
}
