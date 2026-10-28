#pragma once
#include "d3d11shader.h"
#include <d3dcompiler.h>
#include <variant>

#include "Game/ResourceManager/Interface/IShaderManager.h"

using ShaderVariant = std::variant<
	ID3D11VertexShader*,
	ID3D11PixelShader*>;

struct ConstatBufferPtr
{
	ID3D11Buffer* buffer;
	ConstantBufferInfo info;
};

 /**
  * \brief シェーダ
  */
class  Shader {

	// メンバ変数の宣言 -----------------------------------------------
private:

	ShaderVariant m_shader;							// シェーダー
	ID3DBlob* m_blob;								// バイナリ情報
	std::vector<ConstatBufferPtr> m_constantBuffer;	// 定数バッファ
	ID3D11InputLayout* m_inputLayout;				// 入力レイアウト

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
		//Microsoft::WRL::ComPtr<T> comptr;
		//m_shader = std::move(comptr);

		//// バイナリ読み込み
		//D3DReadFileToBlob(
		//	filePath.c_str(),
		//	m_blob.ReleaseAndGetAddressOf());

		//Create(device);
	}

	void UpdateSubResources(ID3D11DeviceContext1* conetxt);

	void Bind(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// バイナリ情報の取得
	ID3DBlob* GetBlob() const { return m_blob; }

	ConstantBufferInfo* GetConstatntBufferInfo(const std::string& name)
	{
		for (auto& constantBuffer : m_constantBuffer)
		{
			if (constantBuffer.info.name == name)
			{
				return &constantBuffer.info;
			}
		}
		return nullptr;
	}

	ID3D11InputLayout* GetInputLayOut() const
	{
		return m_inputLayout;
	}

	void SetShader(const ShaderInfo* shaderInfo);

	// 内部実装
private:
	//void Create(ID3D11Device1* device);
};
