#pragma once

#include "Game/Shader/Shader.h"
#include "SimpleMath.h"

// ディスパッチ命令
struct DispatchCommand
{
	Shader* shader;	// シェーダー
	DirectX::SimpleMath::Vector3 groupNum;	// スレッドグループ数
};

/**
 * \brief コンピュートシェーダーのディスパッチ管理クラス
 */
class  IComputShaderDispatcher {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IComputShaderDispatcher() = default;

	// デストラクタ
	virtual ~IComputShaderDispatcher() = default;

	// 操作
public:

	// ディスパッチ命令の登録
	virtual void RegisterDispatchCommand(
		Shader* shader,
		const DirectX::SimpleMath::Vector3 groupNum) = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
