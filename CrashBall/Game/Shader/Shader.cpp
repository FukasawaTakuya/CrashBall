/*****************************************************************//**
 * \file   Shader.cpp
 * \brief  シェーダー操作クラス
 *
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "Shader.h"

/**
 * \brief コンストラクタ
 * 
 */
Shader::Shader()
{
}

/**
 * \brief サブリソースの更新
 * 
 * \param context デバイスコンテキスト
 */
void Shader::UpdateSubResources(ID3D11DeviceContext1* context)
{
	// 定数バッファの更新
	for (auto& constantBuffer : m_constantBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE subResource{};
		context->Map(constantBuffer.buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, constantBuffer.info.data.data(), constantBuffer.info.size);
		context->Unmap(constantBuffer.buffer, 0);
	}
}

/**
 * \brief バインド
 * 
 * \param context デバイスコンテキスト
 */
void Shader::Bind(ID3D11DeviceContext1* context)
{
	std::visit([&](const auto& shader)
		{
			using shaderType = std::decay_t<decltype(shader)>;

			// 頂点シェーダの時
			if constexpr (std::is_same_v<shaderType, ID3D11VertexShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->VSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&constantBuffer.buffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->VSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&shaderTextrueInfo.texture);
				}
				// シェーダのセット
				context->VSSetShader(shader, nullptr, 0);
			}
			// ピクセルシェーダの時
			if constexpr (std::is_same_v<shaderType, ID3D11PixelShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->PSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&constantBuffer.buffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->PSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&shaderTextrueInfo.texture);
				}
				// シェーダのセット
				context->PSSetShader(shader, nullptr, 0);
			}
			// コンピュートシェーダーの時
			if constexpr (std::is_same_v<shaderType, ID3D11ComputeShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->CSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&constantBuffer.buffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->CSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&shaderTextrueInfo.texture);
				}
				// 書き込み可能構造化バッファのセット
				for (auto& rwPtr : m_rwStructuredBuffer)
				{
					if (rwPtr.uav != nullptr)
					{
						// UAVのリセット
						UINT value[4]{ 0,0,0,0 };
						context->ClearUnorderedAccessViewUint(
							rwPtr.uav, value);
					}

					context->CSSetUnorderedAccessViews(
						rwPtr.info.registerSlot,
						1,
						&rwPtr.uav,
						nullptr);
				}
				// 書き込み可能シェーダーテクスチャのセット
				for (auto& rwTexPtr : m_rwStructuredTexture)
				{
					context->CSSetUnorderedAccessViews(
						rwTexPtr.registerSlot,
						1,
						&rwTexPtr.uav,
						nullptr);
				}
				// シェーダのセット
				context->CSSetShader(shader, nullptr, 0);
			}
		}, m_shader);
}

/**
 * \brief バインドの解除
 * 
 * \param context デバイスコンテキスト
 */
void Shader::ReleaseBind(ID3D11DeviceContext1* context)
{
	std::visit([&](const auto& shader)
		{
			// シェーダーの型
			using shaderType = std::decay_t<decltype(shader)>;

			// バインド解除用のポインタ
			ID3D11Buffer* nullBuffer = nullptr;
			ID3D11ShaderResourceView* nullSrv = nullptr;
			ID3D11UnorderedAccessView* nullUav = nullptr;

			// 頂点シェーダの時
			if constexpr (std::is_same_v<shaderType, ID3D11VertexShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->VSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&nullBuffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->VSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&nullSrv);
				}
				// シェーダのセット
				context->VSSetShader(shader, nullptr, 0);
			}
			// ピクセルシェーダの時
			if constexpr (std::is_same_v<shaderType, ID3D11PixelShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->PSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&nullBuffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->PSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&nullSrv);
				}
				// シェーダのセット
				context->PSSetShader(shader, nullptr, 0);
			}
			// コンピュートシェーダーの時
			if constexpr (std::is_same_v<shaderType, ID3D11ComputeShader*>)
			{
				// 定数バッファのセット
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->CSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&nullBuffer);
				}
				// シェーダーテクスチャのセット
				for (auto& shaderTextrueInfo : m_shaderTextrueInfo)
				{
					context->CSSetShaderResources(
						shaderTextrueInfo.registerSlot,
						1,
						&nullSrv);
				}
				// UAVのセット
				for (auto& rwPtr : m_rwStructuredBuffer)
				{
					context->CSSetUnorderedAccessViews(
						rwPtr.info.registerSlot,
						1,
						&nullUav,
						nullptr);
				}
				// 書き込み可能シェーダーテクスチャのセット
				for (auto& rwTexPtr : m_rwStructuredTexture)
				{
					context->CSSetUnorderedAccessViews(
						rwTexPtr.registerSlot,
						1,
						&nullUav,
						nullptr);
				}
				// シェーダのセット
				context->CSSetShader(shader, nullptr, 0);
			}
		}, m_shader);
}

/**
 * \brief UAVをCPUにコピー
 * 
 * \param context デバイスコンテキスト
 */
void Shader::CopyResource(ID3D11DeviceContext1* context)
{
	for (auto& rwPtr : m_rwStructuredBuffer)
	{
		if (rwPtr.uav == nullptr) continue;

		// ステージングバッファにUAVをコピー
		context->CopyResource(rwPtr.stagingBuffer[rwPtr.frameCount % 3], rwPtr.buffer);

		// CPU側にステージングバッファをコピー
		D3D11_MAPPED_SUBRESOURCE subResource{};
		int index = (rwPtr.frameCount - 1) % 3;
		index = std::max(index, 0);
		context->Map(rwPtr.stagingBuffer[index], 0, D3D11_MAP_READ, 0, &subResource);
		memcpy(rwPtr.cpudata, subResource.pData, rwPtr.info.size * rwPtr.uavCount);
		context->Unmap(rwPtr.stagingBuffer[index], 0);

		rwPtr.frameCount++;
	}
}

/**
 * \brief UAVの作成
 * 
 * \param uavName UAV名
 * \param uavCount UAVの数
 */
void Shader::CreateRWStructuredUAV(const std::string& uavName, int uavCount)
{
	auto it = std::ranges::find_if(m_rwStructuredBuffer, [&](RWStructuredBufferResourcePtr& rwPtr)
		{
			return uavName == rwPtr.info.name;
		});

	if (it != m_rwStructuredBuffer.end())
	{
		// UAV作成命令の設定命令を実行する
		it->submitUavCreateCmd(uavCount);
		it->uavCount = uavCount;
	}
}

/**
 * \brief CPU側のUAVデータの格納先の設定
 * 
 * \param uavName
 * \param cpuData
 */
void Shader::SetCpuData(const std::string& uavName, void* cpudata)
{
	auto it = std::ranges::find_if(m_rwStructuredBuffer, [&](RWStructuredBufferResourcePtr& rwPtr)
		{
			return uavName == rwPtr.info.name;
		});

	if (it != m_rwStructuredBuffer.end())
	{
		// データの格納先を設定
		it->cpudata = cpudata;
	}
}

/**
 * \brief RWTextrueの設定
 * 
 * \param rwTexName
 * \param texture
 */
void Shader::CreateRWTextureUAV(const std::string& rwTexName, ID3D11Texture2D* texture)
{
	auto it = std::ranges::find_if(m_rwStructuredTexture, [&](RWShaderTextrueResourcePtr& rwTexPtr)
		{
			return rwTexName == rwTexPtr.name;
		});

	if (it != m_rwStructuredTexture.end())
	{
		it->texture2D = texture;
		// データの格納先を設定
		it->submitUavCrateCmd(texture);
	}
}

/**
 * \brief レンダーターゲットをコピーしてRWTextrueのUAVを作成
 *
 * \param rwTexName
 * \param texture
 */
void Shader::CreateRWTextureUAVWithCopy(const std::string& rwTexName, ID3D11Texture2D* texture)
{
	auto it = std::ranges::find_if(m_rwStructuredTexture, [&](RWShaderTextrueResourcePtr& rwTexPtr)
		{
			return rwTexName == rwTexPtr.name;
		});

	if (it != m_rwStructuredTexture.end())
	{
		it->texture2D = texture;
		// データの格納先を設定
		it->submitUavCrateCmdWithCopy(texture);
	}
}

/**
 * \brief シェーダの設定
 * 
 * \param shaderInfo シェーダ情報
 */
void Shader::SetShader(ShaderInfo* shaderInfo)
{
	if (shaderInfo == nullptr) return;

	m_constantBuffer.clear();
	m_shaderTextrueInfo.clear();

	// シェーダのポインタを格納
	std::visit([&](auto& shader)
		{
			m_shader = shader.Get();
		}, shaderInfo->shader);

	// バイナリ情報のポインタを格納
	m_blob = shaderInfo->blob.Get();

	// 定数バッファ
	for (auto& cb : shaderInfo->constantBuffer)
	{
		// 定数バッファはポインタを格納し定数バッファ情報はコピー
		m_constantBuffer.emplace_back(cb.buffer.Get(), cb.info);
	}

	// シェーダーテクスチャ
	for (auto& st : shaderInfo->shaderTetureInfo)
	{
		m_shaderTextrueInfo.emplace_back(st);
	}

	// キャパシティ確保
	m_rwStructuredBuffer.reserve(shaderInfo->rwStructuredResource.size());
	// 書き換え可能構造化バッファ
	for (auto& rw : shaderInfo->rwStructuredResource)
	{
		m_rwStructuredBuffer.emplace_back();
		RWStructuredBufferResourcePtr& rwPtr = m_rwStructuredBuffer.back();

		rwPtr.info = rw.info;

		auto ptr = &rw;
		rwPtr.submitUavCreateCmd = [&, ptr](int count) { ptr->SubmitUAVCreateCmd(count, &rwPtr); };
	}

	// キャパシティ確保
	m_rwStructuredTexture.reserve(shaderInfo->rwShaderTextureInfo.size());
	// 書き換え可能シェーダーテクスチャ
	for (auto& rwTex : shaderInfo->rwShaderTextureInfo)
	{
		m_rwStructuredTexture.emplace_back();
		RWShaderTextrueResourcePtr& rwTexPtr = m_rwStructuredTexture.back();

		rwTexPtr.name = rwTex.name;
		rwTexPtr.registerSlot = rwTex.registerSlot;

		auto ptr = &rwTex;
		rwTexPtr.submitUavCrateCmd			= [&, ptr](ID3D11Texture2D* texture2D) { ptr->SubmitUAVCreateCmd(texture2D, &rwTexPtr); };
		rwTexPtr.submitUavCrateCmdWithCopy = [&, ptr](ID3D11Texture2D* texture2D) { ptr->SubmitUAVCreateCmdWithCopy(texture2D, &rwTexPtr); };
	}

	// 入力レイアウトのポインタを格納
	m_inputLayout = shaderInfo->inputLayout.Get();
}
