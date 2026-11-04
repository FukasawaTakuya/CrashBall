#pragma once

#include "Service.h"
#include "SimpleMath.h"
#include <d3d11.h>

 /**
  * \brief 
  */
class  IPaintTexture : public Service {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IPaintTexture() = default;

	// デストラクタ
	virtual ~IPaintTexture() = default;

	// 操作
public:

	// 描画命令の登録
	virtual void RegisterRenderCommnad(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color& color) = 0;

	// ペイントのクリア
	virtual void ClearPaint() = 0;

	// 取得/設定
public:

	virtual ID3D11ShaderResourceView* GetPaintTexture() const = 0;

	// 内部実装
private:

};
