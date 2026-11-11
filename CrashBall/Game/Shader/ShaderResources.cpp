/*****************************************************************//**
 * \file   ShaderResources.h
 * \brief  シェーダーリソースをまとめたファイル
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "ShaderResources.h"

/**
 * \brief UAV作成命令の実行
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
 * \brief UAV作成命令の設定
 *
 * \param uavCount UAV数
 */
void RWStructuredResource::SetUAVCreateCmd(int uavCount)
{
	this->uavCount = uavCount;
	createUAVCmd = [&](ID3D11Device1* device)
		{
			// バッファの作成
			D3D11_BUFFER_DESC bufDesc = {};
			bufDesc.Usage = D3D11_USAGE_DEFAULT;
			bufDesc.ByteWidth = info.size * uavCount;
			bufDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
			bufDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			bufDesc.StructureByteStride = info.size;
			device->CreateBuffer(&bufDesc, nullptr, buffer.ReleaseAndGetAddressOf());
			// UAVの作成
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = uavCount;

			device->CreateUnorderedAccessView(buffer.Get(), &uavDesc, uav.ReleaseAndGetAddressOf());

			// ステージングバッファの作成
			bufDesc.Usage = D3D11_USAGE_STAGING;
			bufDesc.BindFlags = 0;
			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			bufDesc.MiscFlags = 0;
			bufDesc.StructureByteStride = 0;

			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[0].ReleaseAndGetAddressOf());
			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[1].ReleaseAndGetAddressOf());
			device->CreateBuffer(&bufDesc, nullptr, stagingBuffer[2].ReleaseAndGetAddressOf());
		};
}
