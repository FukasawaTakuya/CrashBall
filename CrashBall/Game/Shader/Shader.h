#pragma once
#include "d3d11shader.h"
#include <d3dcompiler.h>
#include <variant>

using ConstantBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using ShaderVariant = std::variant<
	Microsoft::WRL::ComPtr<ID3D11VertexShader>,
	Microsoft::WRL::ComPtr<ID3D11PixelShader>>;

struct ShaderVariableInfo
{
	std::string name;
	uint32_t size;
	uint32_t offset;
};

struct ConstantBufferInfo
{
	std::string name;
	uint32_t size;
	uint32_t registerSlot;

	std::vector<ShaderVariableInfo> variables;

	std::vector<std::byte> data;
	ConstantBuffer gpuBuffer;

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
};

 /**
  * \brief シェーダ
  */
class  Shader {

	// メンバ変数の宣言 -----------------------------------------------
private:

	ShaderVariant m_shader;		// シェーダー

	std::vector<ConstantBufferInfo> m_constantInfo;	// 定数バッファ情報

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;					// バイナリ情報
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> m_reflection;// リフレクション情報

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Shader();

	// デストラクタ
	~Shader() = default;

	// 操作
public:

	// 作成
	template<typename T>
	void Create(const std::wstring& filePath, ID3D11Device1* device)
	{
		// シェーダ
		Microsoft::WRL::ComPtr<T> comptr;
		m_shader = std::move(comptr);

		// バイナリ読み込み
		D3DReadFileToBlob(
			filePath.c_str(),
			m_blob.ReleaseAndGetAddressOf());

		Create(device);
	}

	void UpdateSubResources(ID3D11DeviceContext1* conetxt);

	void Bind(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// バイナリ情報の取得
	ID3DBlob* GetBlob() const { return m_blob.Get(); }

	ConstantBufferInfo* GetConstatntBufferInfo(const std::string& name)
	{
		for (auto& cbinfo : m_constantInfo)
		{
			if (cbinfo.name == name)
			{
				return &cbinfo;
			}
		}
		return nullptr;
	}

	// 内部実装
private:

	ShaderVariant CreateShader(
		Microsoft::WRL::ComPtr<ID3D11VertexShader>& shader,
		const std::wstring& filePath,
		ID3D11Device1* device);

	ShaderVariant CreateShader(
		Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader,
		const std::wstring& filePath,
		ID3D11Device1* device);

	void Create(ID3D11Device1* device);
};
