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
			if constexpr (std::is_same_v<shaderType, ID3D11ComputeShader>)
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
				// UAVのセット
				for (auto& rwPtr : m_rwStructuredBuffer)
				{
					context->CSSetUnorderedAccessViews(
						rwPtr.info.registerSlot,
						rwPtr.uavCount,
						&rwPtr.uav,
						nullptr);

					context->CopyResource(rwPtr.stagingBuffer[rwPtr.frameCount % 2], rwPtr.uav);
					rwPtr.frameCount++;
				}
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
						rwPtr.uavCount,
						&nullUav,
						nullptr);
				}
				// シェーダのセット
				context->CSSetShader(shader, nullptr, 0);
			}
		}, m_shader);
}

/**
 * \brief UAVの作成
 * 
 * \param uavName UAV名
 * \param uavCount UAVの数
 */
void Shader::CreateUAV(const std::string& uavName, int uavCount)
{
	auto it = std::ranges::find_if(m_rwStructuredBuffer, [&](RWStructuredBufferPtr& rwPtr)
		{
			return uavName == rwPtr.info.name;
		});

	if (it != m_rwStructuredBuffer.end())
	{
		// UAV生成命令を設定する
		it->setUavCreateCmd(uavCount);
		it->uavCount = uavCount;
	}
}

/**
 * \brief シェーダの設定
 * 
 * \param shaderInfo シェーダ情報
 */
void Shader::SetShader(ShaderInfo* shaderInfo)
{
	m_constantBuffer.clear();
	m_shaderTextrueInfo.clear();

	// シェーダのポインタを格納
	std::visit([&](auto& shader)
		{
			m_shader = shader.Get();
		}, shaderInfo->shader);

	// バイナリ情報のポインタを格納
	m_blob = shaderInfo->blob.Get();

	for (auto& cb : shaderInfo->constantBuffer)
	{
		// 定数バッファはポインタを格納し定数バッファ情報はコピー
		m_constantBuffer.emplace_back(cb.buffer.Get(), cb.info);
	}

	for (auto& st : shaderInfo->shaderTetureInfo)
	{
		m_shaderTextrueInfo.emplace_back(st);
	}

	for (auto& rw : shaderInfo->rwStructuredResource)
	{
		RWStructuredBufferPtr rwPtr;

		rwPtr.buffer = rw.buffer.Get();
		rwPtr.uav = rw.uav.Get();
		rwPtr.info = rw.info;
		rwPtr.stagingBuffer[0] = rw.stagingBuffer[0].Get();
		rwPtr.stagingBuffer[1] = rw.stagingBuffer[1].Get();
		rwPtr.stagingBuffer[2] = rw.stagingBuffer[2].Get();

		rwPtr.setUavCreateCmd = [&](int count) { rw.SetUAVCreateCmd(count); };
	}

	// 入力レイアウトのポインタを格納
	m_inputLayout = shaderInfo->inputLayout.Get();
}
