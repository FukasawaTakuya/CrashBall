#pragma once
#include "d3d11shader.h"
#include <d3dcompiler.h>
#include <variant>

using ConstantBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using ShaderVariant = std::variant<
	Microsoft::WRL::ComPtr<ID3D11VertexShader>,
	Microsoft::WRL::ComPtr<ID3D11PixelShader>>;

 /**
  * \brief 
  */
class  Shader {

	// メンバ変数の宣言 -----------------------------------------------
private:

	ShaderVariant m_shader;		// シェーダー

	std::vector<ConstantBuffer> m_constantBs;	// 定数バッファ

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;	// バイナリ
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> m_reflection;// リフレクション

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Shader();

	// デストラクタ
	~Shader() = default;

	// 操作
public:

	template<typename T>
	void Create(const std::wstring& path, ID3D11Device1* device)
	{
		// バイナリ読み込み
		D3DReadFileToBlob(
			path.c_str(),
			m_blob.ReleaseAndGetAddressOf());

		Microsoft::WRL::ComPtr<T> comptr;
		m_shader = std::move(comptr);

		// シェーダの作成
		std::visit([&, this](auto& shader)
			{
				// 頂点シェーダ
				if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11VertexShader>>)
				{
					DX::ThrowIfFailed(
						device->CreateVertexShader(
							m_blob->GetBufferPointer(),
							m_blob->GetBufferSize(),
							nullptr,
							shader.ReleaseAndGetAddressOf()));
				}
				// ピクセルシェーダ
				if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11PixelShader>>)
				{
					DX::ThrowIfFailed(
						device->CreatePixelShader(
							m_blob->GetBufferPointer(),
							m_blob->GetBufferSize(),
							nullptr,
							shader.ReleaseAndGetAddressOf()));
				}
			}, m_shader);


		// リフレクション
		DX::ThrowIfFailed(
			D3DReflect(
				m_blob->GetBufferPointer(),
				m_blob->GetBufferSize(),
				IID_ID3D11ShaderReflection,
				reinterpret_cast<void**>(m_reflection.GetAddressOf())));

		D3D11_SHADER_DESC shaderDesc;

		DX::ThrowIfFailed(m_reflection->GetDesc(&shaderDesc));
		for (int i = 0; i < shaderDesc.ConstantBuffers; i++)
		{
			auto cb = m_reflection->GetConstantBufferByIndex(i);
		}
	}

	// 取得/設定
public:

	// 内部実装
private:

	ShaderVariant CreateShader(
		Microsoft::WRL::ComPtr<ID3D11VertexShader>& shader,
		const std::wstring& path,
		ID3D11Device1* device);

	ShaderVariant CreateShader(
		Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader,
		const std::wstring& path,
		ID3D11Device1* device);

};
