#include "pch.h"
#include "Shader.h"

#include <d3dcompiler.h>

Shader::Shader()
{
}

ShaderVariant Shader::CreateShader(
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& shader, 
	const std::wstring& path, 
	ID3D11Device1* device)
{
	DX::ThrowIfFailed(
		device->CreateVertexShader(
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			nullptr,
			shader.ReleaseAndGetAddressOf()));

	return std::move(shader);
}

ShaderVariant Shader::CreateShader(
	Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader,
	const std::wstring& path,
	ID3D11Device1* device)
{
	DX::ThrowIfFailed(
		device->CreatePixelShader(
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			nullptr,
			shader.ReleaseAndGetAddressOf()));

	return std::move(shader);
}

