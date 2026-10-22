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
	uint32_t vertexCount = 0;	// 頂点数
	uint32_t indexCount = 0;	// インデックス数
	uint32_t submeshCount = 0;	// サブメッシュ数
	uint32_t materialCount = 0;	// マテリアル数
	uint32_t textureCount = 0;	// テクスチャ数
};

struct Vertex
{
	DirectX::XMFLOAT3 position;	// ポジション
	DirectX::XMFLOAT3 normal;	// 法線
	DirectX::XMFLOAT2 uv;		// UV座標
};

struct Submesh
{
	uint32_t indexStart = 0;	// 開始インデックス
	uint32_t indexCount = 0;	// インデックス数
	uint32_t materialIndex = -1;// 使用マテリアルのインデックス
};

struct MaterialData
{
	DirectX::XMFLOAT4 baseColor;		// 基本色
	int textureIndex;					// テクスチャのインデックス
};

// 頂点シェーダ用定数バッファ
struct ConstantVS
{
	DirectX::XMFLOAT4X4 worldViewProj;			// world*view*proj
	DirectX::XMFLOAT4X4 worldInvertTranspose;	// ワールド逆転置行列
	DirectX::XMFLOAT4 lightDirection;			// ライト方向
};

// ピクセルシェーダ用定数バッファ
struct ConstantPS
{
	DirectX::XMFLOAT4 baseColor;		// 基本色
	DirectX::XMFLOAT4 textureIndex;		// テクスチャのインデックス
};

 /**
  * \brief 自作モデルクラス
  */
class  MyModel {

	// メンバ変数の宣言 -----------------------------------------------
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;		// インデックス

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantVS;	// 頂点シェーダ用定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantPS;	// ピクセルシェーダ用定数バッファ

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
