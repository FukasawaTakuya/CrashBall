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
	for (auto& constantBuffer : m_constantBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE subResource{};
		context->Map(constantBuffer.buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, constantBuffer.info.data.data(), constantBuffer.info.size);
		context->Unmap(constantBuffer.buffer, 0);
	}
}

/**
 * \brief コンテキストにシェーダを渡す
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
		}, m_shader);
}

/**
 * \brief シェーダの設定
 * 
 * \param shaderInfo シェーダ情報
 */
void Shader::SetShader(const ShaderInfo* shaderInfo)
{
	m_constantBuffer.clear();
	m_constantInfoMap.clear();

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
		// 格納した定数バッファをマップに登録
		auto& cbInfo = m_constantBuffer.back();
		m_constantInfoMap.emplace(cbInfo.info.name, &cbInfo.info);
	}

	for (auto& st : shaderInfo->shaderTetureInfo)
	{
		m_shaderTextrueInfo.push_back(st);
		// マップに登録
		auto& stInfo = m_shaderTextrueInfo.back();
		m_shaderTextureInfoMap.emplace(stInfo.name, &stInfo);

	}

	// 入力レイアウトのポインタを格納
	m_inputLayout = shaderInfo->inputLayout.Get();
}
