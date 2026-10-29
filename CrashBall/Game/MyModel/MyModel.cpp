#include "pch.h"
#include "MyModel.h"

#include <fstream>
#include "WICTextureLoader.h"
#include "DX/ReadData.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
MyModel::MyModel()
{
}

/**
 * \brief 描画
 * 
 * \param world ワールド行列
 * \param view ビュー行列
 * \param proj プロジェクション行列
 * \param states コモンステート
 * \param vertexShader 頂点シェーダ
 * \param pixelShader ピクセルシェーダ
 * \param context デバイスコンテキスト
 */
void MyModel::Draw(
	const DirectX::SimpleMath::Matrix& world,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj,
	Shader* vertexShader,
	Shader* pixelShader,
	DirectX::CommonStates* states,
	ID3D11DeviceContext1* context)
{
	// =========== IA =========== //

	// 頂点バッファの設定
	ID3D11Buffer* vBuffers[] = { m_vertexBuffer.Get() };
	UINT strides[] = { sizeof(Vertex) };
	UINT offset[] = { 0 };
	context->IASetVertexBuffers(0, 1, vBuffers, strides, offset);
	// インデックスバッファの設定
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	// トポロジーの設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 入力レイアウトの設定
	context->IASetInputLayout(vertexShader->GetInputLayOut());

	// ==== RS ==== //
	context->RSSetState(states->CullClockwise());

	// ==== OM ==== //
	// 深度ステンシルステートの設定
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ブレンドステートの設定
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xffffffff);
	 
	// ==== VS ==== //
	auto vsConstantBuffer = vertexShader->GetConstatntBufferInfo("ConstBuffer");
	if (vsConstantBuffer != nullptr)
	{
		vsConstantBuffer->SetVariable("World", world);
		vsConstantBuffer->SetVariable("View", view);
		vsConstantBuffer->SetVariable("Proj", proj);

		XMFLOAT4X4 worldInvertTranspose;
		XMStoreFloat4x4(&worldInvertTranspose, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
		vsConstantBuffer->SetVariable("WorldInvertTranspose", worldInvertTranspose);
	}
	vertexShader->UpdateSubResources(context);
	vertexShader->Bind(context);
	 
	// ==== PS ==== //
	// サンプラーをシェーダに渡す
	auto sampler = states->LinearClamp();
	context->PSSetSamplers(0, 1, &sampler);
	for (auto& submesh : m_submeshList)
	{
		MaterialData mat = m_materialDataList[submesh.materialIndex];
		// テクスチャをシェーダに渡す
		ID3D11ShaderResourceView* srv = nullptr;
		if (mat.textureIndex >= 0)
		{
			srv = m_textureList[mat.textureIndex].Get();
		}
		pixelShader->GetShaderTextrueInfo("Texture")->texture = srv;

		// 定数バッファの設定
		auto psConstantBuffer = pixelShader->GetConstatntBufferInfo("ConstBuffer");
		if (psConstantBuffer != nullptr)
		{
			psConstantBuffer->SetVariable("BaseColor", mat.baseColor);
			psConstantBuffer->SetVariable("TextureIndex", mat.textureIndex);
			psConstantBuffer->SetVariable("LightDirection", XMFLOAT4(1.0f, -1.0f, 1.0f, 1.0f));
		}
		pixelShader->UpdateSubResources(context);
		pixelShader->Bind(context);

		// 描画
		context->DrawIndexed(submesh.indexCount, submesh.indexStart, 0);
	}
}


/**
 * \brief モデルの作成
 * 
 * \param filepath
 */
void MyModel::Create(
	ID3D11Device1* device,
	const std::string& filepath)
{
	std::ifstream ifs(filepath, std::ios::binary);

	if (!ifs.is_open())
	{
		OutputDebugStringA("ファイルが開けませんでした\n");
		return;
	}

	// ヘッダーの読み込み
	ModelHeader header;
	ifs.read(
		reinterpret_cast<char*>(&header),
		sizeof(ModelHeader));

	// 頂点の読み込み
	m_vertexList.resize(header.vertexCount);
	ifs.read(
		reinterpret_cast<char*>(m_vertexList.data()),
		sizeof(Vertex) * m_vertexList.size());

	// インデックスの読み込み
	m_indexList.resize(header.indexCount);
	ifs.read(
		reinterpret_cast<char*>(m_indexList.data()),
		sizeof(uint32_t) * m_indexList.size());

	// サブメッシュの読み込み
	m_submeshList.resize(header.submeshCount);
	ifs.read(
		reinterpret_cast<char*>(m_submeshList.data()),
			sizeof(Submesh) * m_submeshList.size());

	// マテリアルの読み込み
	m_materialDataList.resize(header.materialCount);
	ifs.read(
		reinterpret_cast<char*>(m_materialDataList.data()),
		sizeof(MaterialData) * m_materialDataList.size());

	// テクスチャの読み込み
	std::vector<std::vector<uint8_t>> textureBinaryList;
	for (int i = 0; i < header.textureCount; i++)
	{
		// テクスチャサイズ
		uint64_t size;
		ifs.read(
			reinterpret_cast<char*>(&size),
			sizeof(uint64_t));

		std::vector<uint8_t> texture(size);
		ifs.read(
			reinterpret_cast<char*>(texture.data()),
			sizeof(uint8_t) * texture.size());

		textureBinaryList.push_back(texture);
	}

	// 頂点バッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * m_vertexList.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = m_vertexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_vertexBuffer.ReleaseAndGetAddressOf()));
	}

	// インデックスバッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(uint32_t) * m_indexList.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = m_indexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_indexBuffer.ReleaseAndGetAddressOf()));
	}

	// テクスチャの作成
	for (auto& texData : textureBinaryList)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DX::ThrowIfFailed(
			CreateWICTextureFromMemory(
				device,
				texData.data(),
				texData.size(),
				nullptr,
				texture.ReleaseAndGetAddressOf()));

		m_textureList.push_back(std::move(texture));
	}
}
