/*****************************************************************//**
 * \file   ComputShaderDispatcher.h
 * \brief  コンピュートシェーダーのディスパッチ管理クラス
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once

#include "IComputShaderDispatcher.h"

 /**
  * \brief コンピュートシェーダーのディスパッチ管理クラス
  */
class  ComputShaderDispatcher : public IComputShaderDispatcher {

	// メンバ変数の宣言 -----------------------------------------------
private:

	std::vector<DispatchCommand> m_dispatchCommandList;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ComputShaderDispatcher() = default;

	// デストラクタ
	~ComputShaderDispatcher() = default;

	// 操作
public:

	// ディスパッチ命令の登録
	void RegisterDispatchCommand(
		Shader* shader,
		const DirectX::SimpleMath::Vector3 groupNum) override;

	// ディスパッチ
	void Dispatch(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};
