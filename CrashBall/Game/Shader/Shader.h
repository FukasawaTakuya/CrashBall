/*****************************************************************//**
 * \file   Shader.h
 * \brief  シェーダー操作クラス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once
#include "d3d11shader.h"
#include <d3dcompiler.h>
#include <variant>

#include "Game/ResourceManager/Interface/IShaderManager.h"

// シェーダーのポインタを保持するバリアント
using ShaderVariant = std::variant<
	ID3D11VertexShader*,
	ID3D11PixelShader*,
	ID3D11ComputeShader*>;

// 定数バッファのポインタを保持する定数バッファ関連構造体
struct ConstantBufferPtr
{
	ID3D11Buffer* buffer = nullptr;	// 定数バッファのポインタ
	ConstantBufferInfo info;// 定数バッファ情報
};

// UAVのポインタを保持するUAV関連構造体
struct RWStructuredBufferPtr
{
	ID3D11UnorderedAccessView* uav;	// UAVのポインタ
	ID3D11Buffer* buffer;			// バッファのポインタ
	UnorderedAccessViewInfo info;	// UAV情報
	ID3D11Buffer* stagingBuffer[3];	// ステージングバッファのポインタ
	uint32_t uavCount;				// UAV数
	void* cpudata;					// CPU側のデータ格納先
	std::function<void(int)> setUavCreateCmd;	// UAV作成命令の設定命令

	int frameCount = 0;							// ステージングバッファ用の経過フレーム数
};

 /**
  * \brief シェーダー操作クラス
  */
class  Shader {

	// メンバ変数の宣言 -----------------------------------------------
private:

	ShaderVariant m_shader;										// シェーダー
	ID3DBlob* m_blob;											// バイナリ情報
	std::vector<ConstantBufferPtr> m_constantBuffer;			// 定数バッファ
	std::vector<ShaderTextrueInfo> m_shaderTextrueInfo;			// シェーダに渡すテクスチャ情報
	std::vector<RWStructuredBufferPtr> m_rwStructuredBuffer;	// UAV情報
	ID3D11InputLayout* m_inputLayout;							// 入力レイアウト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Shader();

	// デストラクタ
	~Shader() = default;

	// 操作
public:

	// サブリソースの更新
	void UpdateSubResources(ID3D11DeviceContext1* conetxt);

	// バインド
	void Bind(ID3D11DeviceContext1* context);

	// バインド解除
	void ReleaseBind(ID3D11DeviceContext1* context);

	// UAVの作成
	void CreateUAV(const std::string& uavName, int uavCount);

	// CPU側のUAVデータの格納先の設定
	void SetCpuData(const std::string& uavName, void* cpudata);

	// 取得/設定
public:

	// バイナリ情報の取得
	ID3DBlob* GetBlob() const { return m_blob; }

	// 定数バッファ情報の取得
	ConstantBufferInfo* GetConstatntBufferInfo(const std::string& name)
	{
		auto it = std::ranges::find_if(m_constantBuffer,
			[&](ConstantBufferPtr& cbuffer)
			{
				return name == cbuffer.info.name;
			});

		if (it != m_constantBuffer.end())
		{
			return &it->info;
		}
		else
		{
			return nullptr;
		}
	}

	// シェーダに渡すテクスチャ情報の取得
	ShaderTextrueInfo* GetShaderTextrueInfo(const std::string& name)
	{
		auto it = std::ranges::find_if(m_shaderTextrueInfo,
			[&](ShaderTextrueInfo& info)
			{
				return name == info.name;
			});

		if (it != m_shaderTextrueInfo.end())
		{
			return it._Ptr;
		}
		else
		{
			return nullptr;
		}
	}

	// 入力レイアウトの取得
	ID3D11InputLayout* GetInputLayOut() const
	{
		return m_inputLayout;
	}

	// シェーダの設定
	void SetShader(ShaderInfo* shaderInfo);

	// 内部実装
private:
};
