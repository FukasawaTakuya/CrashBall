/*****************************************************************//**
 * \file   MyModel.h
 * \brief  モデルクラス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

struct ModelHeader
{
	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;
	uint32_t submeshCount = 0;
	uint32_t materialCount = 0;
	uint32_t textureCount = 0;
};

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
};

struct Submesh
{
	uint32_t indexStart = 0;
	uint32_t indexCount = 0;
	uint32_t materialIndex = -1;
};

struct MaterialData
{
	DirectX::XMFLOAT4 baseColor;		// 基本色
	int textureIndex;					// テクスチャのインデックス
};

 /**
  * \brief 
  */
class  MyModel {

	// メンバ変数の宣言 -----------------------------------------------
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;		// インデックス

	std::vector<Submesh> m_submeshList;				// サブメッシュリスト
	std::vector<MaterialData> m_materialDataList;	// マテリアルリスト
	// テクスチャリスト
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixeShader;		// ピクセルシェーダー

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MyModel();

	// デストラクタ
	~MyModel() = default;

	// 操作
public:

	void Draw(
		const DirectX::SimpleMath::Matrix& world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		DirectX::CommonStates* states,
		ID3D11DeviceContext1* context);

	void Create(
		ID3D11Device1* device,
		const std::string& filepath);

	// 取得/設定
public:

	// 内部実装
private:

};
